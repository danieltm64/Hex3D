#define HEX3D_CORE_MODULE_SOURCE

#include <hex3d/core_module/core_module.hpp>

namespace hex3d
{
    core_module::transform::transform()
        : m_scale(1.0f, 1.0f, 1.0f)
        , m_rotation(0.0f, 0.0f, 0.0f)
        , m_translation(0.0f, 0.0f, 0.0f)
    {
    }

    core_module::transform::transform(const vector3d& scale, const vector3d& rotation, const vector3d& translation)
        : m_scale(scale)
        , m_rotation(rotation)
        , m_translation(translation)
    {
    }

    core_module::vector3d& core_module::transform::scale()
    {
        return m_scale;
    }

    core_module::vector3d& core_module::transform::rotation()
    {
        return m_rotation;
    }

    core_module::vector3d& core_module::transform::translation()
    {
        return m_translation;
    }

    const core_module::vector3d& core_module::transform::scale() const
    {
        return m_scale;
    }

    const core_module::vector3d& core_module::transform::rotation() const
    {
        return m_rotation;
    }

    const core_module::vector3d& core_module::transform::translation() const
    {
        return m_translation;
    }

    core_module::matrix4x4 core_module::transform::world_matrix() const
    {
        core_module::matrix4x4 scale_matrix = core_module::matrix4x4::scale(m_scale);
        core_module::matrix4x4 rotation_matrix = core_module::matrix4x4::rotation(m_rotation);
        core_module::matrix4x4 translation_matrix = core_module::matrix4x4::translation(m_translation);

        return scale_matrix * rotation_matrix * translation_matrix;
    }
} // namespace hex3d
