#define HEX3D_SOURCE

#include <iostream>

#include <hex3d/application.hpp>

#if defined(BOOST_OS_WINDOWS_AVAILABLE)
#   include <windows.h>
#elif defined(BOOST_OS_LINUX_AVAILABLE)
#   include <dlfcn.h>
#endif

namespace hex3d
{
    application* application::only_instance = nullptr;

#if defined(BOOST_OS_WINDOWS_AVAILABLE)
    typedef module* (__stdcall *create_module_function_t)();

    template <typename object_type, typename function_type>
    object_type* load_object(const std::string& libfile)
    {
        std::string name_with_extension = "hex3d-" + libfile + ".dll";
        HINSTANCE handle = LoadLibrary(name_with_extension.c_str());
        if (!handle)
            return nullptr;

        function_type create_function = (function_type)GetProcAddress(handle, "create_module_obj");
        if (!create_function)
            return nullptr;

        return create_function();
    }
#elif defined(BOOST_OS_LINUX_AVAILABLE)
    typedef module* (*create_module_function_t)();

    template <typename object_type, typename function_type>
    object_type* load_object(const std::string& libfile)
    {
        std::string name_with_extension = "./libhex3d-" + libfile + ".so";
        std::cout << name_with_extension << std::endl;
        void* handle = dlopen(name_with_extension.c_str(), RTLD_LAZY);
        if (!handle)
        {
            printf("err is %s\n", dlerror());
            return nullptr;
        }

        function_type create_function = (function_type)dlsym(handle, "create_module_obj");
        if (!create_function)
            return nullptr;

        return create_function();
    };
#endif

    application::application(const std::string& initial_scene_filename)
    {
        if (!only_instance)
            only_instance = this;

#if defined(BOOST_OS_WINDOWS_AVAILABLE)
        const char* gui_module_implementations[] = { "win32_gui_module" };
        const char* grapihcs_module_implementations[] = { "direct3d11_graphics_module" };
#elif defined(BOOST_OS_LINUX_AVAILABLE)
        const char* gui_module_implementations[] = { "x11_gui_module" };
        const char* grapihcs_module_implementations[] = { "opengl_graphics_module" };
#endif

        module* m;
        const char* module_name;

        m = load_object<module, create_module_function_t>("core_module");
        if (m == nullptr)
        {
            std::cerr << "Failed to load the core module." << std::endl;
            std::exit(-1);
        }
        module_name = m->name();
        m_module_objects[module_name] = m;
        m_module_names["core"] = module_name;
        if (!m->is_ready())
        {
            std::cerr << "Failed to initialize the core module." << std::endl;
            std::exit(-1);
        }

        for (const auto& current : gui_module_implementations)
        {
            m = load_object<module, create_module_function_t>(current);
            if (m)
                break;
            std::cout << "Failed to load module " << current << std::endl;
        }
        if (m == nullptr)
        {
            std::cerr << "Failed to load the GUI module." << std::endl;
            std::exit(-1);
        }
        module_name = m->name();
        m_module_objects[module_name] = m;
        m_module_names["gui"] = module_name;
        if (!m->is_ready())
        {
            std::cerr << "Failed to initialize the GUI module." << std::endl;
            std::exit(-1);
        }

        for (const auto& current : grapihcs_module_implementations)
        {
            m = load_object<module, create_module_function_t>(current);
            if (m)
                break;
            std::cout << "Failed to load module " << current << std::endl;
        }
        if (m == nullptr)
        {
            std::cerr << "Failed to load the graphics module." << std::endl;
            std::exit(-1);
        }
        module_name = m->name();
        m_module_objects[module_name] = m;
        m_module_names["graphics"] = module_name;
        if (!m->is_ready())
        {
            std::cerr << "Failed to initialize the graphics module." << std::endl;
            std::exit(-1);
        }

        if (!initial_scene_filename.empty())
            core_module_obj->send_message(HEX3D_CORE_MODULE_MESSAGE_LOAD_SCENE_FILE, initial_scene_filename);
    }

    application* application::instance()
    {
        return only_instance;
    }

    int application::run()
    {
        return m_module_objects[m_module_names["gui"]]->run();
    }

    void application::update(float delta_seconds, float total_seconds)
    {
        m_module_objects[m_module_names[ "core" /*"graphics"*/]]->update(delta_seconds, total_seconds);
    }

    module* application::module_obj(const char *name)
    {
        return m_module_objects[name];
    }
} // namespace hex3d
