#ifndef DIRECT3D11_GRAPHICS_MODULE_HPP
#define DIRECT3D11_GRAPHICS_MODULE_HPP

#include <hex3d/direct3d11_graphics_module/config.hpp>
#include <hex3d/graphics_module/graphics_module.hpp>
#include <Windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl.h>
#include <string>
#include <vector>

#define HEX3D_DIRECT3D11_GRAPHICS_MODULE_NAME "hex3d/direct3d11_graphics_module"

namespace hex3d
{
    using Microsoft::WRL::ComPtr;

    class HEX3D_DIRECT3D11_GRAPHICS_MODULE_DECL direct3d11_graphics_module : public graphics_module
    {
    public:
        direct3d11_graphics_module();

        // copy operations
        direct3d11_graphics_module(const direct3d11_graphics_module& other) = delete;
        direct3d11_graphics_module& operator=(const direct3d11_graphics_module& other) = delete;

        // move operations
        direct3d11_graphics_module(direct3d11_graphics_module&& other) = delete;
        direct3d11_graphics_module& operator=(direct3d11_graphics_module&& other) = delete;

        virtual ~direct3d11_graphics_module();

        virtual bool initialize() override;
        virtual int run() override {return 0;}
        virtual void update(float delta_seconds, float total_seconds) override;
        virtual const char* name() override {return HEX3D_DIRECT3D11_GRAPHICS_MODULE_NAME;}

        class HEX3D_DIRECT3D11_GRAPHICS_MODULE_DECL cube_comp : public graphics_module::cube_comp
        {
        public:
            cube_comp(core_module::entity* owner = nullptr);
            virtual ~cube_comp();

            static bool initialize();
            static cube_comp* create();

            virtual void update(core_module::pass_event* pass_ev) override;

        private:
            class vertex
            {
            public:
                core_module::vector3d position;
                core_module::vector4d color;
            };

            struct cb_per_object
            {
                core_module::matrix4x4 WVP;
            };

            static bool m_initialized;
            static ComPtr<ID3D11InputLayout> m_input_layout;
            static ComPtr<ID3D11VertexShader> m_vertex_shader;
            static ComPtr<ID3D11PixelShader> m_pixel_shader;
            static ComPtr<ID3D11Buffer> m_vertex_buffer;
            static ComPtr<ID3D11Buffer> m_index_buffer;
            static ComPtr<ID3D11Buffer> m_cb_per_object_buffer;
            cb_per_object m_cb_per_obj;
        };

    private:
        void start_pass(core_module::pass_event *ev);
        void end_pass(core_module::pass_event *ev);

        HWND m_main_window_handle;
        ComPtr<ID3D11Device> m_d3ddevice;
        ComPtr<ID3D11DeviceContext> m_immediate_context;
        ComPtr<IDXGISwapChain> m_swap_chain;
        ComPtr<ID3D11RenderTargetView> m_render_target_view;
        ComPtr<ID3D11Texture2D> m_depth_stencil_buffer;
        ComPtr<ID3D11DepthStencilView> m_depth_stencil_view;
        D3D11_VIEWPORT m_viewport;
        float m_clear_color[4];
    };
} // namespace hex3d

#define graphics_module_obj (static_cast<hex3d::direct3d11_graphics_module*>(application_obj->module_obj(HEX3D_DIRECT3D11_GRAPHICS_MODULE_NAME)))

extern "C" HEX3D_DIRECT3D11_GRAPHICS_MODULE_DECL hex3d::module* create_module_obj();

#endif // DIRECT3D11_GRAPHICS_MODULE_HPP
