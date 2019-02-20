#define HEX3D_OPENGL_GRAPHICS_MODULE_SOURCE
#include <hex3d/opengl_graphics_module/opengl_graphics_module.hpp>

#if defined(BOOST_OS_LINUX_AVAILABLE)
#   include <hex3d/x11_gui_module/x11_gui_module.hpp>
#endif

namespace hex3d
{
    opengl_graphics_module::opengl_graphics_module()
    {
    }

    opengl_graphics_module::~opengl_graphics_module()
    {
        glXDestroyContext(m_display, m_opengl_context);
    }

    bool opengl_graphics_module::initialize()
    {
        if (!graphics_module::initialize())
            return false;
        m_is_ready = false;

        gui_module::window* window_locptr = gui_module_obj->window_obj();

        x11_gui_module::window::native_handle window_native_handle = boost::any_cast<x11_gui_module::window::native_handle>(window_locptr->native_handle_obj());
        m_display = window_native_handle.display;
        m_window = window_native_handle.window;
        XVisualInfo* visual_info = window_native_handle.visual_info;
        unsigned int cient_area_width = window_locptr->client_area_width();
        unsigned int client_area_height = window_locptr->client_area_height();

        m_opengl_context = glXCreateContext(m_display, visual_info, NULL, GL_TRUE);

        if (glXMakeCurrent(m_display, m_window, m_opengl_context) == False)
            return false;

        GLenum result = glewInit();
        if (result != GLEW_OK)
            return false;

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        //glFrontFace(GL_CCW);

        m_clear_color[0] = 0.0f;
        m_clear_color[1] = 0.0f;
        m_clear_color[2] = 0.0f;
        m_clear_color[3] = 0.0f;

        core_module::entity_graph* entity_graph_locptr = core_module_obj->entity_graph_obj();
        entity_graph_locptr->register_component_factory_function("cube", cube_comp::create);
        entity_graph_locptr->register_pass(HEX3D_OPENGL_GRAPHICS_MODULE_NAME,
                                           std::bind(&opengl_graphics_module::start_pass, this, std::placeholders::_1),
                                           std::bind(&opengl_graphics_module::end_pass, this, std::placeholders::_1));

        m_is_ready = true;
        return true;
    }

    void opengl_graphics_module::update(float delta_seconds, float total_seconds)
    {
    }

    void opengl_graphics_module::start_pass(core_module::pass_event *ev)
    {
        float total_seconds = ev->total_seconds();
        m_clear_color[0] = (sinf(total_seconds) + 1.0f) * 0.5f;
        m_clear_color[1] = (sinf(total_seconds + 2.0f) + 1.0f) * 0.5f;
        m_clear_color[2] = (sinf(total_seconds + 4.0f) + 1.0f) * 0.5f;
        m_clear_color[3] = 1.0f;
        glClearColor(m_clear_color[0], m_clear_color[1], m_clear_color[2], m_clear_color[3]);
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);
    }

    void opengl_graphics_module::end_pass(core_module::pass_event *ev)
    {
        glXSwapBuffers(m_display, m_window);
        gui_module_obj->window_obj()->set_window_title(L"Hex3D - Total Time: " + std::to_wstring(ev->total_seconds()));
    }

    GLuint opengl_graphics_module::compile_shader_from_file(const char* file_name, shader_type_t shader_type, result_code_t& result_code)
    {
        std::streamoff file_length;
        char* file_content = nullptr;
        std::ifstream file(file_name, std::ifstream::ate);
        if (file.is_open())
        {
            file_length = file.tellg();
            file.seekg(0, std::ios_base::beg);
            if (file_length > 0)
            {
                file_content = new char[file_length];
                file.read(file_content, file_length);
            }
            file.close();
        }
        if (file_content == nullptr)
        {
            result_code = result_code_t::file_could_not_be_read;
            return 0;
        }
        GLuint shader_object = glCreateShader(shader_type == shader_type_t::vertex_shader ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);
        if (shader_object == 0)
        {
            result_code = result_code_t::shader_creation_failed;
            return 0;
        }
        glShaderSource(shader_object, 1, (const GLchar**)&file_content, NULL);
        delete [] file_content;
        glCompileShader(shader_object);
        GLint success;
        glGetShaderiv(shader_object, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            result_code = result_code_t::shader_compilation_failed;
            return 0;
        }
        result_code = result_code_t::success;
        return shader_object;
    }
} // namespace hex3d

hex3d::module* create_module_obj()
{
    hex3d::opengl_graphics_module* module_obj = new hex3d::opengl_graphics_module;
    module_obj->initialize();
    return module_obj;
}
