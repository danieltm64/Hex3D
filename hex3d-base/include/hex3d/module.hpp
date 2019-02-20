#ifndef HEX3D_MODULE_HPP
#define HEX3D_MODULE_HPP

#include <string>

#include <boost/any.hpp>

namespace hex3d
{
    class module
    {
    public:
        module() : m_is_ready(false) {}

        // copy operations
        module(const module& other) = delete;
        module& operator=(const module& other) = delete;

        // move operations
        module(module&& other) noexcept = delete;
        module& operator=(module&& other) noexcept = delete;

        virtual bool initialize() = 0;
        virtual void send_message(const char* name, const boost::any& input) {}
        bool is_ready() const {return m_is_ready;}
        virtual int run() = 0;
        virtual void update(float delta_seconds, float total_seconds) = 0;
        virtual const char* name() {return "hex3d/module";}

    protected:
        bool m_is_ready;
    };
} // namespace hex3d

#endif // HEX3D_MODULE_HPP
