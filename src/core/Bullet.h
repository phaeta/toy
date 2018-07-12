//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <math/Forward.h>
#include <math/Vec.h>
#include <math/Colour.h>

#ifdef TOY_PRIVATE

/* bullet */
#include <LinearMath/btScalar.h>
#include <LinearMath/btVector3.h>
#include <LinearMath/btQuaternion.h>
#include <LinearMath/btTransform.h>
#include <LinearMath/btTransformUtil.h>

using namespace mud; namespace toy
{
	inline vec3 to_vec3(const btVector3& vec) { return vec3{ vec.x(), vec.y(), vec.z() }; }
	inline btVector3 to_btvec3(const vec3& vec) { return btVector3{ vec.x, vec.y, vec.z }; }
	
	inline Colour to_colour(const btVector3& col) { return Colour(col.x(), col.y(), col.z()); }

	inline quat to_quat(const btQuaternion& q) { return quat{ q.w(), q.x(), q.y(), q.z() }; }
	inline btQuaternion to_btquat(const quat& q) { return btQuaternion{ q.x, q.y, q.z, q.w }; }
}

#endif