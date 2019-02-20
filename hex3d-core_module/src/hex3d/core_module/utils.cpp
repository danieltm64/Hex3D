#define HEX3D_CORE_MODULE_SOURCE

#include <hex3d/core_module/core_module.hpp>

namespace hex3d
{
    core_module::vector3d core_module::utils::string_to_vector3d(const std::string& value)
    {
        if (value == "<null>")
            return vector3d(0.0f, 0.0f, 0.0f);

        std::stringstream string_stream(value);
        float x, y, z;
        string_stream >> x >> y >> z;
        return vector3d(x, y, z);
    }

    std::string core_module::utils::vector3d_to_string(const vector3d& value)
    {
        return std::to_string(value.x()) + ' ' + std::to_string(value.y()) + ' ' + std::to_string(value.z());
    }

    float core_module::utils::string_to_float(const std::string& value)
    {
        if (value == "<null>")
            return 0.0f;

        std::stringstream string_stream(value);
        float x;
        string_stream >> x;
        return x;
    }

    std::string core_module::utils::float_to_string(float value)
    {
        return std::to_string(value);
    }
} // namespace hex3d
