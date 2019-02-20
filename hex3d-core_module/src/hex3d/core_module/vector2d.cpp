#define HEX3D_CORE_MODULE_SOURCE

#include <hex3d/core_module/core_module.hpp>

namespace hex3d
{
    core_module::vector2d::vector2d()
        : m_x(0.0f)
        , m_y(0.0f)
    {
    }

    core_module::vector2d::vector2d(float x, float y)
        : m_x(x)
        , m_y(y)
    {
    }

    float core_module::vector2d::x() const
    {
        return m_x;
    }

    void core_module::vector2d::set_x(float x)
    {
        m_x = x;
    }

    float core_module::vector2d::y() const
    {
        return m_y;
    }

    void core_module::vector2d::set_y(float y)
    {
        m_y = y;
    }

    float core_module::vector2d::length() const
    {
        return std::sqrt(std::pow(m_x, 2) + std::pow(m_y, 2));
    }

    void core_module::vector2d::normalize()
    {
        float L = length();
        m_x /= L;
        m_y /= L;
    }

    core_module::vector2d core_module::vector2d::normalized() const
    {
        float L = length();
        return vector2d(m_x / L, m_y / L);
    }

    float core_module::vector2d::dot_product(const core_module::vector2d& vector1, const core_module::vector2d& vector2)
    {
        return vector1.m_x * vector2.m_x + vector1.m_y * vector2.m_y;
    }

    bool core_module::vector2d::operator==(const core_module::vector2d& other) const
    {
        return m_x == other.m_x && m_y == other.m_y;
    }

    bool core_module::vector2d::operator!=(const core_module::vector2d& other) const
    {
        return m_x != other.m_x || m_y != other.m_y;
    }

    core_module::vector2d operator+(const core_module::vector2d& vector1, const core_module::vector2d& vector2)
    {
        return core_module::vector2d(vector1.m_x + vector2.m_x, vector1.m_y + vector2.m_y);
    }

    core_module::vector2d operator-(const core_module::vector2d& vector1, const core_module::vector2d& vector2)
    {
        return core_module::vector2d(vector1.m_x - vector2.m_x, vector1.m_y - vector2.m_y);
    }

    core_module::vector2d operator*(float scalar, const core_module::vector2d& vector)
    {
        return core_module::vector2d(vector.m_x * scalar, vector.m_y * scalar);
    }

    core_module::vector2d operator*(const core_module::vector2d& vector, float scalar)
    {
        return core_module::vector2d(vector.m_x * scalar, vector.m_y * scalar);
    }

    core_module::vector2d operator/(const core_module::vector2d& vector, float scalar)
    {
        return core_module::vector2d(vector.m_x / scalar, vector.m_y / scalar);
    }

    core_module::vector2d& operator+=(core_module::vector2d& vector1, const core_module::vector2d& vector2)
    {
        vector1.m_x += vector2.m_x;
        vector1.m_y += vector2.m_y;
        return vector1;
    }

    core_module::vector2d& operator-=(core_module::vector2d& vector1, const core_module::vector2d& vector2)
    {
        vector1.m_x -= vector2.m_x;
        vector1.m_y -= vector2.m_y;
        return vector1;
    }

    core_module::vector2d& operator*=(core_module::vector2d& vector, float scalar)
    {
        vector.m_x *= scalar;
        vector.m_y *= scalar;
        return vector;
    }

    core_module::vector2d& operator/=(core_module::vector2d& vector, float scalar)
    {
        vector.m_x /= scalar;
        vector.m_y /= scalar;
        return vector;
    }

    std::ostream& operator<<(std::ostream& ostream, const core_module::vector2d& vector)
    {
        ostream << '(' << vector.m_x << ',' << vector.m_y << ')';
        return ostream;
    }
} // namespace hex3d
