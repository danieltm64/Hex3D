#ifndef HEX3D_GUI_MODULE_HPP
#define HEX3D_GUI_MODULE_HPP

#include <hex3d/gui_module/config.hpp>
#include <hex3d/module.hpp>
#include <hex3d/application.hpp>

#include <string>
#include <boost/any.hpp>

#define HEX3D_GUI_MODULE_NAME "hex3d/gui_module"

namespace hex3d
{
    class application;

    class /*HEX3D_GUI_MODULE_DECL*/ gui_module : public module
    {
    public:
        class /*HEX3D_GUI_MODULE_DECL*/ window
        {
        public:
            window();

            std::wstring window_title();
            void set_window_title(const std::wstring& window_title);

            unsigned int client_area_width() const;
            unsigned int client_area_height() const;

            virtual bool initialize() = 0;
            bool is_ready() const;
            virtual int run() = 0;

            virtual boost::any native_handle_obj() const = 0;

        protected:
            std::wstring m_window_title;
            unsigned int m_client_area_width;
            unsigned int m_client_area_height;
            bool m_is_ready;
        };

        gui_module();

        // copy operations
        gui_module(const gui_module& other) = delete;
        gui_module& operator=(const gui_module& other) = delete;

        // move operations
        gui_module(gui_module&& other) = delete;
        gui_module& operator=(gui_module&& other) = delete;

        virtual bool initialize() override;
        virtual int run() override;
        virtual void update(float delta_seconds, float total_seconds) override {}
        virtual const char* name() override {return HEX3D_GUI_MODULE_NAME;}

        window* window_obj();

    protected:
        window* m_window;
    };

    // GUI_MODULE:

    gui_module::gui_module()
        : m_window(nullptr)
    {
    }

    bool gui_module::initialize()
    {
        m_is_ready = m_window->initialize();
        return m_is_ready;
    }

    int gui_module::run()
    {
        return m_window->run();
    }

    gui_module::window* gui_module::window_obj()
    {
        return m_window;
    }

    // WINDOW:

    gui_module::window::window()
        : m_is_ready(false)
    {
    }

    std::wstring gui_module::window::window_title()
    {
        return m_window_title;
    }

    void gui_module::window::set_window_title(const std::wstring& window_title)
    {
        m_window_title = window_title;
    }

    unsigned int gui_module::window::client_area_width() const
    {
        return m_client_area_width;
    }

    unsigned int gui_module::window::client_area_height() const
    {
        return m_client_area_height;
    }

    bool gui_module::window::is_ready() const
    {
        return m_is_ready;
    }
} // namespace hex3d

#define gui_module_obj (static_cast<hex3d::gui_module*>(application_obj->module_obj(HEX3D_GUI_MODULE_NAME)))

extern "C" HEX3D_GUI_MODULE_DECL hex3d::module* create_module_obj();

#endif // HEX3D_GUI_MODULE_HPP
