#ifndef HEX3D_CORE_MODULE_HPP
#define HEX3D_CORE_MODULE_HPP

#include <vector>
#include <map>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include <cml/cml.h>

#include <hex3d/core_module/config.hpp>
#include <hex3d/module.hpp>

#define HEX3D_CORE_MODULE_NAME "hex3d/core_module"
#define HEX3D_CORE_MODULE_MESSAGE_LOAD_SCENE_FILE "load_scene_file"

namespace hex3d
{
    class HEX3D_CORE_MODULE_DECL core_module : public module
    {
    public:
        class entity;
        class entity_graph;

        core_module();

        // copy operations
        core_module(const core_module& other) = delete;
        core_module& operator=(const core_module& other) = delete;

        // move operations
        core_module(core_module&& other) noexcept = delete;
        core_module& operator=(core_module&& other) noexcept = delete;

        virtual bool initialize() override;
        virtual void send_message(const char* name, const boost::any& input) override;
        virtual int run() override {return 0;}
        virtual void update(float delta_seconds, float total_seconds) override;
        virtual const char* name() override {return HEX3D_CORE_MODULE_NAME;}

        entity_graph* entity_graph_obj();

        class HEX3D_CORE_MODULE_DECL vector2d
        {
        public:
            vector2d();
            vector2d(float x, float y);

            // copy operations
            vector2d(const vector2d& other) = default;
            vector2d& operator=(const vector2d& other) = default;

            // move operations
            vector2d(vector2d&& other) noexcept = default;
            vector2d& operator=(vector2d&& other) noexcept = default;

            float x() const;
            void set_x(float x);

            float y() const;
            void set_y(float y);

            float length() const;

            void normalize();
            vector2d normalized() const;

            static float dot_product(const vector2d& vector1, const vector2d& vector2);

            bool operator==(const vector2d& other) const;
            bool operator!=(const vector2d& other) const;

            friend HEX3D_CORE_MODULE_DECL vector2d operator+(const vector2d& vector1, const vector2d& vector2);
            friend HEX3D_CORE_MODULE_DECL vector2d operator-(const vector2d& vector1, const vector2d& vector2);

            friend HEX3D_CORE_MODULE_DECL vector2d operator*(float scalar, const vector2d& vector);
            friend HEX3D_CORE_MODULE_DECL vector2d operator*(const vector2d& vector, float scalar);

            friend HEX3D_CORE_MODULE_DECL vector2d operator/(const vector2d& vector, float scalar);

            friend HEX3D_CORE_MODULE_DECL vector2d& operator+=(vector2d& vector1, const vector2d& vector2);
            friend HEX3D_CORE_MODULE_DECL vector2d& operator-=(vector2d& vector1, const vector2d& vector2);
            friend HEX3D_CORE_MODULE_DECL vector2d& operator*=(vector2d& vector, float scalar);
            friend HEX3D_CORE_MODULE_DECL vector2d& operator/=(vector2d& vector, float scalar);

            friend HEX3D_CORE_MODULE_DECL std::ostream& operator<<(std::ostream& ostream, const vector2d& vector);

        private:
            float m_x;
            float m_y;
        };

        class HEX3D_CORE_MODULE_DECL vector3d
        {
        public:
            vector3d();
            vector3d(float x, float y, float z);

            // copy operations
            vector3d(const vector3d& other) = default;
            vector3d& operator=(const vector3d& other) = default;

            // move operations
            vector3d(vector3d&& other) noexcept = default;
            vector3d& operator=(vector3d&& other) noexcept = default;

            float x() const;
            void set_x(float x);

            float y() const;
            void set_y(float y);

            float z() const;
            void set_z(float z);

            vector2d xy() const;
            vector2d xz() const;
            vector2d yz() const;

            float length() const;

            void normalize();
            vector3d normalized() const;

            static float dot_product(const vector3d& vector1, const vector3d& vector2);
            static vector3d cross_product(const vector3d& vector1, const vector3d& vector2);

            bool operator==(const vector3d& other) const;
            bool operator!=(const vector3d& other) const;

            friend HEX3D_CORE_MODULE_DECL vector3d operator+(const vector3d& vector1, const vector3d& vector2);
            friend HEX3D_CORE_MODULE_DECL vector3d operator-(const vector3d& vector1, const vector3d& vector2);

            friend HEX3D_CORE_MODULE_DECL vector3d operator*(float scalar, const vector3d& vector);
            friend HEX3D_CORE_MODULE_DECL vector3d operator*(const vector3d& vector, float scalar);

            friend HEX3D_CORE_MODULE_DECL vector3d operator/(const vector3d& vector, float scalar);

            friend HEX3D_CORE_MODULE_DECL vector3d& operator+=(vector3d& vector1, const vector3d& vector2);
            friend HEX3D_CORE_MODULE_DECL vector3d& operator-=(vector3d& vector1, const vector3d& vector2);
            friend HEX3D_CORE_MODULE_DECL vector3d& operator*=(vector3d& vector, float scalar);
            friend HEX3D_CORE_MODULE_DECL vector3d& operator/=(vector3d& vector, float scalar);

            friend HEX3D_CORE_MODULE_DECL std::ostream& operator<<(std::ostream& ostream, const vector3d& vector);

        private:
            float m_x;
            float m_y;
            float m_z;
        };

        class HEX3D_CORE_MODULE_DECL vector4d
        {
        public:
            vector4d();
            vector4d(float x, float y, float z, float w);

            // copy operations
            vector4d(const vector4d& other) = default;
            vector4d& operator=(const vector4d& other) = default;

            // move operations
            vector4d(vector4d&& other) noexcept = default;
            vector4d& operator=(vector4d&& other) noexcept = default;

            float x() const;
            void set_x(float x);

            float y() const;
            void set_y(float y);

            float z() const;
            void set_z(float z);

            float w() const;
            void set_w(float w);

            vector2d xy() const;
            vector2d xz() const;
            vector2d xw() const;
            vector2d yz() const;
            vector2d yw() const;
            vector2d zw() const;
            vector3d xyz() const;

            float length() const;

            void normalize();
            vector4d normalized() const;

            static float dot_product(const vector4d& vector1, const vector4d& vector2);

            bool operator==(const vector4d& other) const;
            bool operator!=(const vector4d& other) const;

            friend HEX3D_CORE_MODULE_DECL vector4d operator+(const vector4d& vector1, const vector4d& vector2);
            friend HEX3D_CORE_MODULE_DECL vector4d operator-(const vector4d& vector1, const vector4d& vector2);

            friend HEX3D_CORE_MODULE_DECL vector4d operator*(float scalar, const vector4d& vector);
            friend HEX3D_CORE_MODULE_DECL vector4d operator*(const vector4d& vector, float scalar);

            friend HEX3D_CORE_MODULE_DECL vector4d operator/(const vector4d& vector, float scalar);

            friend HEX3D_CORE_MODULE_DECL vector4d& operator+=(vector4d& vector1, const vector4d& vector2);
            friend HEX3D_CORE_MODULE_DECL vector4d& operator-=(vector4d& vector1, const vector4d& vector2);
            friend HEX3D_CORE_MODULE_DECL vector4d& operator*=(vector4d& vector, float scalar);
            friend HEX3D_CORE_MODULE_DECL vector4d& operator/=(vector4d& vector, float scalar);

            friend HEX3D_CORE_MODULE_DECL std::ostream& operator<<(std::ostream& ostream, const vector4d& vector);

        private:
            float m_x;
            float m_y;
            float m_z;
            float m_w;
        };

        template <unsigned int Rows, unsigned int Columns>
        class /*HEX3D_CORE_MODULE_DECL*/ matrix_c
        {
        public:
            matrix_c()
            {
                for (unsigned int i = 0; i < Rows; ++i)
                    for (unsigned int j = 0; j < Columns; ++j)
                        if (i == j)
                            elements[j][i] = 1.0f;
                        else
                            elements[j][i] = 0.0f;
            }

            matrix_c(std::initializer_list<float> list)
            {
                auto iterator = list.begin();
                for (unsigned int i = 0; i < Rows; ++i)
                    for (unsigned int j = 0; j < Columns; ++j)
                    {
                        if (iterator == list.end())
                            elements[j][i] = 0.0f;
                        else
                            elements[j][i] = *(iterator++);
                    }
            }

            // copy operations
            matrix_c(const matrix_c& other) = default;
            matrix_c& operator=(const matrix_c& other) = default;

            // move operations
            matrix_c(matrix_c&& other) noexcept = default;
            matrix_c& operator=(matrix_c&& other) noexcept = default;

            bool is_identity() const
            {
                for (unsigned int i = 0; i < Rows; ++i)
                    for (unsigned int j = 0; j < Columns; ++j)
                        if (i == j)
                        {
                            if (elements[j][i] != 1.0f)
                                return false;
                        }
                        else
                        {
                            if (elements[j][i] != 0.0f)
                                return false;
                        }
                return true;
            }

            void set_to_identity()
            {
                for (unsigned int i = 0; i < Rows; ++i)
                    for (unsigned int j = 0; j < Columns; ++j)
                        if (i == j)
                            elements[j][i] = 1.0f;
                        else
                            elements[j][i] = 0.0f;
            }

            matrix_c<Columns, Rows> transposed() const
            {
                matrix_c<Columns, Rows> result;
                for (unsigned int i = 0; i < Rows; ++i)
                    for (unsigned int j = 0; j < Columns; ++j)
                        result.elements[i][j] = elements[j][i];
                return result;
            }

            void fill(float value)
            {
                for (unsigned int i = 0; i < Rows; ++i)
                    for (unsigned int j = 0; j < Columns; ++j)
                        elements[j][i] = value;
            }

            static matrix_c identity()
            {
                return matrix_c<Rows, Columns>();
            }

            static matrix_c<4, 4> rotation(const vector3d& yaw_pitch_roll)
            {
                internal_matrix_t mat;
                cml::quaternionf_p quat;
                cml::quaternion_rotation_euler(quat, yaw_pitch_roll.x(), yaw_pitch_roll.y(), yaw_pitch_roll.z(), cml::euler_order_xyz);
                cml::matrix_rotation_quaternion(mat, quat);
                return from_cml(mat);
            }

            static matrix_c<4, 4> translation(const vector3d& vector)
            {
                internal_matrix_t mat;
                cml::matrix_translation(mat, vector.x(), vector.y(), vector.z());
                return from_cml(mat);
            }

            static matrix_c<4, 4> scale(const vector3d& vector)
            {
                internal_matrix_t mat;
                cml::matrix_scale(mat, vector.x(), vector.y(), vector.z());
                return from_cml(mat);
            }

            static matrix_c<4, 4> look_at_LH(const vector3d& eye_position, const vector3d& target_position, const vector3d& up_direction)
            {
                internal_matrix_t mat;
                cml::matrix_look_at_LH(mat, eye_position.x(), eye_position.y(), eye_position.z(), target_position.x(), target_position.y(), target_position.z(), up_direction.x(), up_direction.y(), up_direction.z());
                return from_cml(mat);
            }

            static matrix_c<4, 4> look_at_RH(const vector3d& eye_position, const vector3d& target_position, const vector3d& up_direction)
            {
                internal_matrix_t mat;
                cml::matrix_look_at_RH(mat, eye_position.x(), eye_position.y(), eye_position.z(), target_position.x(), target_position.y(), target_position.z(), up_direction.x(), up_direction.y(), up_direction.z());
                return from_cml(mat);
            }

            static matrix_c<4, 4> perspective_projection_LH(float vertical_FOV, float aspect_ratio, float near_z, float far_z)
            {
                internal_matrix_t mat;
                cml::matrix_perspective_yfov_LH(mat, vertical_FOV, aspect_ratio, near_z, far_z, cml::z_clip_zero);
                return from_cml(mat);
            }

            static matrix_c<4, 4> perspective_projection_RH(float vertical_FOV, float aspect_ratio, float near_z, float far_z)
            {
                internal_matrix_t mat;
                cml::matrix_perspective_yfov_RH(mat, vertical_FOV, aspect_ratio, near_z, far_z, cml::z_clip_zero);
                return from_cml(mat);
            }

            friend matrix_c operator+(const matrix_c& matrix1, const matrix_c& matrix2)
            {
                core_module::matrix_c<Rows, Columns> result;
                for (unsigned int i = 0; i < Rows; ++i)
                    for (unsigned int j = 0; j < Columns; ++j)
                        result.elements[j][i] = matrix1.elements[j][i] + matrix2.elements[j][i];
                return result;
            }

            friend matrix_c operator*(const matrix_c& matrix, float scalar)
            {
                core_module::matrix_c<Rows, Columns> result;
                for (unsigned int i = 0; i < Rows; ++i)
                    for (unsigned int j = 0; j < Columns; ++j)
                        result.elements[j][i] = matrix.elements[j][i] * scalar;
                return result;
            }

            friend matrix_c operator*(float scalar, const matrix_c& matrix)
            {
                core_module::matrix_c<Rows, Columns> result;
                for (unsigned int i = 0; i < Rows; ++i)
                    for (unsigned int j = 0; j < Columns; ++j)
                        result.elements[j][i] = matrix.elements[j][i] * scalar;
                return result;
            }

            template <unsigned int Rows1, unsigned int Columns1Rows2, unsigned int Columns2>
            friend matrix_c<Rows1, Columns2> operator*(const matrix_c<Rows1, Columns1Rows2>& matrix1, const matrix_c<Columns1Rows2, Columns2>& matrix2)
            {
                core_module::matrix_c<Rows1, Columns2> result;
                for (unsigned int i = 0; i < Rows1; ++i)
                    for (unsigned int j = 0; j < Columns2; ++j)
                    {
                        result.elements[j][i] = 0.0f;
                        for (unsigned int k = 0; k < Columns1Rows2; ++k)
                            result.elements[j][i] += matrix1.elements[k][i] * matrix2.elements[j][k];
                    }
                return result;
            }

            template <unsigned int Rows1, unsigned int Columns1>
            friend std::ostream& operator<<(std::ostream& ostream, const matrix_c<Rows, Columns>& matrix)
            {
                for (unsigned int i = 0; i < Rows1; ++i)
                    for (unsigned int j = 0; j < Columns1; ++j)
                    {
                        ostream << matrix.elements[j][i];
                        if (j < Columns1 - 1)
                            ostream << '\t';
                        else
                            ostream << std::endl;
                    }
                return ostream;
            }

            float elements[Columns][Rows];

        private:
            using internal_matrix_t = cml::matrix<float, cml::fixed<Rows, Columns>, cml::col_basis, cml::col_major>;
            static matrix_c<4, 4> from_cml(const cml::matrix<float, cml::fixed<4, 4>, cml::col_basis, cml::col_major>& matrix)
            {
                core_module::matrix_c<4, 4> ret;
                ret.elements[0][0] = matrix(0, 0);
                ret.elements[0][1] = matrix(0, 1);
                ret.elements[0][2] = matrix(0, 2);
                ret.elements[0][3] = matrix(0, 3);
                ret.elements[1][0] = matrix(1, 0);
                ret.elements[1][1] = matrix(1, 1);
                ret.elements[1][2] = matrix(1, 2);
                ret.elements[1][3] = matrix(1, 3);
                ret.elements[2][0] = matrix(2, 0);
                ret.elements[2][1] = matrix(2, 1);
                ret.elements[2][2] = matrix(2, 2);
                ret.elements[2][3] = matrix(2, 3);
                ret.elements[3][0] = matrix(3, 0);
                ret.elements[3][1] = matrix(3, 1);
                ret.elements[3][2] = matrix(3, 2);
                ret.elements[3][3] = matrix(3, 3);
                return ret;
            }
        };

        template <unsigned int Rows, unsigned int Columns>
        class /*HEX3D_CORE_MODULE_DECL*/ matrix_r
        {
        public:
            matrix_r();
            matrix_r(std::initializer_list<float> list);

            // copy operations
            matrix_r(const matrix_r& other) = default;
            matrix_r& operator=(const matrix_r& other) = default;

            // move operations
            matrix_r(matrix_r&& other) noexcept = default;
            matrix_r& operator=(matrix_r&& other) noexcept = default;

            bool is_identity() const;
            void set_to_identity();

            matrix_r<Columns, Rows> transposed() const;

            void fill(float value);

            static matrix_r identity();
            static HEX3D_CORE_MODULE_DECL matrix_r<4, 4> rotation(const vector3d& yaw_pitch_roll);
            static HEX3D_CORE_MODULE_DECL matrix_r<4, 4> translation(const vector3d& vector);
            static HEX3D_CORE_MODULE_DECL matrix_r<4, 4> scale(const vector3d& vector);

            static HEX3D_CORE_MODULE_DECL matrix_r<4, 4> look_at_LH(const vector3d& eye_position, const vector3d& target_position, const vector3d& up_direction);
            static HEX3D_CORE_MODULE_DECL matrix_r<4, 4> look_at_RH(const vector3d& eye_position, const vector3d& target_position, const vector3d& up_direction);

            static HEX3D_CORE_MODULE_DECL matrix_r<4, 4> perspective_projection_LH(float vertical_FOV, float aspect_ratio, float near_z, float far_z);
            static HEX3D_CORE_MODULE_DECL matrix_r<4, 4> perspective_projection_RH(float vertical_FOV, float aspect_ratio, float near_z, float far_z);

            template <unsigned int Rows1, unsigned int Columns1>
            friend matrix_r operator+(const matrix_r& matrix1, const matrix_r& matrix2);

            template <unsigned int Rows1, unsigned int Columns1>
            friend matrix_r operator*(const matrix_r& matrix, float scalar);

            template <unsigned int Rows1, unsigned int Columns1>
            friend matrix_r operator*(float scalar, const matrix_r& matrix);

            template <unsigned int Rows1, unsigned int Columns1Rows2, unsigned int Columns2>
            friend matrix_r<Rows1, Columns2> operator*(const matrix_r<Rows1, Columns1Rows2>& matrix1, const matrix_r<Columns1Rows2, Columns2>& matrix2);

            template <unsigned int Rows1, unsigned int Columns1>
            friend std::ostream& operator<<(std::ostream& ostream, const matrix_r<Rows, Columns>& matrix);

            float elements[Rows][Columns];

        private:
            using internal_matrix_t = cml::matrix<float, cml::fixed<Rows, Columns>, cml::row_basis, cml::row_major>;
            friend matrix_r<4, 4> from_cml(const cml::matrix<float, cml::fixed<4, 4>, cml::row_basis, cml::row_major>& matrix);
        };

        using matrix2x2 = matrix_c<2, 2>;
        using matrix2x3 = matrix_c<2, 3>;
        using matrix2x4 = matrix_c<2, 4>;
        using matrix3x2 = matrix_c<3, 2>;
        using matrix3x3 = matrix_c<3, 3>;
        using matrix3x4 = matrix_c<3, 4>;
        using matrix4x2 = matrix_c<4, 2>;
        using matrix4x3 = matrix_c<4, 3>;
        using matrix4x4 = matrix_c<4, 4>;

        class HEX3D_CORE_MODULE_DECL utils
        {
        public:
            static vector3d string_to_vector3d(const std::string& value);
            static std::string vector3d_to_string(const vector3d& value);
            static float string_to_float(const std::string& value);
            static std::string float_to_string(float value);
        };

        class HEX3D_CORE_MODULE_DECL pass_event
        {
        public:
            pass_event(const std::string& name, float delta_seconds, float total_seconds);

            // copy operations
            pass_event(const pass_event& other) = default;
            pass_event& operator=(const pass_event& other) = default;

            // move operations
            pass_event(pass_event&& other) noexcept = default;
            pass_event& operator=(pass_event&& other) noexcept = default;

            const std::string& name() const;
            float delta_seconds() const;
            float total_seconds() const;

        private:
            std::string m_name;
            float m_delta_seconds;
            float m_total_seconds;
        };

        class HEX3D_CORE_MODULE_DECL component
        {
        public:
            component(entity* owner = nullptr);

            // copy operations
            component(const component& other) = delete;
            component& operator=(const component& other) = delete;

            // move operations
            component(component&& other) noexcept = delete;
            component& operator=(component&& other) noexcept = delete;

            bool is_orphan() const;
            virtual void update(pass_event* pass_ev);

            virtual std::string property(const std::string& name) const;
            virtual void set_property(const std::string& name, const std::string& value);

        protected:
            entity* owner();
            std::string read_property(const std::string& name) const;
            void write_property(const std::string& name, const std::string& value);

        private:
            entity* m_owner;
            std::map<std::string, std::string> m_properties;

            friend class entity;
        };

        class HEX3D_CORE_MODULE_DECL entity
        {
        public:
            entity() = default;

            // copy operations
            entity(const entity& other);
            entity& operator=(const entity& other);

            // move operations
            entity(entity&& other) noexcept = default;
            entity& operator=(entity&& other) noexcept = default;

            // TODO: Get the following function written, unless m_components stores smart pointers instead of raw pointers ('cause then move operations will always succeed).
            // ~entity();

            component* add_component(component* comp)
            {
                for (auto current_component : m_components)
                    if (current_component == comp)
                        return nullptr;
                comp->m_owner = this;
                m_components.push_back(comp);
                return comp;
            }

            template <typename component_t>
            component* add_component()
            {
                for (auto current_component : m_components)
                {
                    component_t* ptr = dynamic_cast<component_t*>(current_component);
                    if (ptr)
                        return nullptr;
                }
                component_t* comp = new component_t(this);
                m_components.push_back(comp);
                return comp;
            }

            template <typename component_t>
            component_t* get_component()
            {
                for (auto current_component : m_components)
                {
                    component_t* ptr = dynamic_cast<component_t*>(current_component);
                    if (ptr)
                        return ptr;
                }
                return nullptr;
            }

            // TODO: Test this function, make sure the const in dynamic_cast is correct.
            template <typename component_t>
            const component_t* get_component() const
            {
                for (auto current_component : m_components)
                {
                    const component_t* ptr = dynamic_cast<const component_t*>(current_component);
                    if (ptr)
                        return ptr;
                }
                return nullptr;
            }

            virtual void update(pass_event* pass_ev);

            std::string name() const;
            void set_name(const std::string& name);

            const std::vector<entity>& children() const;
            void add_child(const entity& child);

            unsigned int component_count() const;

            virtual std::string property(const std::string& name) const;
            virtual void set_property(const std::string& name, const std::string& value);

        protected:
            std::string read_property(const std::string& name) const;
            void write_property(const std::string& name, const std::string& value);

        private:
            std::string m_name;
            std::vector<entity> m_children;
            std::vector<component*> m_components;
            std::map<std::string, std::string> m_properties;

            friend class entity_graph;
        };

        class HEX3D_CORE_MODULE_DECL transform
        {
        public:
            transform();
            transform(const vector3d& scale, const vector3d& rotation, const vector3d& translation);

            vector3d& scale();
            vector3d& rotation();
            vector3d& translation();

            const vector3d& scale() const;
            const vector3d& rotation() const;
            const vector3d& translation() const;

            matrix4x4 world_matrix() const;

        private:
            vector3d m_scale;
            vector3d m_rotation;
            vector3d m_translation;
        };

        class HEX3D_CORE_MODULE_DECL transform_comp : public component
        {
        public:
            transform_comp(entity* owner = nullptr);
            transform_comp(const vector3d& scale, const vector3d& rotation, const vector3d& translation);

            static transform_comp* create();

            core_module::transform& local_transform();
            const core_module::transform& local_transform() const;

            core_module::transform& global_transform();
            const core_module::transform& global_transform() const;

            virtual void set_property(const std::string& name, const std::string& value) override;

        private:
            core_module::transform m_local_transform;
            core_module::transform m_global_transform;
        };

        class HEX3D_CORE_MODULE_DECL entity_graph
        {
        public:
            entity_graph();
            entity_graph(const std::string& filename);

            bool is_ready() const;

            void load(const std::string& filename);
            core_module::entity* entity_by_name(const std::string& name);

            void register_component_factory_function(const std::string& name, const std::function<component*()>& func);
            void register_pass(const std::string& pass_name, const std::function<void(pass_event*)>& pass_starter, const std::function<void(pass_event*)>& pass_ender);

            void run_passes(float delta_seconds, float total_seconds);

        private:
            std::string m_filename;
            std::vector<core_module::entity> m_top_level_entities;
            std::map<std::string, std::function<component*()>> m_factory_functions;
            std::vector<std::string> m_pass_names;
            std::vector<std::function<void(pass_event*)>> m_pass_starters;
            std::vector<std::function<void(pass_event*)>> m_pass_enders;
            bool m_is_ready;

            std::vector<core_module::entity> load_recursive(const boost::property_tree::ptree& tree);
            core_module::entity* entity_by_name_recursive(std::vector<core_module::entity>& entities, const std::string& name);
            void update_entity_object(core_module::transform transform_obj, core_module::entity& parent, core_module::entity& child, pass_event* pass_ev);
            void update_entity_object(core_module::entity& parent, core_module::entity& child, pass_event* pass_ev);

            friend class core_module;
        };

    private:
        entity_graph m_entity_graph;
    };
} // namespace hex3d

#define core_module_obj (static_cast<hex3d::core_module*>(application_obj->module_obj(HEX3D_CORE_MODULE_NAME)))

extern "C" HEX3D_CORE_MODULE_DECL hex3d::module* create_module_obj();

#endif // HEX3D_CORE_MODULE_HPP
