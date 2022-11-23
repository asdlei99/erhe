#include "xr/controller_visualization.hpp"
#include "scene/material_library.hpp"
#include "scene/scene_root.hpp"
#include "renderers/mesh_memory.hpp"

#include "erhe/graphics/buffer_transfer_queue.hpp"
#include "erhe/geometry/shapes/torus.hpp"
#include "erhe/primitive/primitive_builder.hpp"
#include "erhe/scene/mesh.hpp"
#include "erhe/scene/scene.hpp"
#include "erhe/toolkit/profile.hpp"
#include "erhe/xr/headset.hpp"

namespace editor
{

Controller_visualization::Controller_visualization(
    Mesh_memory&       mesh_memory,
    Scene_root&        scene_root,
    erhe::scene::Node* view_root
)
{
    ERHE_PROFILE_FUNCTION

    const auto& material_library = scene_root.material_library();
    auto controller_material = material_library->make_material(
        "Controller",
        glm::vec4{0.1f, 0.1f, 0.2f, 1.0f}
    );
    //constexpr float length = 0.05f;
    //constexpr float radius = 0.02f;
    auto controller_geometry = erhe::geometry::shapes::make_torus(0.05f, 0.0025f, 40, 14);
    controller_geometry.transform(erhe::toolkit::mat4_swap_yz);
    controller_geometry.reverse_polygons();

    erhe::graphics::Buffer_transfer_queue buffer_transfer_queue;
    auto controller_pg = erhe::primitive::make_primitive(
        controller_geometry,
        mesh_memory.build_info
    );

    erhe::primitive::Primitive primitive{
        .material              = controller_material,
        .gl_primitive_geometry = controller_pg
    };
    m_controller_mesh = std::make_shared<erhe::scene::Mesh>("Controller", primitive);
    m_controller_mesh->node_data.visibility_mask |= erhe::scene::Node_visibility::visible | erhe::scene::Node_visibility::controller;
    m_controller_mesh->mesh_data.layer_id = scene_root.layers().content()->id.get_id();
    m_controller_mesh->set_parent(view_root);
}

void Controller_visualization::update(const erhe::xr::Pose& pose)
{
    const glm::mat4 orientation = glm::mat4_cast(pose.orientation);
    const glm::mat4 translation = glm::translate(glm::mat4{ 1 }, pose.position);
    const glm::mat4 m           = translation * orientation;
    m_controller_mesh->set_parent_from_node(m);
}

auto Controller_visualization::get_node() const -> erhe::scene::Node*
{
    return m_controller_mesh.get();
}

}