//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <core/Selector/Selector.h>

#include <core/Actor/Actor.h>
#include <core/Selector/Selection.h>

#include <core/Entity/Entity.h>

#include <math/Vec.h>
#include <util/Procedure.h>
#include <core/Action.h>

using namespace mud; namespace toy
{
	Selector::Selector(User& user)
		: m_user(user)
		, m_actions()
		, m_methods()
	{}

	Selector::~Selector()
	{}

	void Selector::updateActions()
	{
		m_actions.clear();

		for(Ref object : m_selection)
		{
			if(object.type().is<Entity>() && val<Entity>(object).isa<Actor>())
				for(ProcedureType* action : val<Entity>(object).part<Actor>().m_actions.store())
					m_actions.safeAdd(*action);
		}
	}

	void Selector::updateMethods()
	{
		m_methods.clear();

		//for(ProcedureType* method : m_user.m_methods.store())
		//	m_methods.add(*method);
	}

	void Selector::execute(ProcedureType& action)
	{
		for(Ref object : m_selection)
			if(object.type().is<Entity>() && val<Entity>(object).isa<Actor>())
				val<Entity>(object).part<Actor>().execute(&m_user, action, val<Entity>(m_targets[0])); //@kludge we should create a different selector for actors
	}

	void Selector::execute(ProcedureType& action, TargetDispatcher& dispatcher)
	{
		dispatcher.init(m_targets);

		for(Ref object : m_selection)
			if(object.type().is<Entity>() && val<Entity>(object).isa<Actor>())
			{
				Ref target = dispatcher.dispatchTarget(object);
				val<Entity>(object).part<Actor>().queue(&m_user, action, val<Entity>(target));
			}
	}

	void Selector::handleAdd(Entity& entity)
	{
		UNUSED(entity);
		this->updateActions();
	}

	void Selector::handleRemove(Entity& entity)
	{
		UNUSED(entity);
		this->updateActions();
	}

	bool Selector::handleClear()
	{
		this->updateActions();
		return true;
	}
}