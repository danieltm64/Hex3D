#ifndef HEX3D_X11_GUI_MODULE_HPP
#define HEX3D_X11_GUI_MODULE_HPP

#include <hex3d/x11_gui_module/config.hpp>
#include <hex3d/gui_module/gui_module.hpp>
#include <hex3d/application.hpp>

#include <iostream>

#include <GL/glx.h>
#include <string>

#define HEX3D_X11_GUI_MODULE_NAME "hex3d/x11_gui_module"

namespace hex3d
{
    class application;

    class HEX3D_X11_GUI_MODULE_DECL x11_gui_module : public gui_module
    {
    public:
        class HEX3D_X11_GUI_MODULE_DECL window : public gui_module::window
        {
        public:
            struct native_handle
            {
                Display* display;
                Window window;
                XVisualInfo* visual_info;
            };

            window() = default;

            virtual bool initialize() override;
            virtual int run() override;

            virtual boost::any native_handle_obj() const override;

        private:
            Display* m_display;
            Window m_window;
            XVisualInfo* m_visual_info;
        };

        x11_gui_module();

        // copy operations
        x11_gui_module(const x11_gui_module& other) = delete;
        x11_gui_module& operator=(const x11_gui_module& other) = delete;

        // move operations
        x11_gui_module(x11_gui_module&& other) = delete;
        x11_gui_module& operator=(x11_gui_module&& other) = delete;

        virtual bool initialize() override;
        virtual int run() override;
        virtual void update(float delta_seconds, float total_seconds) override {}
        virtual const char* name() override {return HEX3D_X11_GUI_MODULE_NAME;}
    };
} // namespace hex3d

#define gui_module_obj (static_cast<hex3d::x11_gui_module*>(application_obj->module_obj(HEX3D_X11_GUI_MODULE_NAME)))

extern "C" HEX3D_X11_GUI_MODULE_DECL hex3d::module* create_module_obj();

#endif // HEX3D_X11_GUI_MODULE_HPP
