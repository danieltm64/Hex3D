#ifndef HEX3D_GRAPHICS_MODULE_HPP
#define HEX3D_GRAPHICS_MODULE_HPP

#include <hex3d/graphics_module/config.hpp>
#include <hex3d/core_module/core_module.hpp>
#include <hex3d/application.hpp>
#include <string>
#include <vector>

#define HEX3D_GRAPHICS_MODULE_NAME "hex3d/graphics_module"

namespace hex3d
{
    class HEX3D_GRAPHICS_MODULE_DECL graphics_module : public module
    {
    public:
        class camera;

        graphics_module() {/*core_module_obj->entity_graph_obj()->register_pass(HEX3D_GRAPHICS_MODULE_NAME);*/}

        // copy operations
        graphics_module(const graphics_module& other) = delete;
        graphics_module& operator=(const graphics_module& other) = delete;

        // move operations
        graphics_module(graphics_module&& other) = delete;
        graphics_module& operator=(graphics_module&& other) = delete;

        virtual ~graphics_module() {}

        virtual bool initialize() override;
        virtual int run() override = 0;
        virtual void update(float delta_seconds, float total_seconds) override = 0;
        virtual const char* name() override {return HEX3D_GRAPHICS_MODULE_NAME;}

        camera* main_camera();

        class HEX3D_GRAPHICS_MODULE_DECL camera
        {
        public:
            camera() = default;

            core_module::vector3d eye_position() const;
            void set_eye_position(const core_module::vector3d& eye_position);

            core_module::vector3d target_position() const;
            void set_target_position(const core_module::vector3d& target_position);

            core_module::vector3d up_direction() const;
            void set_up_direction(const core_module::vector3d& up_direction);

            float vertical_FOV() const;
            void set_vertical_FOV(float vertical_FOV);

            float near_z() const;
            void set_near_z(float near_z);

            float far_z() const;
            void set_far_z(float far_z);

            float aspect_ratio() const;
            void set_aspect_ratio(float aspect_ratio);

            core_module::matrix4x4 view_matrix();
            core_module::matrix4x4 projection_matrix();

        private:
            core_module::vector3d m_eye_position;
            core_module::vector3d m_target_position;
            core_module::vector3d m_up_direction;
            float m_vertical_FOV;
            float m_near_z;
            float m_far_z;
            float m_aspect_ratio;
        };

        class HEX3D_GRAPHICS_MODULE_DECL camera_comp : public core_module::component
        {
        public:
            camera_comp(core_module::entity* owner = nullptr) : core_module::component(owner) {}
            camera_comp(const camera_comp& other) = delete;
            camera_comp& operator=(const camera_comp& other) = delete;

            static camera_comp* create() {return new camera_comp;}

            graphics_module::camera& camera() {return m_camera;}
            const graphics_module::camera& camera() const {return m_camera;}

            virtual void set_property(const std::string& name, const std::string& value) override;

        private:
            graphics_module::camera m_camera;
        };

        class HEX3D_GRAPHICS_MODULE_DECL cube_comp : public core_module::component
        {
        public:
            cube_comp(core_module::entity* owner = nullptr) : core_module::component(owner) {}
            cube_comp(const cube_comp& other) = delete;
            cube_comp& operator=(const cube_comp& other) = delete;
        };
    };
} // namespace hex3d

#define graphics_module_obj (static_cast<hex3d::graphics_module*>(application_obj->module_obj(HEX3D_GRAPHICS_MODULE_NAME)))

extern "C" HEX3D_GRAPHICS_MODULE_DECL hex3d::module* create_module_obj();

#endif // HEX3D_GRAPHICS_MODULE_HPP
