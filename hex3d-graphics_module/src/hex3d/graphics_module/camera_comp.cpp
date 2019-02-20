#define HEX3D_GRAPHICS_MODULE_SOURCE
#include <hex3d/graphics_module/graphics_module.hpp>

namespace hex3d
{
    void graphics_module::camera_comp::set_property(const std::string& name, const std::string& value)
    {
        component::write_property(name, value);
        if (name == "eye_position")
            m_camera.set_eye_position(core_module::utils::string_to_vector3d(value));
        else if (name == "target_position")
            m_camera.set_target_position(core_module::utils::string_to_vector3d(value));
        else if (name == "up_direction")
            m_camera.set_up_direction(core_module::utils::string_to_vector3d(value));
        else if (name == "vertical_FOV")
            m_camera.set_vertical_FOV(core_module::utils::string_to_float(value));
        else if (name == "aspect_ratio")
            m_camera.set_aspect_ratio(core_module::utils::string_to_float(value));
        else if (name == "near_z")
            m_camera.set_near_z(core_module::utils::string_to_float(value));
        else if (name == "far_z")
            m_camera.set_far_z(core_module::utils::string_to_float(value));
    }
} // namespace hex3d
