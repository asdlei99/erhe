#include "erhe/physics/bullet_constraint.hpp"
#include "erhe/physics/bullet_rigid_body.hpp"
#include "erhe/physics/glm_conversions.hpp"

namespace erhe::physics
{

auto IConstraint::create_point_to_point_constraint(IRigid_body* rigid_body, const glm::vec3 point) -> IConstraint*
{
    return new Bullet_point_to_point_constraint(rigid_body, point);
}
auto IConstraint::create_point_to_point_constraint_shared(IRigid_body* rigid_body, const glm::vec3 point) -> std::shared_ptr<IConstraint>
{
    return std::make_shared<Bullet_point_to_point_constraint>(rigid_body, point);
}
auto IConstraint::create_point_to_point_constraint_unique(IRigid_body* rigid_body, const glm::vec3 point) -> std::unique_ptr<IConstraint>
{
    return std::make_unique<Bullet_point_to_point_constraint>(rigid_body, point);
}

auto IConstraint::create_point_to_point_constraint(IRigid_body*    rigid_body_a, IRigid_body*    rigid_body_b, 
                                                   const glm::vec3 pivot_in_a,   const glm::vec3 pivot_in_b) -> IConstraint*
{
    return new Bullet_point_to_point_constraint(rigid_body_a, rigid_body_b, pivot_in_a, pivot_in_b);
}
auto IConstraint::create_point_to_point_constraint_shared(IRigid_body*    rigid_body_a, IRigid_body*    rigid_body_b, 
                                                          const glm::vec3 pivot_in_a,   const glm::vec3 pivot_in_b) -> std::shared_ptr<IConstraint>
{
    return std::make_shared<Bullet_point_to_point_constraint>(rigid_body_a, rigid_body_b, pivot_in_a, pivot_in_b);
}
auto IConstraint::create_point_to_point_constraint_unique(IRigid_body*    rigid_body_a, IRigid_body*    rigid_body_b, 
                                                          const glm::vec3 pivot_in_a,   const glm::vec3 pivot_in_b) -> std::unique_ptr<IConstraint>
{
    return std::make_unique<Bullet_point_to_point_constraint>(rigid_body_a, rigid_body_b, pivot_in_a, pivot_in_b);
}

Bullet_point_to_point_constraint::Bullet_point_to_point_constraint(IRigid_body* rigid_body, const glm::vec3 point)
    : m_bullet_constraint{
        *static_cast<Bullet_rigid_body*>(rigid_body)->get_bullet_rigid_body(),
        from_glm(point)
    }
{
}

Bullet_point_to_point_constraint::Bullet_point_to_point_constraint(IRigid_body*    rigid_body_a, IRigid_body*    rigid_body_b, 
                                                                   const glm::vec3 pivot_in_a,   const glm::vec3 pivot_in_b)
    : m_bullet_constraint{
        *static_cast<Bullet_rigid_body*>(rigid_body_a)->get_bullet_rigid_body(),
        *static_cast<Bullet_rigid_body*>(rigid_body_b)->get_bullet_rigid_body(),
        from_glm(pivot_in_a),
        from_glm(pivot_in_b)
    }
{
}

void Bullet_point_to_point_constraint::set_pivot_in_a(const glm::vec3 pivot_in_a)
{
    m_bullet_constraint.setPivotA(from_glm(pivot_in_a));
}
void Bullet_point_to_point_constraint::set_pivot_in_b(const glm::vec3 pivot_in_b)
{
    m_bullet_constraint.setPivotB(from_glm(pivot_in_b));
}
auto Bullet_point_to_point_constraint::get_pivot_in_a() -> glm::vec3
{
    return to_glm(m_bullet_constraint.getPivotInA());
}
auto Bullet_point_to_point_constraint::get_pivot_in_b() -> glm::vec3
{
    return to_glm(m_bullet_constraint.getPivotInB());
}

void Bullet_point_to_point_constraint::set_impulse_clamp(const float impulse_clamp)
{
    m_bullet_constraint.m_setting.m_impulseClamp = impulse_clamp;
}

void Bullet_point_to_point_constraint::set_damping(const float damping)
{
    m_bullet_constraint.m_setting.m_damping = damping;
}

void Bullet_point_to_point_constraint::set_tau(const float tau)
{
    m_bullet_constraint.m_setting.m_tau = tau;
}

auto Bullet_point_to_point_constraint::get_bullet_constraint() -> btTypedConstraint*
{
    return &m_bullet_constraint;
}
auto Bullet_point_to_point_constraint::get_bullet_constraint() const -> const btTypedConstraint*
{
    return &m_bullet_constraint;
}

} // namespace erhe::physics
