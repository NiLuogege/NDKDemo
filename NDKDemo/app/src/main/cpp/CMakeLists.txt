# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.18.1)

# Declares and names the project.

project("ndkdemo")


# 指定源码文件夹， inc 是放头文件的， giflib是完整的giflib库
include_directories(inc)

# 引入所有gif 源文件
file(GLOB_RECURSE GIF_DIRECTORIES giflib/*.*)

# 搜索自动目录下的所有源代码文件 src 路径下，并存储在 SRC_LIST 变量中
aux_source_directory(src SRC_LIST)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

# 指定生成的库的名称、类型、源码
add_library( # 设置生成库的名称
        ndkdemo
        # 设置生成库的类型（SHARED 动态库，STATIC 静态库）
        SHARED
        # gif 源文件
        ${GIF_DIRECTORIES}
        # 指定源码的路径
        ${SRC_LIST})


# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
        ndkdemo

        # Links the target library to the log library
        # included in the NDK.
        ${log-lib}

        # 引入下面这俩才能使用assert_manager.h 和 asset_manager_jni.h相关功能
        jnigraphics
        android
        )