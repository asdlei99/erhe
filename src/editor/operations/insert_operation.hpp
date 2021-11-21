#pragma once

#include "operations/ioperation.hpp"

#include "erhe/scene/light.hpp"
#include "erhe/scene/mesh.hpp"
#include "erhe/scene/node.hpp"
#include "erhe/toolkit/verify.hpp"

namespace erhe::geometry
{
    class Geometry;
}

namespace erhe::scene
{
    class Light_layer;
    class Mesh_layer;
    class Scene;
};

namespace erhe::physics
{
    class IWorld;
};

namespace editor
{

class Node_physics;
class Selection_tool;

class Node_transform_operation
    : public IOperation
{
public:
    class Context
    {
    public:
        erhe::scene::Mesh_layer&           layer;
        erhe::scene::Scene&                scene;
        erhe::physics::IWorld&             physics_world;
        std::shared_ptr<erhe::scene::Node> node;
        erhe::scene::Transform             parent_from_node_before;
        erhe::scene::Transform             parent_from_node_after;
    };

    explicit Node_transform_operation(const Context& context);
    ~Node_transform_operation        () override;

    // Implements IOperation
    void execute () const override;
    void undo    () const override;
    auto describe() const -> std::string override;

private:
    Context m_context;
};

class Scene_item_operation
    : public IOperation
{
public:
    enum class Mode : unsigned int
    {
        insert = 0,
        remove
    };

    static auto inverse(const Mode mode) -> Mode
    {
        switch (mode)
        {
        case Mode::insert: return Mode::remove;
        case Mode::remove: return Mode::insert;
        default:
            FATAL("Bad Context::Mode");
            // unreachable return Mode::insert;
        }
    }
};

class Mesh_insert_remove_operation
    : public Scene_item_operation
{
public:
    class Context
    {
    public:
        Selection_tool*                    selection_tool{nullptr};
        erhe::scene::Scene&                scene;
        erhe::scene::Mesh_layer&           layer;
        erhe::physics::IWorld&             physics_world;
        std::shared_ptr<erhe::scene::Mesh> mesh;
        std::shared_ptr<Node_physics>      node_physics;
        std::shared_ptr<erhe::scene::Node> parent;
        Mode                               mode;
    };

    explicit Mesh_insert_remove_operation(const Context& context);
    ~Mesh_insert_remove_operation        () override;

    // Implements IOperation
    void execute () const override;
    void undo    () const override;
    auto describe() const -> std::string override;

private:
    void execute(const Mode mode) const;

    Context                                         m_context;
    std::vector<std::shared_ptr<erhe::scene::Node>> m_selection_before;
    std::vector<std::shared_ptr<erhe::scene::Node>> m_selection_after;
};

class Light_insert_remove_operation
    : public Scene_item_operation
{
public:
    class Context
    {
    public:
        std::shared_ptr<Selection_tool>     selection_tool;
        erhe::scene::Light_layer&           layer;
        erhe::scene::Scene&                 scene;
        std::shared_ptr<erhe::scene::Light> light;
        std::shared_ptr<erhe::scene::Node>  parent;
        Mode                                mode;
    };

    explicit Light_insert_remove_operation(const Context& context);
    ~Light_insert_remove_operation        () override;

    void execute () const override;
    void undo    () const override;
    auto describe() const -> std::string override;

private:
    void execute(const Mode mode) const;

    Context                                         m_context;
    std::vector<std::shared_ptr<erhe::scene::Node>> m_selection_before;
    std::vector<std::shared_ptr<erhe::scene::Node>> m_selection_after;
};

}
