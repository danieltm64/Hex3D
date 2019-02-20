#ifndef HEX3D_OPENGL_GRAPHICS_MODULE_HPP
#define HEX3D_OPENGL_GRAPHICS_MODULE_HPP

#include <hex3d/opengl_graphics_module/config.hpp>
#include <hex3d/graphics_module/graphics_module.hpp>
#include <GL/glew.h>
#include <GL/gl.h>

#if defined(BOOST_OS_LINUX_AVAILABLE)
#   include <GL/glx.h>
#endif

#include <string>

#define HEX3D_OPENGL_GRAPHICS_MODULE_NAME "hex3d/opengl_graphics_module"

namespace hex3d
{
    class HEX3D_OPENGL_GRAPHICS_MODULE_DECL opengl_graphics_module : public graphics_module
    {
    public:
        opengl_graphics_module();

        // copy operations
        opengl_graphics_module(const opengl_graphics_module& other) = delete;
        opengl_graphics_module& operator=(const opengl_graphics_module& other) = delete;

        // move operations
        opengl_graphics_module(opengl_graphics_module&& other) = delete;
        opengl_graphics_module& operator=(opengl_graphics_module&& other) = delete;

        virtual ~opengl_graphics_module();

        virtual bool initialize() override;
        virtual int run() override {return 0;}
        virtual void update(float delta_seconds, float total_seconds) override;
        virtual const char* name() override {return HEX3D_OPENGL_GRAPHICS_MODULE_NAME;}

        class HEX3D_OPENGL_GRAPHICS_MODULE_DECL cube_comp : public graphics_module::cube_comp
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

            static GLuint m_shader_program;
            static GLuint m_vertex_buffer_object;
            static GLuint m_index_buffer_object;

            static bool m_initialized;
        };

    private:
        friend class cube_comp;

        enum class shader_type_t {
            vertex_shader,
            fragment_shader
        };

        enum class result_code_t {
            success,
            file_could_not_be_read,
            shader_creation_failed,
            shader_compilation_failed
        };

        void start_pass(core_module::pass_event *ev);
        void end_pass(core_module::pass_event *ev);

        static GLuint compile_shader_from_file(const char* file_name, shader_type_t shader_type, result_code_t& result_code);

        Display* m_display;
        Window m_window;
        GLXContext m_opengl_context;
        float m_clear_color[4];
    };
} // namespace hex3d

#define graphics_module_obj (static_cast<hex3d::opengl_graphics_module*>(application_obj->module_obj(HEX3D_OPENGL_GRAPHICS_MODULE_NAME)))

extern "C" HEX3D_OPENGL_GRAPHICS_MODULE_DECL hex3d::module* create_module_obj();

#endif // HEX3D_OPENGL_GRAPHICS_MODULE_HPP
