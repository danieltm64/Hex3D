#define HEX3D_CORE_MODULE_SOURCE

#include <hex3d/core_module/core_module.hpp>

namespace hex3d
{
    core_module::entity_graph::entity_graph()
        : m_is_ready(false)
    {
    }

    core_module::entity_graph::entity_graph(const std::string& filename)
        : m_filename(filename)
        , m_is_ready(false)
    {
        load(m_filename);
    }

    bool core_module::entity_graph::is_ready() const
    {
        return m_is_ready;
    }

    void core_module::entity_graph::load(const std::string& filename)
    {
        boost::property_tree::ptree tree;
        boost::property_tree::read_xml(filename, tree);
        m_top_level_entities = load_recursive(tree.get_child("level.scene_graph"));
        if (m_top_level_entities.empty())
            m_is_ready = false;
        else
            m_is_ready = true;
        /*
        std::cerr << "Entity graph up to 4 levels down:" << std::endl;
        for (auto& current1 : m_top_level_entities)
        {
            std::cerr << "name: " << current1.name() << std::endl;
            for (auto& current_comp : current1.m_components)
            {
                std::cerr << "> owner: " << current_comp->owner()->name() << std::endl;
                if (dynamic_cast<core_module::transform_comp*>(current_comp))
                    std::cerr << "> It's a transform_comp" << std::endl;
                else
                    std::cerr << "> It IS NOT a transform_comp" << std::endl;
            }
            for (auto& current2 : current1.children())
            {
                std::cerr << "++ name: " << current2.name() << std::endl;
                for (auto& current_comp : current2.m_components)
                {
                    std::cerr << "++> owner: " << current_comp->owner()->name() << std::endl;
                    if (dynamic_cast<core_module::transform_comp*>(current_comp))
                        std::cerr << "++> It's a transform_comp" << std::endl;
                    else
                        std::cerr << "++> It IS NOT a transform_comp" << std::endl;
                }
                for (auto& current3 : current2.children())
                {
                    std::cerr << "++++ name: " << current3.name() << std::endl;
                    for (auto& current_comp : current3.m_components)
                    {
                        std::cerr << "++++> owner: " << current_comp->owner()->name() << std::endl;
                        if (dynamic_cast<core_module::transform_comp*>(current_comp))
                            std::cerr << "++++> It's a transform_comp" << std::endl;
                        else
                            std::cerr << "++++> It IS NOT a transform_comp" << std::endl;
                    }
                }
            }
        }
        std::exit(-17);
        */
    }

    core_module::entity* core_module::entity_graph::entity_by_name(const std::string& name)
    {
        return entity_by_name_recursive(m_top_level_entities, name);
    }

    void core_module::entity_graph::register_component_factory_function(const std::string& name, const std::function<core_module::component*()>& func)
    {
        m_factory_functions[name] = func;
    }

    void core_module::entity_graph::register_pass(const std::string &pass_name, const std::function<void(pass_event*)>& pass_starter, const std::function<void(pass_event*)>& pass_ender)
    {
        m_pass_names.push_back(pass_name);
        m_pass_starters.push_back(pass_starter);
        m_pass_enders.push_back(pass_ender);
    }

    void core_module::entity_graph::run_passes(float delta_seconds, float total_seconds)
    {
        pass_event pass_ev(HEX3D_CORE_MODULE_NAME, delta_seconds, total_seconds);

        entity& root_entity = m_top_level_entities.front();
        std::vector<core_module::entity> root_entity_children = root_entity.children();

        transform root_entity_transform;
        transform_comp* root_entity_transform_comp = root_entity.get_component<core_module::transform_comp>();

        root_entity_transform.scale() = root_entity_transform_comp->local_transform().scale();
        root_entity_transform.rotation() = root_entity_transform_comp->local_transform().rotation();
        root_entity_transform.translation() = root_entity_transform_comp->local_transform().translation();

        for (unsigned int i = 0; i < root_entity_children.size(); ++i)
            update_entity_object(root_entity_transform, root_entity, root_entity_children[i], &pass_ev);

        for (unsigned int i = 0; i < m_pass_names.size(); ++i)
        {
            pass_event pass_ev(m_pass_names[i], delta_seconds, total_seconds);
            m_pass_starters[i](&pass_ev);
            for (unsigned int i = 0; i < root_entity_children.size(); ++i)
                update_entity_object(root_entity, root_entity_children[i], &pass_ev);
            m_pass_enders[i](&pass_ev);
        }
    }

    std::vector<core_module::entity> core_module::entity_graph::load_recursive(const boost::property_tree::ptree& tree)
    {
        std::vector<core_module::entity> objects;
        for (auto element : tree)
        {
            if (element.first.data() == std::string("entity"))
            {
                core_module::entity object;
                for (auto sub : element.second)
                {
                    if (sub.first.data() == std::string("<xmlattr>"))
                        for (auto attribute : sub.second)
                        {
                            if (attribute.first.data() == std::string("name"))
                                object.set_name(attribute.second.data());
                        }
                    else if (sub.first.data() == std::string("property"))
                    {
                        for (auto property_sub : sub.second)
                        {
                            if (property_sub.first.data() == std::string("<xmlattr>"))
                            {
                                std::string property_name;
                                std::string property_value;
                                for (auto attribute : property_sub.second)
                                {
                                    if (attribute.first.data() == std::string("name"))
                                        property_name = attribute.second.data();
                                    else if (attribute.first.data() == std::string("value"))
                                        property_value = attribute.second.data();
                                }
                                object.set_property(property_name, property_value);
                            }
                        }
                    }
                    else if (sub.first.data() == std::string("component"))
                    {
                        component* comp = nullptr;
                        for (auto component_sub : sub.second)
                        {
                            if (component_sub.first.data() == std::string("<xmlattr>"))
                            {
                                std::string component_type;
                                for (auto attribute : component_sub.second)
                                {
                                    if (attribute.first.data() == std::string("type"))
                                        component_type = attribute.second.data();
                                }
                                object.set_property("component " + component_type, "<valid>");
                                if (m_factory_functions.count(component_type))
                                    comp = object.add_component(m_factory_functions[component_type]());
                            }
                            else if (component_sub.first.data() == std::string("property"))
                            {
                                for (auto property_sub : component_sub.second)
                                {
                                    if (property_sub.first.data() == std::string("<xmlattr>"))
                                    {
                                        std::string property_name;
                                        std::string property_value;
                                        for (auto attribute : property_sub.second)
                                        {
                                            if (attribute.first.data() == std::string("name"))
                                                property_name = attribute.second.data();
                                            else if (attribute.first.data() == std::string("value"))
                                                property_value = attribute.second.data();
                                        }
                                        if (comp)
                                            comp->set_property(property_name, property_value);
                                    }
                                }
                            }
                        }
                    }
                    else if (sub.first.data() == std::string("children"))
                    {
                        std::vector<core_module::entity> children = load_recursive(sub.second);
                        object.m_children = std::move(children);
                        /*
                        for (const auto& child : children)
                            object.add_child(child);
                        */
                    }
                }
                objects.push_back(object);
            }
        }
        return objects;
    }

    core_module::entity* core_module::entity_graph::entity_by_name_recursive(std::vector<core_module::entity>& entities, const std::string& name) //const
    {
        core_module::entity* ent = nullptr;
        for (auto& element : entities)
        {
            if (element.name() == name)
                return &element;
        }
        for (auto& element : entities)
        {
            core_module::entity* temp = entity_by_name_recursive(element.m_children, name);
            if (temp != nullptr)
                return temp;
        }
        return ent;
    }

    void core_module::entity_graph::update_entity_object(core_module::transform transform_obj, core_module::entity &parent, core_module::entity &child, pass_event* pass_ev)
    {
        transform_comp* transform_ptr = child.get_component<transform_comp>();

        if (transform_ptr)
        {
            vector3d scaleop1 = transform_obj.scale();
            vector3d scaleop2 = transform_ptr->local_transform().scale();
            transform_obj.scale() = vector3d(scaleop1.x() * scaleop2.x(), scaleop1.y() * scaleop2.y(), scaleop1.z() * scaleop2.z());
            transform_obj.rotation() += transform_ptr->local_transform().rotation();
            transform_obj.translation() += transform_ptr->local_transform().translation();
            transform_ptr->global_transform() = transform_obj;
        }

        child.update(pass_ev);

        for (unsigned int i = 0; i < child.children().size(); ++i)
            update_entity_object(transform_obj, child, child.m_children[i], pass_ev);
    }

    void core_module::entity_graph::update_entity_object(core_module::entity &parent, core_module::entity &child, core_module::pass_event* pass_ev)
    {
        child.update(pass_ev);

        for (unsigned int i = 0; i < child.children().size(); ++i)
            update_entity_object(child, child.m_children[i], pass_ev);
    }
} // namespace hex3d
