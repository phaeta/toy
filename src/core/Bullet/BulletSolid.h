//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <proto/Complex.h>
#include <core/Forward.h>
#include <core/Bullet/BulletCollider.h>

using namespace mud; namespace toy
{
	class BulletMotionState;

	class refl_ TOY_CORE_EXPORT BulletSolid : public BulletCollider
    {
    public:
		BulletSolid(SubBulletWorld& bullet_world, Solid& solid);
        ~BulletSolid();

		btRigidBody* m_rigid_body;

		virtual void update_transform(const vec3& position, const quat& rotation) override;
		virtual void update_motion(const vec3& linear_velocity, const vec3& angular_velocity) override;

		virtual vec3 linear_velocity() override;
		virtual vec3 angular_velocity() override;

		virtual void set_linear_velocity(const vec3& force) override;
		virtual void set_angular_velocity(const vec3& torque) override;
		virtual void set_angular_factor(const vec3& factor) override;

		virtual void set_force(const vec3& force) override;
		virtual void set_torque(const vec3& torque) override;

		virtual void impulse(const vec3& force, const vec3& point) override;

		virtual void impulse_force(const vec3& force) override;
		virtual void impulse_torque(const vec3& torque) override;

    public:
		unique_ptr<BulletMotionState> m_motion_state;
    };
}
