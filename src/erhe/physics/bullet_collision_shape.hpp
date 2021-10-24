#pragma once

#include "erhe/physics/icollision_shape.hpp"

#include "btBulletCollisionCommon.h"
#include "BulletCollision/CollisionShapes/btBoxShape.h"
#include "BulletCollision/CollisionShapes/btConeShape.h"
#include "BulletCollision/CollisionShapes/btCylinderShape.h"
#include "BulletCollision/CollisionShapes/btSphereShape.h"

#include <glm/glm.hpp>

#include <memory>
#include <optional>

namespace erhe::physics
{

class Bullet_collision_shape
    : public ICollision_shape
{
public:
    Bullet_collision_shape(btCollisionShape* shape)
        : m_bullet_collision_shape{shape}
    {
    }

    // Implements ICollision_shape
    void calculate_local_inertia(float mass, glm::vec3& inertia) const                                   override;
    auto is_convex              () const -> bool                                                         override;
    void add_child_shape        (ICollision_shape* shape, const glm::mat3 basis, const glm::vec3 origin) override;

    auto get_bullet_collision_shape() -> btCollisionShape*
    {
        return m_bullet_collision_shape;
    }
    auto get_bullet_collision_shape() const -> const btCollisionShape*
    {
        m_bullet_collision_shape;
    }

protected:
    btCollisionShape* m_bullet_collision_shape;
};

class Bullet_box_shape
    : public Bullet_collision_shape
{
public:
    Bullet_box_shape(const glm::vec3 half_extents);

private:
    btBoxShape m_box_shape;
};

class Bullet_capsule_x_shape
    : public Bullet_collision_shape
{
public:
    Bullet_capsule_x_shape(const float radius, const float length);

private:
    btCapsuleShapeX m_capsule_shape;
};

class Bullet_capsule_y_shape
    : public Bullet_collision_shape
{
public:
    Bullet_capsule_y_shape(const float radius, const float length);

private:
    btCapsuleShapeX m_capsule_shape;
};

class Bullet_capsule_z_shape
    : public Bullet_collision_shape
{
public:
    Bullet_capsule_z_shape(const float radius, const float length);

private:
    btCapsuleShapeX m_capsule_shape;
};

class Bullet_cone_x_shape
    : public Bullet_collision_shape
{
public:
    Bullet_cone_x_shape(const float base_radius, const float height);

private:
    btConeShapeX m_cone_shape;
};

class Bullet_cone_y_shape
    : public Bullet_collision_shape
{
public:
    Bullet_cone_y_shape(const float base_radius, const float height);

private:
    btConeShape m_cone_shape;
};

class Bullet_cone_z_shape
    : public Bullet_collision_shape
{
public:
    Bullet_cone_z_shape(const float base_radius, const float height);

private:
    btConeShapeZ m_cone_shape;
};

class Bullet_cylinder_x_shape
    : public Bullet_collision_shape
{
public:
    Bullet_cylinder_x_shape(const glm::vec3 half_extents);

private:
    btCylinderShapeX m_cylinder_shape;
};

class Bullet_cylinder_y_shape
    : public Bullet_collision_shape
{
public:
    Bullet_cylinder_y_shape(const glm::vec3 half_extents);

private:
    btCylinderShape m_cylinder_shape;
};

class Bullet_cylinder_z_shape
    : public Bullet_collision_shape
{
public:
    Bullet_cylinder_z_shape(const glm::vec3 half_extents);

private:
    btCylinderShapeZ m_cylinder_shape;
};

class Bullet_sphere_shape
    : public Bullet_collision_shape
{
public:
    Bullet_sphere_shape(const float radius);

private:
    btSphereShape m_sphere_shape;
};

} // namespace erhe::physics