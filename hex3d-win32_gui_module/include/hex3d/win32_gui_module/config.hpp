#ifndef HEX3D_WIN32_GUI_MODULE_CONFIG_HPP
#define HEX3D_WIN32_GUI_MODULE_CONFIG_HPP

#include <hex3d/globals.hpp>

#include <boost/predef.h>

#if defined(HEX3D_ALL_DYN_LINK) || defined(HEX3D_WIN32_GUI_MODULE_DYN_LINK)
# if defined(HEX3D_WIN32_GUI_MODULE_SOURCE)
#   define HEX3D_WIN32_GUI_MODULE_DECL BOOST_SYMBOL_EXPORT
# else
#   define HEX3D_WIN32_GUI_MODULE_DECL BOOST_SYMBOL_IMPORT
# endif
#else
# define HEX3D_WIN32_GUI_MODULE_DECL
#endif

#endif // HEX3D_WIN32_GUI_MODULE_CONFIG_HPP
