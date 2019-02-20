#define HEX3D_OPENGL_GRAPHICS_MODULE_SOURCE
#include <hex3d/opengl_graphics_module/opengl_graphics_module.hpp>

namespace hex3d
{
    GLuint opengl_graphics_module::cube_comp::m_shader_program;
    GLuint opengl_graphics_module::cube_comp::m_vertex_buffer_object;
    GLuint opengl_graphics_module::cube_comp::m_index_buffer_object;
    bool opengl_graphics_module::cube_comp::m_initialized;

    opengl_graphics_module::cube_comp::cube_comp(core_module::entity* owner)
        : graphics_module::cube_comp(owner)
    {
        initialize();
    }

    opengl_graphics_module::cube_comp::~cube_comp()
    {
    }

    bool opengl_graphics_module::cube_comp::initialize()
    {
        if (m_initialized)
            return false;

        opengl_graphics_module* graphics_module_locptr = graphics_module_obj;

        result_code_t result_code;
        GLuint vertex_shader = opengl_graphics_module::compile_shader_from_file("data/vertex_shader.glsl", shader_type_t::vertex_shader, result_code);
        if (result_code != result_code_t::success)
            return false;

        GLuint fragment_shader = opengl_graphics_module::compile_shader_from_file("data/fragment_shader.glsl", shader_type_t::fragment_shader, result_code);
        if (result_code != result_code_t::success)
            return false;

        m_shader_program = glCreateProgram();
        glAttachShader(m_shader_program, vertex_shader);
        glAttachShader(m_shader_program, fragment_shader);
        GLint success;
        glLinkProgram(m_shader_program);
        glGetProgramiv(m_shader_program, GL_LINK_STATUS, &success);
        if (!success)
            return false;

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

        glGenBuffers(1, &m_vertex_buffer_object);
        glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_object);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertex) * 8, vertices, GL_STATIC_DRAW);

        glGenBuffers(1, &m_index_buffer_object);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer_object);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 12 * 3, indices, GL_STATIC_DRAW);
    }

    opengl_graphics_module::cube_comp* opengl_graphics_module::cube_comp::create()
    {
        return new cube_comp;
    }

    void opengl_graphics_module::cube_comp::update(core_module::pass_event* pass_ev)
    {
        if (pass_ev->name() != HEX3D_OPENGL_GRAPHICS_MODULE_NAME)
            return;

        core_module::transform_comp* transform_ptr = owner()->get_component<core_module::transform_comp>();
        if (transform_ptr)
        {
            opengl_graphics_module* graphics_module_locptr = graphics_module_obj;

            glUseProgram(m_shader_program);
            glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_object);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer_object);

            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, static_cast<void*>(0));
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, static_cast<void*>(0));

            core_module::transform transform = transform_ptr->global_transform();
            transform.rotation() = core_module::vector3d(0.0f, pass_ev->total_seconds(), 0.0f);
            //glUniformMatrix4fv(glGetUniformLocation(m_shader_program, "WVP"), 1, GL_FALSE, &(transform.world_matrix() * graphics_module_locptr->main_camera()->view_matrix() * graphics_module_locptr->main_camera()->projection_matrix()).elements[0][0]);
            core_module::matrix4x4 mat = transform.world_matrix() * graphics_module_locptr->main_camera()->view_matrix() * graphics_module_locptr->main_camera()->projection_matrix();
            mat = mat.transposed();
            glUniformMatrix4fv(glGetUniformLocation(m_shader_program, "WVP"), 1, GL_FALSE, &mat.elements[0][0]);

            glDrawElements(GL_TRIANGLES, 12 * 3, GL_UNSIGNED_INT, (void*)0);
        }
    }
} // namespace hex3d
