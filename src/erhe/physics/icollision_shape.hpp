#pragma once

#include <glm/glm.hpp>

#include <memory>

namespace erhe::physics
{

enum class Axis : int
{
    X,
    Y,
    Z
};

class ICollision_shape
{
public:
    static auto create_box_shape                   (const glm::vec3 half_extents) -> ICollision_shape*;
    static auto create_box_shape_shared            (const glm::vec3 half_extents) -> std::shared_ptr<ICollision_shape>;

    static auto create_capsule_shape               (const Axis axis, const float radius, const float length) -> ICollision_shape*;
    static auto create_capsule_shape_shared        (const Axis axis, const float radius, const float length) -> std::shared_ptr<ICollision_shape>;

    static auto create_compound_shape              () -> ICollision_shape*;
    static auto create_compound_shape_shared       () -> std::shared_ptr<ICollision_shape>;

    static auto create_cone_shape                  (const Axis axis, const float base_radius, const float height) -> ICollision_shape*;
    static auto create_cone_shape_shared           (const Axis axis, const float base_radius, const float height) -> std::shared_ptr<ICollision_shape>;

    static auto create_convex_hull_shape           (const float* points, const int numPoints, const int stride) -> ICollision_shape*;
    static auto create_convex_hull_shape_shared    (const float* points, const int numPoints, const int stride) -> std::shared_ptr<ICollision_shape>;

    static auto create_cylinder_shape              (const Axis axis, const glm::vec3 half_extents) -> ICollision_shape*;
    static auto create_cylinder_shape_shared       (const Axis axis, const glm::vec3 half_extents) -> std::shared_ptr<ICollision_shape>;

    static auto create_sphere_shape                (const float radius) -> ICollision_shape*;
    static auto create_sphere_shape_shared         (const float radius) -> std::shared_ptr<ICollision_shape>;

    static auto create_uniform_scaling_shape       (ICollision_shape* shape, const float scale) -> ICollision_shape*;
    static auto create_uniform_scaling_shape_shared(ICollision_shape* shape, const float scale) -> std::shared_ptr<ICollision_shape>;

    virtual void calculate_local_inertia(const float mass, glm::vec3& inertia) const = 0;
    virtual auto is_convex              () const -> bool = 0;
    virtual void add_child_shape        (ICollision_shape* shape, const glm::mat3 basis, const glm::vec3 origin) = 0;
};


} // namespace erhe::physics