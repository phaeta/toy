//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <proto/Complex.h>
#include <math/Math.h>
#include <block/Forward.h>
#include <core/Entity/Entity.h>

using namespace mud; namespace toy
{
	class refl_ TOY_BLOCK_EXPORT Chunk : public Complex
	{
	public:
		constr_ Chunk(Id id, Entity& parent, const vec3& position, size_t index, Element& element, float size);

		comp_ attr_ Entity m_entity;

		attr_ size_t m_index;
		attr_ Block& m_block;
		attr_ Element& m_element;
		attr_ float m_size;

		Sector& sector();

		Chunk* neighbour(Side side);
		bool boundary(Side side);
	};
}
