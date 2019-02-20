#define HEX3D_WIN32_GUI_MODULE_SOURCE
#include <hex3d/win32_gui_module/win32_gui_module.hpp>
#include <chrono>

namespace hex3d
{
    // WIN32_GUI_MODULE:

    win32_gui_module::win32_gui_module()
    {
        m_window = new win32_gui_module::window;
    }

    bool win32_gui_module::initialize()
    {
        m_is_ready = m_window->initialize();
        return m_is_ready;
    }

    int win32_gui_module::run()
    {
        return m_window->run();
    }

    // WINDOW:

    win32_gui_module::window* g_main_window_ptr = nullptr;

    LRESULT CALLBACK window_procedure(HWND window_handle, UINT message, WPARAM w_param, LPARAM l_param)
    {
        if (g_main_window_ptr == nullptr)
            return DefWindowProc(window_handle, message, w_param, l_param);
        return g_main_window_ptr->window_procedure(window_handle, message, w_param, l_param);
    }

    bool win32_gui_module::window::initialize()
    {
        m_application_instance_handle = GetModuleHandle(nullptr);
        m_command_line = GetCommandLine();
        m_show_command = SW_SHOWNORMAL;
        m_window_class_name = "Hex3DWindowClass";
        g_main_window_ptr = this;

        WNDCLASS window_class;
        window_class.style = CS_HREDRAW | CS_VREDRAW;
        window_class.lpfnWndProc = hex3d::window_procedure;
        window_class.cbClsExtra = 0;
        window_class.cbWndExtra = 0;
        window_class.hInstance = m_application_instance_handle;
        window_class.hIcon = LoadIcon(0, IDI_APPLICATION);
        window_class.hCursor = LoadCursor(0, IDC_ARROW);
        window_class.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
        window_class.lpszMenuName = 0;
        window_class.lpszClassName = m_window_class_name;

        if (!RegisterClass(&window_class))
            return false;

        m_client_area_width = 800;
        m_client_area_height = 600;

        RECT rectangle;
        rectangle.left = 0;
        rectangle.top = 0;
        rectangle.right = m_client_area_width;
        rectangle.bottom = m_client_area_height;

        AdjustWindowRect(&rectangle, WS_OVERLAPPEDWINDOW, false);

        unsigned int window_width = rectangle.right - rectangle.left;
        unsigned int window_height = rectangle.bottom - rectangle.top;

        m_main_window_handle = CreateWindow(m_window_class_name, std::string(m_window_title.begin(), m_window_title.end()).c_str(), WS_OVERLAPPEDWINDOW, (GetSystemMetrics(SM_CXSCREEN) - window_width) / 2, (GetSystemMetrics(SM_CYSCREEN) - window_height) / 2, window_width, window_height, 0, 0, m_application_instance_handle, 0);

        if (!m_main_window_handle)
            return false;

        m_is_ready = true;
        return true;
    }

    int win32_gui_module::window::run()
    {
        if (!m_is_ready)
            return -1;

        ShowWindow(m_main_window_handle, m_show_command);
        UpdateWindow(m_main_window_handle);

        MSG message;
        ZeroMemory(&message, sizeof(MSG));

        float delta_seconds = 0.0f;
        float total_seconds = 0.0f;

        std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
        std::chrono::steady_clock::time_point last_time = start_time;
        std::chrono::steady_clock::time_point current_time;
        std::chrono::duration<double> difference;

        while (message.message != WM_QUIT)
        {
            if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&message);
                DispatchMessage(&message);
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

        return (int)message.wParam;
    }

    boost::any win32_gui_module::window::native_handle_obj() const
    {
        native_handle handle;
        handle.application_instance_handle = m_application_instance_handle;
        handle.main_window_handle = m_main_window_handle;
        handle.device_context = m_device_context;
        return handle;
    }

    LRESULT win32_gui_module::window::window_procedure(HWND window_handle, UINT message, WPARAM w_param, LPARAM l_param)
    {
        switch (message)
        {
        case WM_CREATE:
            m_device_context = GetDC(m_main_window_handle);
            return 0;
        case WM_KEYDOWN:
            if (w_param == VK_ESCAPE)
                DestroyWindow(m_main_window_handle);
            return 0;
        case WM_DESTROY:
            ReleaseDC(m_main_window_handle, m_device_context);
            PostQuitMessage(0);
            return 0;
        default:
            return DefWindowProc(window_handle, message, w_param, l_param);
        }
    }
} // namespace hex3d

hex3d::module* create_module_obj()
{
    hex3d::win32_gui_module* module_obj = new hex3d::win32_gui_module;
    module_obj->initialize();
    return module_obj;
}

