/*
#define HEX3D_CORE_MODULE_SOURCE

#include <hex3d/core_module/core_module.hpp>
*/

namespace hex3d
{
    core_module::matrix_c<4, 4> from_cml(const cml::matrix<float, cml::fixed<4, 4>, cml::col_basis, cml::col_major>& matrix)
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

    template <unsigned int Rows1, unsigned int Columns1>
    core_module::matrix_c<Rows1, Columns1>::matrix_c()
    {
        for (unsigned int i = 0; i < Rows1; ++i)
            for (unsigned int j = 0; j < Columns1; ++j)
                if (i == j)
                    elements[j][i] = 1.0f;
                else
                    elements[j][i] = 0.0f;
    }

    template <unsigned int Rows1, unsigned int Columns1>
    core_module::matrix_c<Rows1, Columns1>::matrix_c(std::initializer_list<float> list)
    {
        auto iterator = list.begin();
        for (unsigned int i = 0; i < Rows1; ++i)
            for (unsigned int j = 0; j < Columns1; ++j)
            {
                if (iterator == list.end())
                    elements[j][i] = 0.0f;
                else
                    elements[j][i] = *(iterator++);
            }
    }

    template <unsigned int Rows1, unsigned int Columns1>
    bool core_module::matrix_c<Rows1, Columns1>::is_identity() const
    {
        for (unsigned int i = 0; i < Rows1; ++i)
            for (unsigned int j = 0; j < Columns1; ++j)
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

    template <unsigned int Rows1, unsigned int Columns1>
    void core_module::matrix_c<Rows1, Columns1>::set_to_identity()
    {
        for (unsigned int i = 0; i < Rows1; ++i)
            for (unsigned int j = 0; j < Columns1; ++j)
                if (i == j)
                    elements[j][i] = 1.0f;
                else
                    elements[j][i] = 0.0f;
    }

    template <unsigned int Rows1, unsigned int Columns1>
    core_module::matrix_c<Columns1, Rows1> core_module::matrix_c<Rows1, Columns1>::transposed() const
    {
        matrix_c<Columns1, Rows1> result;
        for (unsigned int i = 0; i < Rows1; ++i)
            for (unsigned int j = 0; j < Columns1; ++j)
                result.elements[i][j] = elements[j][i];
        return result;
    }

    template <unsigned int Rows1, unsigned int Columns1>
    void core_module::matrix_c<Rows1, Columns1>::fill(float value)
    {
        for (unsigned int i = 0; i < Rows1; ++i)
            for (unsigned int j = 0; j < Columns1; ++j)
                elements[j][i] = value;
    }

    template <unsigned int Rows1, unsigned int Columns1>
    core_module::matrix_c<Rows1, Columns1> core_module::matrix_c<Rows1, Columns1>::identity()
    {
        return matrix_c<Rows1, Columns1>();
    }

    template <>
    core_module::matrix_c<4, 4> core_module::matrix_c<4, 4>::rotation(const vector3d& yaw_pitch_roll)
    {
        internal_matrix_t mat;
        cml::quaternionf_p quat;
        cml::quaternion_rotation_euler(quat, yaw_pitch_roll.x(), yaw_pitch_roll.y(), yaw_pitch_roll.z(), cml::euler_order_xyz);
        cml::matrix_rotation_quaternion(mat, quat);
        return from_cml(mat);
    }

    template <>
    core_module::matrix_c<4, 4> core_module::matrix_c<4, 4>::translation(const vector3d& vector)
    {
        internal_matrix_t mat;
        cml::matrix_translation(mat, vector.x(), vector.y(), vector.z());
        return from_cml(mat);
    }

    template <>
    core_module::matrix_c<4, 4> core_module::matrix_c<4, 4>::scale(const vector3d& vector)
    {
        internal_matrix_t mat;
        cml::matrix_scale(mat, vector.x(), vector.y(), vector.z());
        return from_cml(mat);
    }

    template <>
    core_module::matrix_c<4, 4> core_module::matrix_c<4, 4>::look_at_LH(const vector3d& eye_position, const vector3d& target_position, const vector3d& up_direction)
    {
        internal_matrix_t mat;
        cml::matrix_look_at_LH(mat, eye_position.x(), eye_position.y(), eye_position.z(), target_position.x(), target_position.y(), target_position.z(), up_direction.x(), up_direction.y(), up_direction.z());
        return from_cml(mat);
    }

    template <>
    core_module::matrix_c<4, 4> core_module::matrix_c<4, 4>::look_at_RH(const vector3d& eye_position, const vector3d& target_position, const vector3d& up_direction)
    {
        internal_matrix_t mat;
        cml::matrix_look_at_RH(mat, eye_position.x(), eye_position.y(), eye_position.z(), target_position.x(), target_position.y(), target_position.z(), up_direction.x(), up_direction.y(), up_direction.z());
        return from_cml(mat);
    }

    template <>
    core_module::matrix_c<4, 4> core_module::matrix_c<4, 4>::perspective_projection_LH(float vertical_FOV, float aspect_ratio, float near_z, float far_z)
    {
        internal_matrix_t mat;
        cml::matrix_perspective_yfov_LH(mat, vertical_FOV, aspect_ratio, near_z, far_z, cml::z_clip_zero);
        return from_cml(mat);
    }

    template <>
    core_module::matrix_c<4, 4> core_module::matrix_c<4, 4>::perspective_projection_RH(float vertical_FOV, float aspect_ratio, float near_z, float far_z)
    {
        internal_matrix_t mat;
        cml::matrix_perspective_yfov_RH(mat, vertical_FOV, aspect_ratio, near_z, far_z, cml::z_clip_zero);
        return from_cml(mat);
    }

    template <unsigned int Rows1, unsigned int Columns1>
    core_module::matrix_c<Rows1, Columns1> operator+(const core_module::matrix_c<Rows1, Columns1>& matrix1, const core_module::matrix_c<Rows1, Columns1>& matrix2)
    {
        core_module::matrix_c<Rows1, Columns1> result;
        for (unsigned int i = 0; i < Rows1; ++i)
            for (unsigned int j = 0; j < Columns1; ++j)
                result.elements[j][i] = matrix1.elements[j][i] + matrix2.elements[j][i];
        return result;
    }

    template <unsigned int Rows1, unsigned int Columns1>
    core_module::matrix_c<Rows1, Columns1> operator*(const core_module::matrix_c<Rows1, Columns1>& matrix, float scalar)
    {
        core_module::matrix_c<Rows1, Columns1> result;
        for (unsigned int i = 0; i < Rows1; ++i)
            for (unsigned int j = 0; j < Columns1; ++j)
                result.elements[j][i] = matrix.elements[j][i] * scalar;
        return result;
    }

    template <unsigned int Rows1, unsigned int Columns1>
    core_module::matrix_c<Rows1, Columns1> operator*(float scalar, const core_module::matrix_c<Rows1, Columns1>& matrix)
    {
        core_module::matrix_c<Rows1, Columns1> result;
        for (unsigned int i = 0; i < Rows1; ++i)
            for (unsigned int j = 0; j < Columns1; ++j)
                result.elements[j][i] = matrix.elements[j][i] * scalar;
        return result;
    }

    template <unsigned int Rows1, unsigned int Columns1Rows2, unsigned int Columns2>
    core_module::matrix_c<Rows1, Columns2> operator*(const core_module::matrix_c<Rows1, Columns1Rows2>& matrix1, const core_module::matrix_c<Columns1Rows2, Columns2>& matrix2)
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
    std::ostream& operator<<(std::ostream& ostream, const core_module::matrix_c<Rows1, Columns1>& matrix)
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
} // namespace hex3d
