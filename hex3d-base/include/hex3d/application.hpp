#ifndef HEX3D_APPLICATION_HPP
#define HEX3D_APPLICATION_HPP

#include <string>

#include <hex3d/config.hpp>
#include <hex3d/core_module/core_module.hpp>

namespace hex3d
{
    class HEX3D_DECL application
    {
    public:
        application(const std::string& initial_scene_filename = "");

        // copy operations
        application(const application& other) = delete;
        application& operator=(const application& other) = delete;

        // move operations
        application(application&& other) noexcept = delete;
        application& operator=(application&& other) noexcept = delete;

        static application* instance();

        int run();
        void update(float delta_seconds, float total_seconds);
        module* module_obj(const char* name);

    private:
        static application* only_instance;
        std::map<std::string, module*> m_module_objects;
        std::map<std::string, std::string> m_module_names;
    };
} // namespace hex3d

#define application_obj (application::instance())

#endif // HEX3D_APPLICATION_HPP
