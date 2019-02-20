#define HEX3D_DIRECT3D11_GRAPHICS_MODULE_SOURCE
#include <hex3d/direct3d11_graphics_module/direct3d11_graphics_module.hpp>
#include <hex3d/win32_gui_module/win32_gui_module.hpp>
#include <hex3d/application.hpp>

namespace hex3d
{
    direct3d11_graphics_module::direct3d11_graphics_module()
        : m_d3ddevice(nullptr)
        , m_immediate_context(nullptr)
        , m_swap_chain(nullptr)
        , m_render_target_view(nullptr)
        , m_depth_stencil_buffer(nullptr)
        , m_depth_stencil_view(nullptr)
    {
    }

    direct3d11_graphics_module::~direct3d11_graphics_module()
    {
        if (m_immediate_context)
            m_immediate_context->ClearState();
    }

    bool direct3d11_graphics_module::initialize()
    {
        if (!graphics_module::initialize())
            return false;
        m_is_ready = false;

        gui_module::window* window_locptr = gui_module_obj->window_obj();

        m_main_window_handle = boost::any_cast<win32_gui_module::window::native_handle>(window_locptr->native_handle_obj()).main_window_handle;
        unsigned int client_area_width = window_locptr->client_area_width();
        unsigned int client_area_height = window_locptr->client_area_height();

        D3D_FEATURE_LEVEL selected_feature_level;
        HRESULT result = D3D11CreateDevice(0, D3D_DRIVER_TYPE_HARDWARE, 0, 0, 0, 0, D3D11_SDK_VERSION, m_d3ddevice.GetAddressOf(), &selected_feature_level, m_immediate_context.GetAddressOf());

        if (FAILED(result))
            return false;

        DXGI_SWAP_CHAIN_DESC swap_chain_description;
        swap_chain_description.BufferCount = 1;
        swap_chain_description.BufferDesc.Width = client_area_width;
        swap_chain_description.BufferDesc.Height = client_area_height;
        swap_chain_description.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        swap_chain_description.BufferDesc.RefreshRate.Numerator = 60;
        swap_chain_description.BufferDesc.RefreshRate.Denominator = 1;
        swap_chain_description.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swap_chain_description.OutputWindow = m_main_window_handle;
        swap_chain_description.SampleDesc.Count = 1;
        swap_chain_description.SampleDesc.Quality = 0;
        swap_chain_description.Windowed = TRUE;
        swap_chain_description.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
        swap_chain_description.Flags = 0;

        ComPtr<IDXGIDevice> dxgi_device(nullptr);
        //result = m_d3ddevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(dxgi_device.GetAddressOf()));
        result = m_d3ddevice.As(&dxgi_device);
        if (FAILED(result))
        {
            if (m_immediate_context)
                m_immediate_context->ClearState();

            return false;
        }

        ComPtr<IDXGIAdapter> dxgi_adapter(nullptr);
        result = dxgi_device->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(dxgi_adapter.GetAddressOf()));
        if (FAILED(result))
        {
            if (m_immediate_context)
                m_immediate_context->ClearState();

            return false;
        }

        ComPtr<IDXGIFactory> dxgi_factory(nullptr);
        result = dxgi_adapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(dxgi_factory.GetAddressOf()));
        if (FAILED(result))
        {
            if (m_immediate_context)
                m_immediate_context->ClearState();

            return false;
        }

        result = dxgi_factory->CreateSwapChain(m_d3ddevice.Get(), &swap_chain_description, m_swap_chain.GetAddressOf());
        if (FAILED(result))
        {
            if (m_immediate_context)
                m_immediate_context->ClearState();

            return false;
        }

        ComPtr<ID3D11Texture2D> back_buffer(nullptr);
        result = m_swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(back_buffer.GetAddressOf()));
        if (FAILED(result))
        {
            if (m_immediate_context)
                m_immediate_context->ClearState();

            return false;
        }
        result = m_d3ddevice->CreateRenderTargetView(back_buffer.Get(), 0, m_render_target_view.GetAddressOf());
        if (FAILED(result))
        {
            if (m_immediate_context)
                m_immediate_context->ClearState();

            return false;
        }

        D3D11_TEXTURE2D_DESC depth_stencil_description;
        depth_stencil_description.Width = client_area_width;
        depth_stencil_description.Height = client_area_height;
        depth_stencil_description.MipLevels = 1;
        depth_stencil_description.ArraySize = 1;
        depth_stencil_description.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
        depth_stencil_description.SampleDesc.Count = 1;
        depth_stencil_description.SampleDesc.Quality = 0;
        depth_stencil_description.Usage = D3D11_USAGE_DEFAULT;
        depth_stencil_description.BindFlags = D3D11_BIND_DEPTH_STENCIL;
        depth_stencil_description.CPUAccessFlags = 0;
        depth_stencil_description.MiscFlags = 0;

        result = m_d3ddevice->CreateTexture2D(&depth_stencil_description, 0, m_depth_stencil_buffer.GetAddressOf());
        if (FAILED(result))
        {
            if (m_immediate_context)
                m_immediate_context->ClearState();

            return false;
        }
        result = m_d3ddevice->CreateDepthStencilView(m_depth_stencil_buffer.Get(), 0, m_depth_stencil_view.GetAddressOf());
        if (FAILED(result))
        {
            if (m_immediate_context)
                m_immediate_context->ClearState();

            return false;
        }

        m_immediate_context->OMSetRenderTargets(1, m_render_target_view.GetAddressOf(), m_depth_stencil_view.Get());

        m_viewport;
        m_viewport.Width = static_cast<float>(client_area_width);
        m_viewport.Height = static_cast<float>(client_area_height);
        m_viewport.MinDepth = 0.0f;
        m_viewport.MaxDepth = 1.0f;
        m_viewport.TopLeftX = 0;
        m_viewport.TopLeftY = 0;
        m_immediate_context->RSSetViewports(1, &m_viewport);

        m_clear_color[0] = 0.0f;
        m_clear_color[1] = 0.0f;
        m_clear_color[2] = 0.0f;
        m_clear_color[3] = 0.0f;

        core_module::entity_graph* entity_graph_locptr = core_module_obj->entity_graph_obj();
        entity_graph_locptr->register_component_factory_function("cube", cube_comp::create);
        entity_graph_locptr->register_pass(HEX3D_DIRECT3D11_GRAPHICS_MODULE_NAME,
                                           std::bind(&direct3d11_graphics_module::start_pass, this, std::placeholders::_1),
                                           std::bind(&direct3d11_graphics_module::end_pass, this, std::placeholders::_1));

        m_is_ready = true;
        return true;
    }

    void direct3d11_graphics_module::update(float delta_seconds, float total_seconds)
    {
    }

    void direct3d11_graphics_module::start_pass(core_module::pass_event* ev)
    {
        float total_seconds = ev->total_seconds();
        m_clear_color[0] = (sinf(total_seconds) + 1.0f) * 0.5f;
        m_clear_color[1] = (sinf(total_seconds + 2.0f) + 1.0f) * 0.5f;
        m_clear_color[2] = (sinf(total_seconds + 4.0f) + 1.0f) * 0.5f;
        m_clear_color[3] = 1.0f;
        m_immediate_context->ClearRenderTargetView(m_render_target_view.Get(), m_clear_color);
        m_immediate_context->ClearDepthStencilView(m_depth_stencil_view.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    }

    void direct3d11_graphics_module::end_pass(core_module::pass_event* ev)
    {
        m_swap_chain->Present(0, 0);
        gui_module_obj->window_obj()->set_window_title(L"Hex3D - Total Time: " + std::to_wstring(ev->total_seconds()));
    }
} // namespace hex3d

hex3d::module* create_module_obj()
{
    hex3d::direct3d11_graphics_module* module_obj = new hex3d::direct3d11_graphics_module;
    module_obj->initialize();
    return module_obj;
}
