//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <infra/Updatable.h>
#include <infra/NonCopy.h>
#include <math/Vec.h>
#include <core/Forward.h>

#ifndef MUD_CPP_20
#include <atomic>
#endif

using namespace mud; namespace toy
{
	TOY_CORE_EXPORT bool spin_2d(Entity& entity, const vec3& axis, const vec3& target, float velocity, float time_step, float margin = 0.1f);
	TOY_CORE_EXPORT bool lookat_2d(Entity& entity, const vec3& axis, const vec3& target, float velocity, float time_step, float margin = 0.1f);
	TOY_CORE_EXPORT bool move_2d(Entity& entity, const vec3& target, float velocity, float time_step, float margin = 0.1f);
	TOY_CORE_EXPORT bool move_2d(Movable& movable, const vec3& target, float velocity, float time_step, float margin = 0.1f);
	TOY_CORE_EXPORT bool steer_2d(Entity& entity, const vec3& target, float velocity, float time_step, float margin = 0.1f);
	TOY_CORE_EXPORT bool steer_2d(Movable& movable, const vec3& target, float velocity, float time_step, float margin = 0.1f);
	TOY_CORE_EXPORT bool stick_2d(Entity& entity, const vec3& target, float velocity, float time_step, float margin = 0.1f);
	TOY_CORE_EXPORT bool track_2d(Entity& entity, const vec3& target, float velocity, float time_step, float margin = 0.1f);

	class refl_ TOY_CORE_EXPORT Movable : public NonCopy, public Updatable
	{
	public:
		constr_ Movable(Entity& entity);
		~Movable();

		attr_ Entity& m_entity;

		MotionState* m_motion_state = nullptr;

		vec3 m_linear_velocity = Zero3;
		vec3 m_angular_velocity = Zero3;

		vec3 m_direction = -Z3;
		vec3 m_acceleration = Zero3;

		bool m_moving = false;
		vec3 m_previous_position;

		vec3 m_max_linear_velocity = Zero3;

		size_t m_updated = 0;
		size_t m_acceleration_updated = 0;
		size_t m_last_tick = 0;

		void set_movement(const vec3& position, const quat& rotation, const vec3& linear_velocity, const vec3& angular_velocity);

        void set_linear_velocity(const vec3& velocity);
		void modify_linear_velocity(const vec3& velocity);

        void set_angular_velocity(const vec3& velocity);
		void modify_angular_velocity(const vec3& velocity);

		void set_acceleration(const vec3& acceleration, const vec3& maxLinVel);
		void modify_acceleration(const vec3& acceleration); 

        void next_frame(size_t tick, size_t delta);
	};
}
