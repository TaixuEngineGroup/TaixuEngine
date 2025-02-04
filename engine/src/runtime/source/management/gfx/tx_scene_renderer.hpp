//
// Created by xmmmmmovo on 1/7/2024.
//

#pragma once

#include "taixu/common/designs/noncopyable.hpp"
#include "taixu/gameplay/gui/window.hpp"

#include "common/hal/tx_string.hpp"
#include "common/math/color.hpp"
#include "management/gfx/shaders/shader_manager.hpp"
#include "management/gfx/tx_context.hpp"
#include "tx_command_queue.hpp"

#ifdef USE_VULKAN
    #include "platform/vulkan/vk_context.hpp"
#endif

namespace taixu {

class Scene;

enum class ImguiComponentType : std::uint8_t { WIDGET, MENUBAR };

struct ImGuiComponentInfo {
    using ImGuiComponentCallbackT = std::function<void()>;

    tx_string_view          name{};
    ImguiComponentType      component_type{};
    ImGuiComponentCallbackT update_func{nullptr};
    ImGuiComponentCallbackT end_call_back{nullptr};
    ImGuiWindowFlags        flags{0};
    bool*                   open{nullptr};
};

struct ImguiStyleGroup {
    Color background{0.0f, 0.0f, 0.0f, 0.0f};
    Color foreground{0.0f, 0.0f, 0.0f, 0.0f};
    Color text{0.0f, 0.0f, 0.0f, 0.0f};
    Color text_background{0.0f, 0.0f, 0.0f, 0.0f};
    Color highlight_primary{0.0f, 0.0f, 0.0f, 0.0f};
    Color hover_primary{0.0f, 0.0f, 0.0f, 0.0f};
    Color highlight_secondary{0.0f, 0.0f, 0.0f, 0.0f};
    Color hover_secondary{0.0f, 0.0f, 0.0f, 0.0f};
    Color modal_dim{0.0f, 0.0f, 0.0f, 0.0f};
};

class TXSceneRenderer final : public Noncopyable {
private:
    /**
     * Graphics variables
     */

    /**
     * @brief Graphics Context
     *
     */
    pro::proxy<TXGFXProxy> _context{};
    /**
     * @brief Shader manager
     *
     */
    TXShaderModuleManager  _shader_module_manager{};
    /**
     * @brief Command Queue for rendering
     *
     */
    TXCommandQueue         _command_queue{};

    /**
     * Imgui variables
     *
     */

    /**
     * @brief ImGui io接口
     **/
    ImGuiIO*    _io{nullptr};
    /**
     * @brief ImGui style
     */
    ImGuiStyle* _style{nullptr};

    std::function<void()> _imgui_update{nullptr};
    bool                  _enable_imgui{true};

    const Window* _window{nullptr};

public:
    void init(Window* window, RenderAPI render_api);
    void update(float delta_time, Scene* scene);
    void fixedUpdate(float delta_time);
    void destroy();

    void enableImgui(const std::function<void()>& update_func);
    void disableImgui();

private:
    void loadFont(DPIScale const& dpi_scale) const;
    void loadStyle(DPIScale const& dpi_scale);
    void initImgui(const Window* window);
    void imguiUpdate();
    void imguiDestroy();

protected:
    void updateScene(float delta_time, Scene* scene);

    /**
     * @brief 初始化图形API
     *
     * @param window GLFW窗口
     */
    void initForGraphicsAPI(Window* window, RenderAPI render_api);

    void clearWindow();
    void presentToWindow();

    void destroyGraphicsAPI();
};

}// namespace taixu
