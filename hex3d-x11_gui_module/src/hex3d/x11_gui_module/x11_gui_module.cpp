#define HEX3D_X11_GUI_MODULE_SOURCE
#include <hex3d/x11_gui_module/x11_gui_module.hpp>
#include <chrono>

namespace hex3d
{
    // X11_GUI_MODULE:

    x11_gui_module::x11_gui_module()
    {
        m_window = new x11_gui_module::window;
    }

    bool x11_gui_module::initialize()
    {
        m_is_ready = m_window->initialize();
        return m_is_ready;
    }

    int x11_gui_module::run()
    {
        return m_window->run();
    }

    // WINDOW:

    bool x11_gui_module::window::initialize()
    {
        m_display = XOpenDisplay(NULL);
        if (m_display == NULL)
        {
            return false;
        }

        Window root_window = DefaultRootWindow(m_display);

        int attribute_list[] = {GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None};

        m_visual_info = glXChooseVisual(m_display, 0, attribute_list);
        if (m_visual_info == NULL)
        {
            XCloseDisplay(m_display);
            return false;
        }

        Colormap  colormap = XCreateColormap(m_display, root_window, m_visual_info->visual, AllocNone);

        XSetWindowAttributes set_window_attributes;
        set_window_attributes.colormap = colormap;
        set_window_attributes.event_mask = ExposureMask | KeyPressMask;

        unsigned int client_area_width = 800;
        unsigned int client_area_height = 600;

        m_window = XCreateWindow(m_display, root_window, 0, 0, client_area_width, client_area_height, 0, m_visual_info->depth, InputOutput, m_visual_info->visual, CWColormap | CWEventMask, &set_window_attributes);

        XStoreName(m_display, m_window, std::string(m_window_title.begin(), m_window_title.end()).c_str());

        m_is_ready = true;
        return true;
    }

    int x11_gui_module::window::run()
    {
        if (!m_is_ready)
            return -1;

        XMapWindow(m_display, m_window);

        XEvent event;
        XWindowAttributes window_attributes;
        Atom wm_delete_message = XInternAtom(m_display, "WM_DELETE_WINDOW", False);
        XSetWMProtocols(m_display, m_window, &wm_delete_message, 1);

        float delta_seconds = 0.0f;
        float total_seconds = 0.0f;

        std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
        std::chrono::steady_clock::time_point last_time = start_time;
        std::chrono::steady_clock::time_point current_time;
        std::chrono::duration<double> difference;

        while (true)
        {
            if (XPending(m_display) > 0)
            {
                XNextEvent(m_display, &event);
                switch (event.type)
                {
                case Expose:
                    XGetWindowAttributes(m_display, m_window, &window_attributes);
                    break;
                case ClientMessage:
                    if (event.xclient.data.l[0] == wm_delete_message)
                        goto end;
                    break;
                case KeyPress:
                    if (XKeycodeToKeysym(m_display, event.xkey.keycode, 0) == XK_Escape)
                        goto end;
                    break;
                }
            }
            else
            {
                current_time = std::chrono::steady_clock::now();
                difference = std::chrono::duration_cast<std::chrono::duration<double>>(current_time - last_time);
                delta_seconds = difference.count();
                last_time = current_time;
                difference = std::chrono::duration_cast<std::chrono::duration<double>>(current_time - start_time);
                total_seconds = difference.count();

                application_obj->update(delta_seconds, total_seconds);
            }
        }
        end:;

        XDestroyWindow(m_display, m_window);
        XCloseDisplay(m_display);

        return 0;
    }

    boost::any x11_gui_module::window::native_handle_obj() const
    {
        native_handle handle;
        handle.display = m_display;
        handle.window = m_window;
        handle.visual_info = m_visual_info;
        return handle;
    }
} // namespace hex3d

hex3d::module* create_module_obj()
{
    hex3d::x11_gui_module* module_obj = new hex3d::x11_gui_module;
    module_obj->initialize();
    return module_obj;
}
