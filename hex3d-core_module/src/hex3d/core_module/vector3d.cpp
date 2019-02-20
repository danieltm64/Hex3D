#define HEX3D_CORE_MODULE_SOURCE

#include <hex3d/core_module/core_module.hpp>

namespace hex3d
{
    core_module::vector3d::vector3d()
        : m_x(0.0f)
        , m_y(0.0f)
        , m_z(0.0f)
    {
    }

    core_module::vector3d::vector3d(float x, float y, float z)
        : m_x(x)
        , m_y(y)
        , m_z(z)
    {
    }

    float core_module::vector3d::x() const
    {
        return m_x;
    }

    void core_module::vector3d::set_x(float x)
    {
        m_x = x;
    }

    float core_module::vector3d::y() const
    {
        return m_y;
    }

    void core_module::vector3d::set_y(float y)
    {
        m_y = y;
    }

    float core_module::vector3d::z() const
    {
        return m_z;
    }

    void core_module::vector3d::set_z(float z)
    {
        m_z = z;
    }

    core_module::vector2d core_module::vector3d::xy() const
    {
        return vector2d(m_x, m_y);
    }

    core_module::vector2d core_module::vector3d::xz() const
    {
        return vector2d(m_x, m_z);
    }

    core_module::vector2d core_module::vector3d::yz() const
    {
        return vector2d(m_y, m_z);
    }

    float core_module::vector3d::length() const
    {
        return std::sqrt(std::pow(m_x, 2) + std::pow(m_y, 2) + std::pow(m_z, 2));
    }

    void core_module::vector3d::normalize()
    {
        float L = length();
        m_x /= L;
        m_y /= L;
        m_z /= L;
    }

    core_module::vector3d core_module::vector3d::normalized() const
    {
        float L = length();
        return core_module::vector3d(m_x / L, m_y / L, m_z / L);
    }

    float core_module::vector3d::dot_product(const core_module::vector3d& vector1, const core_module::vector3d& vector2)
    {
        return vector1.m_x * vector2.m_x + vector1.m_y * vector2.m_y + vector1.m_z * vector2.m_z;
    }

    core_module::vector3d core_module::vector3d::cross_product(const core_module::vector3d& vector1, const core_module::vector3d& vector2)
    {
        return core_module::vector3d(vector1.m_y * vector2.m_z - vector1.m_z * vector2.m_y,
                        vector1.m_z * vector2.m_x - vector1.m_x * vector2.m_z,
                        vector1.m_x * vector2.m_y - vector1.m_y * vector2.m_x);
    }

    bool core_module::vector3d::operator==(const core_module::vector3d& other) const
    {
        return m_x == other.m_x && m_y == other.m_y && m_z == other.m_z;
    }

    bool core_module::vector3d::operator!=(const core_module::vector3d& other) const
    {
        return m_x != other.m_x || m_y != other.m_y || m_z != other.m_z;
    }

    core_module::vector3d operator+(const core_module::vector3d& vector1, const core_module::vector3d& vector2)
    {
        return core_module::vector3d(vector1.m_x + vector2.m_x, vector1.m_y + vector2.m_y, vector1.m_z + vector2.m_z);
    }

    core_module::vector3d operator-(const core_module::vector3d& vector1, const core_module::vector3d& vector2)
    {
        return core_module::vector3d(vector1.m_x - vector2.m_x, vector1.m_y - vector2.m_y, vector1.m_z - vector2.m_z);
    }

    core_module::vector3d operator*(float scalar, const core_module::vector3d& vector)
    {
        return core_module::vector3d(vector.m_x * scalar, vector.m_y * scalar, vector.m_z * scalar);
    }

    core_module::vector3d operator*(const core_module::vector3d& vector, float scalar)
    {
        return core_module::vector3d(vector.m_x * scalar, vector.m_y * scalar, vector.m_z * scalar);
    }

    core_module::vector3d operator/(const core_module::vector3d& vector, float scalar)
    {
        return core_module::vector3d(vector.m_x / scalar, vector.m_y / scalar, vector.m_z / scalar);
    }

    core_module::vector3d& operator+=(core_module::vector3d& vector1, const core_module::vector3d& vector2)
    {
        vector1.m_x += vector2.m_x;
        vector1.m_y += vector2.m_y;
        vector1.m_z += vector2.m_z;
        return vector1;
    }

    core_module::vector3d& operator-=(core_module::vector3d& vector1, const core_module::vector3d& vector2)
    {
        vector1.m_x -= vector2.m_x;
        vector1.m_y -= vector2.m_y;
        vector1.m_z -= vector2.m_z;
        return vector1;
    }

    core_module::vector3d& operator*=(core_module::vector3d& vector, float scalar)
    {
        vector.m_x *= scalar;
        vector.m_y *= scalar;
        vector.m_z *= scalar;
        return vector;
    }

    core_module::vector3d& operator/=(core_module::vector3d& vector, float scalar)
    {
        vector.m_x /= scalar;
        vector.m_y /= scalar;
        vector.m_z /= scalar;
        return vector;
    }

    std::ostream& operator<<(std::ostream& ostream, const core_module::vector3d& vector)
    {
        ostream << '(' << vector.m_x << ',' << vector.m_y << ',' << vector.m_z << ')';
        return ostream;
    }
} // namespace hex3d
