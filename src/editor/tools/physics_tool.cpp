#include "tools/physics_tool.hpp"
#include "log.hpp"
#include "tools.hpp"
#include "renderers/line_renderer.hpp"
#include "scene/node_physics.hpp"
#include "scene/scene_root.hpp"
#include "tools/pointer_context.hpp"

#include "erhe/scene/mesh.hpp"
#include "erhe/physics/iworld.hpp"
#include "erhe/physics/iconstraint.hpp"

#include "imgui.h"

namespace editor
{

using namespace erhe::toolkit;

Physics_tool::Physics_tool()
    : erhe::components::Component{c_name}
{
}

Physics_tool::~Physics_tool() = default;

void Physics_tool::connect()
{
    m_scene_root = get<Scene_root>();
}

void Physics_tool::initialize_component()
{
    get<Editor_tools>()->register_tool(this);
}

auto Physics_tool::state() const -> State
{
    return m_state;
}

auto Physics_tool::description() -> const char*
{
    return c_name.data();
}

void Physics_tool::imgui(Pointer_context&)
{
    ImGui::Begin("Physics Tool");

    ImGui::SliderFloat("Tau",             &m_tau,             0.0f,  0.1f);
    ImGui::SliderFloat("Damping",         &m_damping,         0.0f,  1.0f);
    ImGui::SliderFloat("Impulse Clamp",   &m_impulse_clamp,   0.0f, 10.0f);
    ImGui::SliderFloat("Linear Damping",  &m_linear_damping,  0.0f,  1.0f);
    ImGui::SliderFloat("Angular Damping", &m_angular_damping, 0.0f,  1.0f);
    ImGui::End();
}

void Physics_tool::cancel_ready()
{
    m_state = State::Passive;
}

auto Physics_tool::update(Pointer_context& pointer_context) -> bool
{
    ZoneScoped;

    if (pointer_context.priority_action != Action::drag)
    {
        if (m_state != State::Passive)
        {
            cancel_ready();
        }
        return false;
    }

    if (!pointer_context.scene_view_focus ||
        !pointer_context.pointer_in_content_area())
    {
        return false;
    }

    if (m_state == State::Passive)
    {
        if (pointer_context.hover_content && pointer_context.mouse_button[Mouse_button_left].pressed)
        {
            m_drag_mesh             = pointer_context.hover_mesh;
            m_drag_depth            = pointer_context.pointer_z;
            m_drag_position_in_mesh = glm::vec3(m_drag_mesh->node()->node_from_world() * glm::vec4(pointer_context.position_in_world(), 1.0f));
            m_drag_node_physics     = m_drag_mesh->node()->get_attachment<Node_physics>();
            if (m_drag_node_physics)
            {
                m_original_linear_damping  = m_drag_node_physics->rigid_body()->get_linear_damping();
                m_original_angular_damping = m_drag_node_physics->rigid_body()->get_angular_damping();
                m_drag_node_physics->rigid_body()->set_damping(m_linear_damping,
                                                             m_angular_damping);
                const glm::vec3 pivot{m_drag_position_in_mesh.x, m_drag_position_in_mesh.y, m_drag_position_in_mesh.z};
                m_drag_constraint = erhe::physics::IConstraint::create_point_to_point_constraint_unique(m_drag_node_physics->rigid_body(),
                                                                                                        pivot);
                m_drag_constraint->set_impulse_clamp(m_impulse_clamp);
                m_drag_constraint->set_damping(m_damping);
                m_drag_constraint->set_tau(m_tau);
                m_drag_node_physics->rigid_body()->begin_move();
                m_scene_root->physics_world().add_constraint(m_drag_constraint.get());
            }
            log_tools.trace("Physics tool state = ready\n");
            m_state = State::Ready;
            return true;
        }
        return false;
    }

    if (m_state == State::Passive)
    {
        return false;
    }

    if ((m_state == State::Ready) && pointer_context.mouse_moved)
    {
        log_tools.trace("Physics tool state = active\n");
        m_state = State::Active;
    }

    if (m_state != State::Active)
    {
        return false;
    }

    if (!m_drag_mesh->node())
    {
        return false;
    }

    m_drag_position_start = glm::vec3(m_drag_mesh->node()->world_from_node() * glm::vec4(m_drag_position_in_mesh, 1.0f));
    m_drag_position_end   = pointer_context.position_in_world(m_drag_depth);

    if (m_drag_constraint)
    {
        m_drag_constraint->set_pivot_in_b(m_drag_position_end);
    }

    if (pointer_context.mouse_button[Mouse_button_left].released)
    {
        if (m_drag_constraint)
        {
            if (m_drag_node_physics)
            {
                m_drag_node_physics->rigid_body()->set_damping(m_original_linear_damping,
                                                               m_original_angular_damping);
                m_drag_node_physics->rigid_body()->end_move();
                m_drag_node_physics.reset();
            }
            m_scene_root->physics_world().remove_constraint(m_drag_constraint.get());
            m_drag_constraint.reset();
        }
        m_drag_mesh.reset();
        log_tools.trace("Physics tool state = passive\n");
        m_state = State::Passive;
    }
    return true;
    return false;
}


void Physics_tool::render(const Render_context& render_context)
{
    ZoneScoped;

    render_context.line_renderer->set_line_color(0xffffffffu);
    render_context.line_renderer->add_lines({{m_drag_position_start, m_drag_position_end}}, 4.0f);    
}

}
