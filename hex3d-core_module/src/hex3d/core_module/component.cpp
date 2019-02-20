#define HEX3D_CORE_MODULE_SOURCE

#include <hex3d/core_module/core_module.hpp>

namespace hex3d
{
    core_module::component::component(core_module::entity* owner)
        : m_owner(owner)
    {
    }

    // TODO: Get rid o' this:
    /*
    core_module::component::component(const core_module::component& other)
        : m_owner(nullptr)
        , m_properties(other.m_properties)
    {
    }

    core_module::component& core_module::component::operator=(const core_module::component& other)
    {
        m_owner = nullptr;
        m_properties = other.m_properties;
    }
    */

    bool core_module::component::is_orphan() const
    {
        return m_owner == nullptr;
    }

    void core_module::component::update(pass_event* pass_ev)
    {
    }

    std::string core_module::component::property(const std::string& name) const
    {
        return read_property(name);
    }

    void core_module::component::set_property(const std::string& name, const std::string& value)
    {
        write_property(name, value);
    }

    core_module::entity* core_module::component::owner()
    {
        return m_owner;
    }

    std::string core_module::component::read_property(const std::string& name) const
    {
        std::string value;
        try
        {
            value = m_properties.at(name);
        }
        catch (std::out_of_range& ex)
        {
            value = "<null>";
        }

        return value;
    }

    void core_module::component::write_property(const std::string& name, const std::string& value)
    {
        m_properties[name] = value;
    }
} // namespace hex3d
