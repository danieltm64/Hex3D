#define HEX3D_GRAPHICS_MODULE_SOURCE
#include <hex3d/graphics_module/graphics_module.hpp>

namespace hex3d
{
    bool graphics_module::initialize()
    {
        core_module_obj->entity_graph_obj()->register_component_factory_function("camera", camera_comp::create);

        m_is_ready = true;
        return true;
    }

    graphics_module::camera* graphics_module::main_camera()
    {
        core_module::entity_graph* entity_graph_locptr = core_module_obj->entity_graph_obj();
        return &(entity_graph_locptr->entity_by_name(entity_graph_locptr->entity_by_name("root")->property("main_camera"))->get_component<graphics_module::camera_comp>()->camera());
    }
} // namespace hex3d

hex3d::module* create_module_obj()
{
    return nullptr;
}
