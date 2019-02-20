#define HEX3D_CORE_MODULE_SOURCE

#include <hex3d/core_module/core_module.hpp>

namespace hex3d
{
    core_module::pass_event::pass_event(const std::string& name, float delta_seconds, float total_seconds)
        : m_name(name)
        , m_delta_seconds(delta_seconds)
        , m_total_seconds(total_seconds)
    {
    }

    const std::string& core_module::pass_event::name() const
    {
        return m_name;
    }

    float core_module::pass_event::delta_seconds() const
    {
        return m_delta_seconds;
    }

    float core_module::pass_event::total_seconds() const
    {
        return m_total_seconds;
    }
} // namespace hex3d
