#define HEX3D_CORE_MODULE_SOURCE

#include <hex3d/core_module/core_module.hpp>

namespace hex3d
{
    core_module::core_module()
    {
        m_entity_graph.register_component_factory_function("transform", transform_comp::create);
    }

    bool core_module::initialize()
    {
        m_is_ready = true;
        return true;
    }

    void core_module::send_message(const char* name, const boost::any& input)
    {
        if (std::strcmp(name, HEX3D_CORE_MODULE_MESSAGE_LOAD_SCENE_FILE) == 0)
            m_entity_graph.load(boost::any_cast<std::string>(input));
    }

    void core_module::update(float delta_seconds, float total_seconds)
    {
        m_entity_graph.run_passes(delta_seconds, total_seconds);
    }

    core_module::entity_graph* core_module::entity_graph_obj()
    {
        return &m_entity_graph;
    }
} // namespace hex3d

hex3d::module* create_module_obj()
{
    hex3d::core_module* module_obj = new hex3d::core_module;
    module_obj->initialize();
    return module_obj;
}
