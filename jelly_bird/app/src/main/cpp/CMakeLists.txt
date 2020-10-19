cmake_minimum_required(VERSION 3.4.1)

# build native_app_glue as a static lib
set(${CMAKE_C_FLAGS}, "${CMAKE_C_FLAGS}")
add_library(native_app_glue STATIC
    ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)

# now build app's shared lib
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++17 -Wall -Werror -Wno-unused-private-field -Wno-unused-variable")

# Export ANativeActivity_onCreate(),
# Refer to: https://github.com/android-ndk/ndk/issues/381.
set(CMAKE_SHARED_LINKER_FLAGS
    "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")

# library glm
add_subdirectory(external/glm)

# game source
file(GLOB_RECURSE mainCPP
        "*.cpp")
add_library(jelly-bird SHARED
        ${mainCPP})


target_include_directories(jelly-bird PRIVATE
    ${ANDROID_NDK}/sources/android/native_app_glue)

# add lib dependencies
target_link_libraries(jelly-bird
    android
    native_app_glue
    EGL
    GLESv3
    OpenSLES
    log
    glm)
