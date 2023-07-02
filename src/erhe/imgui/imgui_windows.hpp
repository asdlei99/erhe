#pragma once

#include "erhe/toolkit/window_event_handler.hpp"

#include <functional>
#include <memory>
#include <mutex>
#include <vector>

namespace erhe::rendergraph
{
    class Rendergraph;
}

namespace erhe::toolkit
{
    class Context_window;
}

namespace erhe::imgui
{

class Imgui_window;
class Imgui_viewport;
class Imgui_renderer;
class Window_imgui_viewport;

class Imgui_windows
    : public erhe::toolkit::Window_event_handler
{
public:
    Imgui_windows(
        Imgui_renderer&                 imgui_renderer,
        erhe::toolkit::Context_window*  context_window,
        erhe::rendergraph::Rendergraph& rendergraph
    );

    // Public API
    void lock_mutex               ();
    void unlock_mutex             ();
    void queue                    (std::function<void()>&& operation);
    void flush_queue              ();
    void register_imgui_viewport  (Imgui_viewport* viewport);
    void unregister_imgui_viewport(Imgui_viewport* viewport);
    void register_imgui_window    (Imgui_window* window);
    void register_imgui_window    (Imgui_window* window, bool visible);
    void make_current             (const Imgui_viewport* imgui_viewport);
    void imgui_windows            ();
    void window_menu              (Imgui_viewport* imgui_viewport);
    auto get_windows              () -> std::vector<Imgui_window*>&;

    [[nodiscard]] auto get_window_viewport  () -> std::shared_ptr<Window_imgui_viewport>;
    [[nodiscard]] auto want_capture_keyboard() const -> bool;
    [[nodiscard]] auto want_capture_mouse   () const -> bool;

    // Implements erhe::toolkit::Window_event_handler
    // Forwards events to each window
    auto on_key         (signed int keycode, uint32_t modifier_mask, bool pressed) -> bool override;
    auto on_char        (unsigned int codepoint) -> bool                                   override;
    auto on_focus       (int focused) -> bool                                              override;
    auto on_cursor_enter(int entered) -> bool                                              override;
    auto on_mouse_move  (float x, float y) -> bool                                         override;
    auto on_mouse_button(uint32_t button, bool pressed) -> bool                            override;
    auto on_mouse_wheel (float x, float y) -> bool                                         override;

private:
    std::recursive_mutex                   m_mutex;
    bool                                   m_iterating{false};
    std::vector<Imgui_viewport*>           m_imgui_viewports;
    std::vector<Imgui_window*>             m_imgui_windows;
    std::mutex                             m_queued_operations_mutex;
    std::vector<std::function<void()>>     m_queued_operations;
    const Imgui_viewport*                  m_current_viewport{nullptr}; // current context
    erhe::rendergraph::Rendergraph&        m_rendergraph;

    std::shared_ptr<Window_imgui_viewport> m_window_imgui_viewport;
};

} // namespace erhe::imgui