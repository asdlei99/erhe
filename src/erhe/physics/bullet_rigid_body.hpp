#pragma once

#include "erhe/physics/irigid_body.hpp"

#include "BulletDynamics/Dynamics/btRigidBody.h"

namespace erhe::physics
{

class Motion_state_adapter
    : public btMotionState
{
public:
    Motion_state_adapter(IMotion_state* motion_state);

	void getWorldTransform(btTransform& worldTrans) const override;
	void setWorldTransform(const btTransform& worldTrans) override;

private:
    IMotion_state* m_motion_state;
};

class Bullet_rigid_body
    : public IRigid_body
{
public:
    Bullet_rigid_body(
        IRigid_body_create_info& create_info,
        IMotion_state*           motion_state
    );

    // Implements IRigid_body
    //auto get_node_transform() const -> glm::mat4           override;
    void set_collision_mode  (Collision_mode collision_mode)                           override;
    auto get_collision_mode  () const -> Collision_mode                                override;
    auto get_collision_shape () const -> ICollision_shape*                             override;
    void set_dynamic         ()                                                        override;
    void set_static          ()                                                        override;
    void set_kinematic       ()                                                        override;
    auto get_friction        () -> float                                               override;
    void set_friction        (const float friction)                                    override;
    auto get_rolling_friction() -> float                                               override;
    void set_rolling_friction(const float rolling_friction)                            override;
    auto get_restitution     () -> float                                               override;
    void set_restitution     (const float restitution)                                 override;
    void set_world_transform (const glm::mat3 basis, const glm::vec3 origin)           override;
    void set_linear_velocity (const glm::vec3 velocity)                                override;
    void set_angular_velocity(const glm::vec3 velocity)                                override;
    auto get_linear_damping  () const -> float                                         override;
    auto get_angular_damping () const -> float                                         override;
    void set_damping         (const float linear_damping, const float angular_damping) override;
    auto get_local_inertia   () const -> glm::vec3                                     override;
    auto get_mass            () const -> float                                         override;
    void set_mass_properties (const float mass, const glm::vec3 local_inertia)         override;
    void begin_move          ()                                                        override; // Disables deactivation
    void end_move            ()                                                        override; // Sets active, clears disable deactivation

    auto get_bullet_rigid_body() -> btRigidBody*;

private:
    Motion_state_adapter              m_motion_state_adapter;
    std::shared_ptr<ICollision_shape> m_collision_shape;
    btRigidBody                       m_bullet_rigid_body;
    Collision_mode                    m_collision_mode{Collision_mode::e_kinematic};
};

} // namespace erhe::physics