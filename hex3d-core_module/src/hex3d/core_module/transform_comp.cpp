#define HEX3D_CORE_MODULE_SOURCE

#include <hex3d/core_module/core_module.hpp>

namespace hex3d
{
    core_module::transform_comp::transform_comp(entity *owner)
        : component(owner)
    {
    }

    core_module::transform_comp::transform_comp(const vector3d& scale, const vector3d& rotation, const vector3d& translation)
        : m_local_transform(scale, rotation, translation)
    {
    }

    core_module::transform_comp *core_module::transform_comp::create()
    {
        return new transform_comp;
    }

    core_module::transform& core_module::transform_comp::local_transform()
    {
        return m_local_transform;
    }

    const core_module::transform& core_module::transform_comp::local_transform() const
    {
        return m_local_transform;
    }

    core_module::transform& core_module::transform_comp::global_transform()
    {
        return m_global_transform;
    }

    const core_module::transform& core_module::transform_comp::global_transform() const
    {
        return m_global_transform;
    }

    void core_module::transform_comp::set_property(const std::string& name, const std::string& value)
    {
        component::write_property(name, value);
        if (name == "scale")
            m_local_transform.scale() = core_module::utils::string_to_vector3d(value);
        else if (name == "rotation")
            m_local_transform.rotation() = core_module::utils::string_to_vector3d(value);
        else if (name == "translation")
            m_local_transform.translation() = core_module::utils::string_to_vector3d(value);
    }
} // namespace hex3d
