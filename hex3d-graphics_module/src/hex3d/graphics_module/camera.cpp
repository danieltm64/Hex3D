#define HEX3D_GRAPHICS_MODULE_SOURCE
#include <hex3d/graphics_module/graphics_module.hpp>

namespace hex3d
{
    core_module::vector3d graphics_module::camera::eye_position() const
    {
        return m_eye_position;
    }

    void graphics_module::camera::set_eye_position(const core_module::vector3d& eye_position)
    {
        m_eye_position = eye_position;
    }

    core_module::vector3d graphics_module::camera::target_position() const
    {
        return m_target_position;
    }

    void graphics_module::camera::set_target_position(const core_module::vector3d& target_position)
    {
        m_target_position = target_position;
    }

    core_module::vector3d graphics_module::camera::up_direction() const
    {
        return m_up_direction;
    }

    void graphics_module::camera::set_up_direction(const core_module::vector3d& up_direction)
    {
        m_up_direction = up_direction;
    }

    float graphics_module::camera::vertical_FOV() const
    {
        return m_vertical_FOV;
    }

    void graphics_module::camera::set_vertical_FOV(float vertical_FOV)
    {
        m_vertical_FOV = vertical_FOV;
    }

    float graphics_module::camera::near_z() const
    {
        return m_near_z;
    }

    void graphics_module::camera::set_near_z(float near_z)
    {
        m_near_z = near_z;
    }

    float graphics_module::camera::far_z() const
    {
        return m_far_z;
    }

    void graphics_module::camera::set_far_z(float far_z)
    {
        m_far_z = far_z;
    }

    float graphics_module::camera::aspect_ratio() const
    {
        return m_aspect_ratio;
    }

    void graphics_module::camera::set_aspect_ratio(float aspect_ratio)
    {
        m_aspect_ratio = aspect_ratio;
    }

    core_module::matrix4x4 graphics_module::camera::view_matrix()
    {
        return core_module::matrix4x4::look_at_LH(m_eye_position, m_target_position, m_up_direction);
    }

    core_module::matrix4x4 graphics_module::camera::projection_matrix()
    {
        return core_module::matrix4x4::perspective_projection_LH(m_vertical_FOV, m_aspect_ratio, m_near_z, m_far_z);
    }
} // namespace hex3d
