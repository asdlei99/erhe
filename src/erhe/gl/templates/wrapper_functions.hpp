{AUTOGENERATION_WARNING}

#pragma once

#if defined(_WIN32)
#   ifndef _CRT_SECURE_NO_WARNINGS
#       define _CRT_SECURE_NO_WARNINGS
#   endif
#   ifndef WIN32_LEAN_AND_MEAN
#       define WIN32_LEAN_AND_MEAN
#   endif
#   define VC_EXTRALEAN
#   ifndef STRICT
#       define STRICT
#   endif
#   ifndef NOMINMAX
#       define NOMINMAX       // Macros min(a,b) and max(a,b)
#   endif
//#   include <windows.h>
#endif

#if defined(ERHE_WINDOW_LIBRARY_MANGO)
#   define MANGO_OPENGL_DISABLE_PLATFORM_API 1
#   include "mango/opengl/opengl.hpp"
#   undef MANGO_OPENGL_DISABLE_PLATFORM_API
#else
#   include <GL/glcorearb.h>
#   define GL_GLEXT_PROTOTYPES 1
#   include <GL/glext.h>
#   undef GL_GLEXT_PROTOTYPES
#endif

#include "erhe/gl/wrapper_enums.hpp"

namespace gl
{{

{WRAPPER_FUNCTION_DECLARATIONS}

}} // namespace gl
