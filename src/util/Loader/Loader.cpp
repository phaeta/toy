//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.


#include <util/Generated/Types.h>
#include <util/Loader/Loader.h>

#include <obj/Memory/ObjectPool.h>

#include <util/Loader/DataLoader.h>
#include <util/Loader/MemberLoader.h>

#include <obj/Reflect/Injector.h>
#include <obj/Reflect/Class.h>

#include <obj/Complex.h>

#include <set>

using namespace mud; namespace toy
{
	GlobalLoader::GlobalLoader()
		: m_loaders(MUD_MAX_TYPES)
	{}

	void GlobalLoader::clear()
	{
		m_loaders.clear();
		m_loaders.resize(MUD_MAX_TYPES);
	}

	void GlobalLoader::setDataSource(DataSource& dataSource)
	{
		m_dataSource = &dataSource;
	}

	ObjectLoader& GlobalLoader::getLoader(Type& type)
	{
		if(m_loaders[type.m_id] == nullptr)
			m_loaders[type.m_id] = make_object<ObjectLoader>(type, *m_dataSource);

		return *m_loaders[type.m_id];
	}

	Loader::Loader(Type& type, DataSource& dataSource, ObjectLoader* parent)
		: m_type(type)
		, m_dataSource(dataSource)
		, m_parent(parent)
		, m_autoId(false)
		, m_dataId(false)
	{
		if(type.m_class->m_members.empty() || strcmp(type.m_class->m_members[0].m_name, "id") != 0)
			m_dataId = true;
		if(m_dataId && is_root_type(type))
			m_autoId = true;
	}

	Loader::~Loader()
	{}

	void Loader::setup(Loader* parent, Member* member)
	{
		m_dataLoader = m_dataSource.makeLoader();
		m_dataLoader->setup(m_type, parent ? parent->m_dataLoader.get() : nullptr, member);
		m_data = m_dataLoader->data();
	}

	void Loader::select(Id id)
	{
		if(m_dataLoader)
			m_dataLoader->select(id);
	}

	bool Loader::selectNext()
	{
		if(m_dataLoader)
			return m_dataLoader->selectNext();
		return true;
	}

	void Loader::parseNext()
	{
		if(m_dataLoader)
			m_dataLoader->load(m_data);
	}

	void Loader::saveInit()
	{}

	void Loader::saveCommit()
	{}

	void Loader::queue(Ref object, size_t depth)
	{
		UNUSED(object); UNUSED(depth);
	}

	void Loader::dump(Ref object)
	{
		UNUSED(object);
	}

	void Loader::erase(Ref object)
	{
		UNUSED(object);
	}


	ObjectLoader::ObjectLoader(Type& type, DataSource& dataSource, ObjectLoader* parent, Member* member)
		: Loader(type, dataSource, parent)
		, m_injector(nullptr)
		, m_args()
		, m_batch(5)
		, m_batchCounter(0)
		, m_protoIndex(0)
	{
		this->setupObject(parent, member);
	}

	ObjectLoader::~ObjectLoader()
	{}

	void ObjectLoader::setupObject(Loader* parent, Member* loader_member)
	{
		this->setup(parent, loader_member);

		m_injectors.emplace_back(m_type);

		for(Type* type : m_type.m_class->m_prototypes)
			if(type->m_class->m_constructors.size() > size_t(ConstructorIndex::ProtoParts))
				m_injectors.emplace_back(*type, type->m_class->m_constructors[size_t(ConstructorIndex::ProtoParts)]);

		m_injector = &m_injectors.front();
		m_args = m_injector->m_args;

		Constructor& constructor = *m_type.m_class->constructor(m_type.m_class->m_members.size());
		for(Param& param : constructor.m_params)
		{
			if(param.m_index == 0)
				continue;

			Member& member = m_type.m_class->member(param.m_name);
			bool partstem = (!is_root_type(m_type) && param.m_index == 0);
			bool link = member.is_link() || partstem;

			if(strcmp(param.m_name, "prototype") == 0)
				m_protoIndex = param.m_index;

			TypeClass typeClass = member.meta().m_type_class;
			if(member.m_type->is<Type>())
				m_subloaders.emplace_back(make_object<TypeLoader>(*this, member, param.m_index));
			else if((is_object(*member.m_type) || is_struct(*member.m_type)) && link)
				m_subloaders.emplace_back(make_object<LinkedLoader>(*this, member, param.m_index));
			else if(is_struct(*member.m_type))
				m_subloaders.emplace_back(make_object<OwnedLoader>(*this, member, param.m_index));
			else if(typeClass <= TypeClass::Complex)
				m_subloaders.emplace_back(make_object<LinkedLoader>(*this, member, param.m_index));
			else if(is_sequence(*member.m_type))
				m_subloaders.emplace_back(make_object<SequenceLoader>(*this, member, param.m_index));
			else if(is_base_type(*member.m_type))
				m_subloaders.emplace_back(make_object<MemberLoader>(*this, member, param.m_index));
			else if(is_enum(*member.m_type))
				m_subloaders.emplace_back(make_object<MemberLoader>(*this, member, param.m_index));
		}

		std::set<Type*> parts;
		for(Prototype* prototype : m_type.m_class->m_prototypes)
			for(Type* part : prototype->m_parts)
				parts.insert(part);

		for(Type* part : parts)
			if(part->m_kind != TypeKind::Prototype)
				m_subloaders.push_back(make_object<PartLoader>(*this, *part));

		for(Member& member : m_type.m_class->m_members)
		{
			if(member.is_structure() && (is_sequence(*member.m_type)))
				m_subloaders.push_back(make_object<StructureLoader>(*this, member, m_subloaders.size()));
		}

		//for(auto& loader : m_subloaders)
		//	loader->setupSubLoader(); // @todo move back and fix StructureLoader setup
	}

	Id ObjectLoader::allocate()
	{
		return m_dataLoader->allocate();
	}

	void ObjectLoader::erase(Ref object, Id id)
	{
		for(auto& loader : m_subloaders)
			loader->erase(object);

		m_dataLoader->deallocate(id);
	}














	Ref ObjectLoader::load(Id id)
	{
		this->select(id);
		selectNext();
		Ref object = loadNext();
		while(selectNext())
			loadNext();
		return object;
	}

	void ObjectLoader::fill(Ref object, Id id)
	{
		UNUSED(object);
		this->select(id);
		while(selectNext())
			loadNext();
	}

	void ObjectLoader::select(Id id)
	{
		Loader::select(id);

		for(auto& loader : m_subloaders)
			loader->select(id);
	}

	bool ObjectLoader::selectNext()
	{
		if(!Loader::selectNext())
			return false;

		for(auto& loader : m_subloaders)
			loader->selectNext();

		return true;
	}

	void ObjectLoader::parseNext()
	{
		Loader::parseNext();

		if(m_type.m_class->m_prototypes.size() > 0)
			this->parsePrototype();

		for(auto& loader : m_subloaders)
			loader->parseNext();
	}

	void ObjectLoader::parsePrototype()
	{
		m_subloaders[m_protoIndex]->parseNext();
		m_prototype = &val<Prototype>(m_args[m_protoIndex]);

		for(Injector& injector : m_injectors)
			if(&injector.m_type == m_prototype)
			{
				m_injector = &injector;
				m_args = m_injector->m_args;
			}
	}

	void ObjectLoader::loadNext(Var& arg)
	{
		this->parseNext();
		m_injector->inject(arg);
	}

	Ref ObjectLoader::loadNext()
	{
		this->parseNext();

		// compute poolSector from input arguments for chunked allocation
		// size_t poolSector 
		return m_injector->inject(GlobalPool::me().pool(*m_prototype));
	}














	Id ObjectLoader::saveId(Ref object)
	{
		saveInit();
		queue(object, m_batchDepth);
		saveCommit();

		return 0;// @todo get id 
	}

	void ObjectLoader::saveInit()
	{
		if(!m_dataLoader)
		{
			printf("WARNING: Loader for type %s has no DataLoader. Actually saving any object of this type will crash or fail.\n", m_type.m_name);
			return;
		}

		m_dataSource.beginBatch(*this);

		m_batchDepth = 0;
		m_batchCounter = 0;

		for(auto& loader : m_subloaders)
			loader->saveInit();
	}

	void ObjectLoader::queue(Ref object, size_t depth)
	{
		//this->debugPrint(object, depth, "Queuing ");

		++m_batchCounter;

		for(auto& loader : m_subloaders)
			loader->queue(object, depth);

		m_batch[depth].push_back(object);
	}

	/*void ObjectLoader::dumpElement(Id parent, Id object)
	{
		Id id = m_autoId ? m_autoFirstId++ : object;
		m_dataLoader->saveElement(parent, id);
	}*/

	void ObjectLoader::save(Ref object, Id id)
	{
		//this->debugPrint(object, m_batchDepth, "Saving ");

		for(auto& loader : m_subloaders)
			loader->dump(object);

		//if(!m_type.m_meta->isRoot)
		//	id = part.stem().m_id; @todo

		m_dataLoader->save(id, m_data, false);
	}

	void ObjectLoader::saveCommit()
	{
		if(m_batchCounter == 0)
			return;

		for(auto& loader : m_subloaders)
			loader->saveCommit();

		for(m_batchDepth = m_batch.size() - 1; m_batchDepth + 1 > 0; --m_batchDepth)
			for(Ref& object : m_batch[m_batchDepth])
			{
				Id id = val<Id>(cls(object).m_id_member->get(object));
				this->save(object, id);
			}

		m_batch.clear();

		if(m_autoId)
			m_autoFirstId = m_dataLoader->lastId() + 1 - m_batchCounter;

		m_dataSource.commitBatch(*this);

		m_batchCounter = 0;
	}

	void ObjectLoader::debugPrint(Ref object, size_t depth, cstring message)
	{
		if(!is_root_type(m_type))
			++depth;
		for(size_t i = 0; i < depth; ++i)
			printf("  ");
		printf("%s %s : %s\n", message, m_type.m_name, m_type.m_meta->m_type_class == TypeClass::Complex ? val<Complex>(object).m_prototype.m_name : "");
	}






	PartLoader::PartLoader(ObjectLoader& parent, Type& type)
		: ObjectLoader(type, parent.m_dataSource, &parent)
	{}

	void PartLoader::parseNext()
	{
		if(m_parent->m_prototype->has_part(m_type))
		{
			m_args = m_parent->m_injector->args(m_type);
			ObjectLoader::parseNext();
		}
	}

	void PartLoader::queue(Ref object, size_t depth)
	{
		Complex& modular = val<Complex>(object);
		if(modular.has_part(m_type))
			ObjectLoader::queue(modular.partref(m_type), depth);
	}
}