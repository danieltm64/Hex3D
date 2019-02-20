#ifndef HEX3D_CORE_MODULE_CONFIG_HPP
#define HEX3D_CORE_MODULE_CONFIG_HPP

#include <boost/predef.h>

#include <hex3d/globals.hpp>

#if defined(HEX3D_ALL_DYN_LINK) || defined(HEX3D_CORE_MODULE_DYN_LINK)
# if defined(HEX3D_CORE_MODULE_SOURCE)
#   define HEX3D_CORE_MODULE_DECL BOOST_SYMBOL_EXPORT
# else
#   define HEX3D_CORE_MODULE_DECL BOOST_SYMBOL_IMPORT
# endif
#else
# define HEX3D_CORE_MODULE_DECL
#endif

#endif // HEX3D_CORE_MODULE_CONFIG_HPP
