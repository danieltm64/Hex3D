#define HEX3D_CORE_MODULE_SOURCE

#include <hex3d/core_module/core_module.hpp>

namespace hex3d
{
    core_module::entity::entity(const core_module::entity& other)
        : m_name(other.m_name)
        , m_properties(other.m_properties)
        , m_children(other.m_children)
    {
        for (auto current_component : m_components)
        {
            delete current_component;
        }

        m_components = other.m_components;

        for (auto current_component : m_components)
        {
           current_component->m_owner = this;
        }
    }

    core_module::entity& core_module::entity::operator=(const core_module::entity& other)
    {
        if (this == &other)
            return *this;

        m_name = other.m_name;
        m_properties = other.m_properties;
        m_children = other.m_children;

        for (auto current_component : m_components)
        {
            delete current_component;
        }

        m_components = other.m_components;

        for (auto current_component : m_components)
        {
            current_component->m_owner = this;
        }

        return *this;
    }
    /*
    core_module::entity::entity(core_module::entity&& other)
        : m_name(std::move(other.m_name))
        , m_properties(std::move(other.m_properties))
        , m_children(other.m_children)
    {
        for (auto current_component : m_components)
        {
            delete current_component;
        }

        m_components = other.m_components;

        for (auto current_component : m_components)
        {
           current_component->m_owner = this;
        }
    }

    core_module::entity& core_module::entity::operator=(core_module::entity&& other)
    {
        if (this == &other)
            return *this;

        m_name = std::move(other.m_name);
        m_properties = std::move(other.m_properties);
        m_children = std::move(other.m_children);

        for (auto current_component : m_components)
        {
            delete current_component;
        }

        m_components = std::move(other.m_components);

        for (auto current_component : m_components)
        {
            current_component->m_owner = this;
        }

        return *this;
    }
    */
    void core_module::entity::update(pass_event* pass_ev)
    {
        for (auto& current_component : m_components)
        {
            current_component->update(pass_ev);
        }
    }

    std::string core_module::entity::name() const
    {
        return m_name;
    }

    void core_module::entity::set_name(const std::string& name)
    {
        m_name = name;
    }

    const std::vector<core_module::entity>& core_module::entity::children() const
    {
        return m_children;
    }

    void core_module::entity::add_child(const core_module::entity& child)
    {
        m_children.push_back(child);
    }

    unsigned int core_module::entity::component_count() const
    {
        return m_components.size();
    }

    std::string core_module::entity::property(const std::string& name) const
    {
        return read_property(name);
    }

    void core_module::entity::set_property(const std::string& name, const std::string& value)
    {
        write_property(name, value);
    }

    std::string core_module::entity::read_property(const std::string& name) const
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

    void core_module::entity::write_property(const std::string& name, const std::string& value)
    {
        m_properties[name] = value;
    }
} // namespace hex3d
