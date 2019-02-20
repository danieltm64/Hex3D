#ifndef HEX3D_WIN32_GUI_MODULE_HPP
#define HEX3D_WIN32_GUI_MODULE_HPP

#include <hex3d/win32_gui_module/config.hpp>
#include <hex3d/gui_module/gui_module.hpp>
#include <hex3d/application.hpp>

#include <iostream>

#include <Windows.h>
#include <string>

#define HEX3D_WIN32_GUI_MODULE_NAME "hex3d/win32_gui_module"

namespace hex3d
{
    class application;

    class HEX3D_WIN32_GUI_MODULE_DECL win32_gui_module : public gui_module
    {
    public:
        class HEX3D_WIN32_GUI_MODULE_DECL window : public gui_module::window
        {
        public:
            struct native_handle
            {
                HINSTANCE application_instance_handle;
                HWND main_window_handle;
                HDC device_context;
            };

            window() = default;

            virtual bool initialize() override;
            virtual int run() override;

            virtual boost::any native_handle_obj() const override;

        protected:
            virtual LRESULT window_procedure(HWND window_handle, UINT message, WPARAM w_param, LPARAM l_param);
            friend LRESULT CALLBACK window_procedure(HWND window_handle, UINT message, WPARAM w_param, LPARAM l_param);

        private:
            HINSTANCE m_application_instance_handle;
            LPTSTR m_command_line;
            int m_show_command;
            HWND m_main_window_handle;
            LPCSTR m_window_class_name;
            HDC m_device_context;
        };

        win32_gui_module();

        // copy operations
        win32_gui_module(const win32_gui_module& other) = delete;
        win32_gui_module& operator=(const win32_gui_module& other) = delete;

        // move operations
        win32_gui_module(win32_gui_module&& other) = delete;
        win32_gui_module& operator=(win32_gui_module&& other) = delete;

        virtual bool initialize() override;
        virtual int run() override;
        virtual void update(float delta_seconds, float total_seconds) override {}
        virtual const char* name() override {return HEX3D_WIN32_GUI_MODULE_NAME;}
    };
} // namespace hex3d

#define gui_module_obj (static_cast<hex3d::win32_gui_module*>(application_obj->module_obj(HEX3D_WIN32_GUI_MODULE_NAME)))

extern "C" HEX3D_WIN32_GUI_MODULE_DECL hex3d::module* create_module_obj();

#endif // HEX3D_WIN32_GUI_MODULE_HPP
