#1.
#你可以添加 CMake 命令来配置你的构建脚本了。为了让 CMake 将源代码（native source code）编译成 native library。
#需要在编译文件中添加 cmake_minimum_required() 和 add_library()

# Sets the minimum version of CMake required to build your native library.
# This ensures that a certain set of CMake features is available to
# your build.

cmake_minimum_required(VERSION 3.8.0)

# Specifies a library name, specifies whether the library is STATIC or
# SHARED, and provides relative paths to the source code. You can
# define multiple libraries by adding multiple add.library() commands,
# and CMake builds them for you. When you build your app, Gradle
# automatically packages shared libraries with your APK.

add_library( # Specifies the name of the library.
        native-lib

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        src/main/cpp/native-lib.cpp
        src/main/cpp/common.cpp
        src/main/cpp/pointer.cpp
        src/main/cpp/pointer-array.cpp
        src/main/cpp/time-date.cpp
        src/main/cpp/reference.cpp
        src/main/cpp/cstring.cpp
        src/main/cpp/place-holder.cpp
        src/main/cpp/exception.cpp
        src/main/cpp/dynamic-ram.cpp
        src/main/cpp/test-namespace.cpp
        src/main/cpp/test-template.cpp
        src/main/cpp/test-define.cpp
        src/main/cpp/struct.cpp
        src/main/cpp/typedef.cpp
        src/main/cpp/test-class.cpp
        src/main/cpp/file-stream.cpp)

#2.
#当你使用 add_library()，将一个源文件（source file）或库添加到你的 CMake 构建脚本，同步你的项目，
#然后你会发现 Android studio 将关联的头文件也显示了处理。然而，为了让 CMake 在编译时期能定位到你的头文件，
#你需要在 CMake 构建脚本中添加 include_directories() 命令，并指定头文件路径：

# Specifies a path to native header files.
include_directories(src/main/cpp/include/)

#然后，按照约定，CMake 会将生成的 library 命名为下面的形式：
#lib*library-name*.so
#
#比如，如果你在构建脚本中，将 library 命名为 “native-lib”，那么 CMake 会创建叫 libnative-lib.so的文件。
#但是，当你将 library 加载到 Java 代码中的时候， 你需要使用在 CMake 中指定的名称：
#static {
#        System.loadLibrary(“native-lib”);
#}
#如果你将 CMake 脚本里面的 library 重命名了，或者移除了。你需要清理一下你的工程。在 IDE 的菜单栏中选择 Build > Clean Project。

#3.
#添加 NDK APIs
#Android NDK 提供了一些有用的 native APIs。将 NDK librarys 添加到 CMakeLists.txt 脚本文件中，就可以使用这些 API 了。
#
#预编译的 NDK librarys 已经存在在 Android 平台中了，所以你不需要编译它们，或者是将其打包到你的 APK 中。
#因为这些 NDK librarys 已经是 CMake 搜索路径的一部分，你甚至不需要提供你本地安装的 NDK 路径。你只需要向 CMake 提供你想使用的 library 名字。
#
#将 find_library() 命令添加到你的 CMake 构建脚本中，这样就可以定位 NDK library 的位置，并将其位置存储在一个变量之中。
#你可以在构建脚本的其他地方使用这个变量，来代指 NDK library。
#下面的示例代码将 Android-specific log support library 的位置存储到变量 log-lib 中

find_library( # Defines the name of the path variable that stores the
        # location of the NDK library.
        log-lib

        # Specifies the name of the NDK library that
        # CMake needs to locate.
        log)
#4.
#NDK 同样也包含一些只包含源码的 library，这些就需要你去编译，然后链接到你的本地库（native library）。
#你可以在 CMake 构建脚本中使用 add_library() 命令将源码编译进本地库。
#这时就需要提供你的本地 NDK 安装路径，通常将该路径保存在 ANDROID_NDK 变量中，这样 Android Studio 可以自动为你识别。
#
#下面的命令告诉 CMake 去构建 android_native_app_glue.c，这个命令可以管理 NativeActivity的生命周期以及点击输入，
#并将其导入静态库中，然后将其链接至 native-lib：

add_library(app-glue
        STATIC
        ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)

# You need to link static libraries against your shared native library.
target_link_libraries(native-lib
        app-glue
        ${log-lib})

#5.
#添加预编译库和添加本地库（native library）类似。由于预编译库是已经构建好的，你想就要使用 IMPORTED 标志去告诉 CMake ，
#你只需要将其导入到你的项目中即可：

#add_library( imported-lib
#             SHARED
#             IMPORTED )

#然后你需要使用 set_target_properties() 命令去指定库的路径，就像下面的代码那样

#set_target_properties( # Specifies the target library.
#                       imported-lib
#
#                       # Specifies the parameter you want to define.
#                       PROPERTIES IMPORTED_LOCATION
#
#                       # Provides the path to the library you want to import.
#                       imported-lib/src/${ANDROID_ABI}/libimported-lib.so )

#为了让 CMake 在编译时期能找到你的头文件，你需要使用 include_directories() 命令，并且将你的头文件地址传进去：

#include_directories( imported-lib/include/ )

#6.
#在 CMake 构建脚本中使用 target_link_libraries() 命令，将预构建库与你本地库相关联：
target_link_libraries(native-lib
        app-glue
        ${log-lib})