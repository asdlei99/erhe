@rem rd /S /Q build

cmake ^
    -G "Visual Studio 17 2022" ^
    -A x64 ^
    -Thost=x64 ^
    -B build ^
    -S . ^
    -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ^
    -Wno-dev ^
    -DERHE_PNG_LIBRARY=mango ^
    -DERHE_FONT_RASTERIZATION_LIBRARY=freetype ^
    -DERHE_TEXT_LAYOUT_LIBRARY=harfbuzz ^
    -DERHE_WINDOW_LIBRARY=glfw ^
    -DERHE_RAYTRACE_LIBRARY=embree ^
        -DEMBREE_ISPC_SUPPORT=FALSE ^
        -DEMBREE_TASKING_SYSTEM=INTERNAL ^
        -DEMBREE_TUTORIALS=OFF ^
        -DEMBREE_STATIC_LIB=ON ^
    -DERHE_PHYSICS_LIBRARY=bullet ^
    -DERHE_PROFILE_LIBRARY=none ^
    -DERHE_GLTF_LIBRARY=none ^
    -DERHE_XR_LIBRARY=OpenXR
