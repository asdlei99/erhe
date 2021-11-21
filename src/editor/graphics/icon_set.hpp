#pragma once

#include "erhe/components/component.hpp"

#include <imgui.h>
#include <glm/glm.hpp>

#include <filesystem>

namespace erhe::graphics
{
    class Texture;
}

namespace erhe::scene
{
    class Camera;
    class Light;
    class Mesh;
    class Node;
    enum class Light_type : unsigned int;
}

namespace editor {

class Icon_set
    : public erhe::components::Component
{
public:
    static constexpr std::string_view c_name{"Icon_set"};
    static constexpr uint32_t hash = compiletime_xxhash::xxh32(c_name.data(), c_name.size(), {});

    Icon_set(int icon_width = 16, int icon_height = 16, int row_count = 16, int column_count = 16);
    ~Icon_set() override;

    // Implements Component
    auto get_type_hash       () const -> uint32_t override { return hash; }
    void connect             () override;
    void initialize_component() override;

    auto load(const std::filesystem::path& path) -> ImVec2;
    auto uv1 (const ImVec2& uv0) const -> ImVec2;
    void icon(ImVec2 uv0, glm::vec4 tint_color = glm::vec4{1.0f}) const;

    std::shared_ptr<erhe::graphics::Texture> texture;

    void icon(const erhe::scene::Camera& camera) const;
    void icon(const erhe::scene::Light& light) const;
    void icon(const erhe::scene::Mesh& mesh) const;
    void icon(const erhe::scene::Node& node) const;

    auto get_icon(const erhe::scene::Light_type type) const -> const ImVec2;

    struct Icons
    {
        ImVec2 camera{};
        ImVec2 directional_light{};
        ImVec2 point_light{};
        ImVec2 spot_light{};
        ImVec2 mesh{};
        ImVec2 node{};
    };

    Icons icons;

private:
    int   m_icon_width{0};
    int   m_icon_height{0};
    int   m_row_count{0};
    int   m_column_count{0};
    int   m_row{0};
    int   m_column{0};
    float m_icon_uv_width{0.0f};
    float m_icon_uv_height{0.0f};
};

}
