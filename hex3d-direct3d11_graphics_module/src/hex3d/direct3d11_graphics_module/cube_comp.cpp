#define HEX3D_DIRECT3D11_GRAPHICS_MODULE_SOURCE
#include <hex3d/direct3d11_graphics_module/direct3d11_graphics_module.hpp>

namespace hex3d
{
    bool direct3d11_graphics_module::cube_comp::m_initialized = false;
    ComPtr<ID3D11InputLayout> direct3d11_graphics_module::cube_comp::m_input_layout;
    ComPtr<ID3D11VertexShader> direct3d11_graphics_module::cube_comp::m_vertex_shader;
    ComPtr<ID3D11PixelShader> direct3d11_graphics_module::cube_comp::m_pixel_shader;
    ComPtr<ID3D11Buffer> direct3d11_graphics_module::cube_comp::m_vertex_buffer;
    ComPtr<ID3D11Buffer> direct3d11_graphics_module::cube_comp::m_index_buffer;
    ComPtr<ID3D11Buffer> direct3d11_graphics_module::cube_comp::m_cb_per_object_buffer;

    direct3d11_graphics_module::cube_comp::cube_comp(core_module::entity* owner)
        : graphics_module::cube_comp(owner)
    {
        initialize();
    }

    direct3d11_graphics_module::cube_comp::~cube_comp()
    {
    }

    bool direct3d11_graphics_module::cube_comp::initialize()
    {
        if (m_initialized)
            return false;

        direct3d11_graphics_module* graphics_module_locptr = graphics_module_obj;

        ComPtr<ID3D10Blob> vertex_shader_blob, pixel_shader_blob;
        HRESULT result;
        result = D3DCompileFromFile(L"data/shaders.hlsl", nullptr, nullptr,
            "VShader", "vs_4_0", 0, 0, vertex_shader_blob.GetAddressOf(), nullptr);
        if (FAILED(result))
            return false;
        result = D3DCompileFromFile(L"data/shaders.hlsl", nullptr, nullptr,
            "PShader", "ps_4_0", 0, 0, pixel_shader_blob.GetAddressOf(), nullptr);
        if (FAILED(result))
            return false;

        graphics_module_locptr->m_d3ddevice->CreateVertexShader(vertex_shader_blob->GetBufferPointer(), vertex_shader_blob->GetBufferSize(), 0, m_vertex_shader.GetAddressOf());
        graphics_module_locptr->m_d3ddevice->CreatePixelShader(pixel_shader_blob->GetBufferPointer(), pixel_shader_blob->GetBufferSize(), 0, m_pixel_shader.GetAddressOf());

        D3D11_INPUT_ELEMENT_DESC input_element_descriptions[] =
        {
            {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
            {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
        };

        graphics_module_locptr->m_d3ddevice->CreateInputLayout(input_element_descriptions, 2, vertex_shader_blob->GetBufferPointer(), vertex_shader_blob->GetBufferSize(), m_input_layout.GetAddressOf());

        vertex vertices[] =
        {
            {core_module::vector3d(-1.0f, -1.0f, -1.0f), core_module::vector4d(1.0f, 0.0f, 0.0f, 1.0f)},
            {core_module::vector3d(-1.0f, +1.0f, -1.0f), core_module::vector4d(0.0f, 1.0f, 0.0f, 1.0f)},
            {core_module::vector3d(+1.0f, +1.0f, -1.0f), core_module::vector4d(0.0f, 0.0f, 1.0f, 1.0f)},
            {core_module::vector3d(+1.0f, -1.0f, -1.0f), core_module::vector4d(1.0f, 1.0f, 0.0f, 1.0f)},
            {core_module::vector3d(-1.0f, -1.0f, +1.0f), core_module::vector4d(0.0f, 1.0f, 1.0f, 1.0f)},
            {core_module::vector3d(-1.0f, +1.0f, +1.0f), core_module::vector4d(1.0f, 1.0f, 1.0f, 1.0f)},
            {core_module::vector3d(+1.0f, +1.0f, +1.0f), core_module::vector4d(1.0f, 0.0f, 1.0f, 1.0f)},
            {core_module::vector3d(+1.0f, -1.0f, +1.0f), core_module::vector4d(1.0f, 0.0f, 0.0f, 1.0f)}
        };

        unsigned int indices[] =
        {
            // front face
            0, 1, 2,
            0, 2, 3,

            // back face
            4, 6, 5,
            4, 7, 6,

            // left face
            4, 5, 1,
            4, 1, 0,

            // right face
            3, 2, 6,
            3, 6, 7,

            // top face
            1, 5, 6,
            1, 6, 2,

            // bottom face
            4, 0, 3,
            4, 3, 7
        };

        D3D11_BUFFER_DESC index_buffer_description;
        index_buffer_description.ByteWidth = sizeof(unsigned int) * 12 * 3;
        index_buffer_description.Usage = D3D11_USAGE_DEFAULT;
        index_buffer_description.BindFlags = D3D11_BIND_INDEX_BUFFER;
        index_buffer_description.CPUAccessFlags = 0;
        index_buffer_description.MiscFlags = 0;
        index_buffer_description.StructureByteStride = 0;

        D3D11_SUBRESOURCE_DATA subresource_data;
        subresource_data.pSysMem = indices;

        graphics_module_locptr->m_d3ddevice->CreateBuffer(&index_buffer_description, &subresource_data, m_index_buffer.GetAddressOf());

        D3D11_BUFFER_DESC vertex_buffer_description;
        vertex_buffer_description.ByteWidth = sizeof(vertex) * 8;
        vertex_buffer_description.Usage = D3D11_USAGE_DYNAMIC;
        vertex_buffer_description.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        vertex_buffer_description.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        vertex_buffer_description.MiscFlags = 0;
        vertex_buffer_description.StructureByteStride = 0;

        graphics_module_locptr->m_d3ddevice->CreateBuffer(&vertex_buffer_description, 0, m_vertex_buffer.GetAddressOf());

        D3D11_MAPPED_SUBRESOURCE mapped_subresource;
        graphics_module_locptr->m_immediate_context->Map(m_vertex_buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_subresource);
        memcpy(mapped_subresource.pData, vertices, sizeof(vertices));
        graphics_module_locptr->m_immediate_context->Unmap(m_vertex_buffer.Get(), 0);

        D3D11_BUFFER_DESC cb_buffer_description;

        cb_buffer_description.ByteWidth = sizeof(cb_per_object);
        cb_buffer_description.Usage = D3D11_USAGE_DEFAULT;
        cb_buffer_description.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        cb_buffer_description.CPUAccessFlags = 0;
        cb_buffer_description.MiscFlags = 0;
        cb_buffer_description.StructureByteStride = 0;

        graphics_module_locptr->m_d3ddevice->CreateBuffer(&cb_buffer_description, 0, m_cb_per_object_buffer.GetAddressOf());

        m_initialized = true;
        return true;
    }

    direct3d11_graphics_module::cube_comp* direct3d11_graphics_module::cube_comp::create()
    {
        return new cube_comp;
    }

    void direct3d11_graphics_module::cube_comp::update(core_module::pass_event* pass_ev)
    {
        if (pass_ev->name() != HEX3D_DIRECT3D11_GRAPHICS_MODULE_NAME)
            return;

        core_module::transform_comp* transform_ptr = owner()->get_component<core_module::transform_comp>();
        if (transform_ptr)
        {
            direct3d11_graphics_module* graphics_module_locptr = graphics_module_obj;
            graphics_module_locptr->m_immediate_context->VSSetShader(m_vertex_shader.Get(), 0, 0);
            graphics_module_locptr->m_immediate_context->PSSetShader(m_pixel_shader.Get(), 0, 0);
            graphics_module_locptr->m_immediate_context->IASetInputLayout(m_input_layout.Get());

            unsigned int stride = sizeof(vertex);
            unsigned int offset = 0;

            graphics_module_locptr->m_immediate_context->IASetVertexBuffers(0, 1, m_vertex_buffer.GetAddressOf(), &stride, &offset);
            graphics_module_locptr->m_immediate_context->IASetIndexBuffer(m_index_buffer.Get(), DXGI_FORMAT_R32_UINT, 0);
            graphics_module_locptr->m_immediate_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

            core_module::transform transform = transform_ptr->global_transform();
            transform.rotation() = core_module::vector3d(0.0f, pass_ev->total_seconds(), 0.0f);
            // TODO: Make sure matrix4x4_r also works, left-handedness is preferred. Perhaps there's a bug with the camera's matrix generation (remember that OpenGL tutorial?)
            m_cb_per_obj.WVP = transform.world_matrix() * graphics_module_locptr->main_camera()->view_matrix() * graphics_module_locptr->main_camera()->projection_matrix();

            graphics_module_locptr->m_immediate_context->UpdateSubresource(m_cb_per_object_buffer.Get(), 0, 0, &m_cb_per_obj, 0, 0);
            graphics_module_locptr->m_immediate_context->VSSetConstantBuffers(0, 1, m_cb_per_object_buffer.GetAddressOf());
            graphics_module_locptr->m_immediate_context->DrawIndexed(36, 0, 0);
        }
    }
} // namespace hex3d
