{AUTOGENERATION_WARNING}

#include "erhe_gl/wrapper_functions.hpp"
#include "erhe_gl/enum_string_functions.hpp"
#include "erhe_gl/dynamic_load.hpp"
#include "erhe_gl/gl_log.hpp"

#include <spdlog/spdlog.h>

#include <cassert>
#include <memory>

namespace gl {{

extern void check_error();

auto glbitfield(const ::GLbitfield value) -> ::GLbitfield
{{
    return value;
}}

{ENUM_HELPER_DEFINITIONS}

{WRAPPER_FUNCTION_DEFINITIONS}

}} // namespace gl
