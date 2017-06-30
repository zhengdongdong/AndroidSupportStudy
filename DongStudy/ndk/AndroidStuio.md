# 2.2或更高版本 && Gradle2.2.0或更高版本

>先说明一下, ndk-build方式与cmake方式类似，只需要将cmake文件改写为Android.mk和Appliction.mk文件。在CMakeLists.txt加载的位置将CMakeLists.txt替换为Android.mk即可, Gradle 中, 将 cmake{path file("src/main/jni/CMakeLists.txt")} 替换为 ndkBuild{path file("src/main/jni/Android.mk")}

## 先要做的事情, 下载工具

1. NDK: 这套工具集允许您为 Android 使用 C 和 C++ 代码，并提供众多平台库，让您可以管理原生 Activity 和访问物理设备组件，例如传感器和触摸输入
2. CMake: 一款外部构建工具，可与 Gradle 搭配使用来构建原生库。如果您只计划使用 ndk-build，则不需要此组件
3. LLDB: 一种调试程序，Android Studio 使用它来调试原生代码。

## 创建新项目
1. 在 Configure your new project 中选中 Include C++ support
2. 在 Customize C++ Support 中选择标准
>C++ Standard: 选择希望使用哪种C++标准, 选择Toolchain Default 会使用默认的CMake 设置

>Exceptions Support: 如果希望启动C++异常处理, 选中它. Android Stduio 会将 -fexceptions 标志添加到木块级 build.grdale 文件的 cppFlags, Gradle 会将其传递到CMake

>Runtime Type Information Support: 如果希望支持RTTI, 选中它. Android Studio 会将 -frtti 标志添加到模块级 build.gradle 文件的 cppFlags 中，Gradle 会将其传递到 CMake

3. Android Stuido 会自动创建 CMake 构建脚本 CMakeLists.txt, 并将其置于模块的根目录中, 并且自动创建一个简单的示例

## 向现有项目添加C/C++代码
1. 创建 CMake 构建脚本(CMakeLists.txt)到模块根目录 或者 ndk-build 构建脚本(Android.mk, Application.mk)
>如果现有原生库已包含CMakeLists.txt 构建脚本或使用 ndk-build 并包含 Android.mk, 可跳过此步骤

2. 配置Gradle
>要手动配置 Gradle 以关联到您的原生库，您需要将 externalNativeBuild {} 块添加到模块级 build.gradle 文件中，并使用 cmake {} 或 ndkBuild {}对其进行配置

>注：如果您想要将 Gradle 关联到现有 ndk-build 项目，请使用 ndkBuild {} 块而不是 cmake {}，并提供 Android.mk 文件的相对路径。如果 Application.mk 文件与您的 Android.mk 文件位于相同目录下，Gradle 也会包含此文件

```
android {
  
  defaultConfig {}
  buildTypes {}

  // Encapsulates your external native build configurations.
  externalNativeBuild {

    // Encapsulates your CMake build configurations.
    cmake {

      // Provides a relative path to your CMake build script.
      path "CMakeLists.txt"
    }
  }
}
```

>指定可选配置

>您可以在模块级 build.gradle 文件的 defaultConfig {} 块中配置另一个 externalNativeBuild {} 块，为 CMake 或 ndk-build 指定可选参数和标志。与 defaultConfig {} 块中的其他属性类似，您也可以在构建配置中为每个产品风味重写这些属性。

>例如，如果您的 CMake 或 ndk-build 项目定义多个原生库，您可以使用 targets 属性仅为给定产品风味构建和打包这些库中的一部分。以下代码示例说明了您可以配置的部分属性：

```
android {
  defaultConfig {
    // This block is different from the one you use to link Gradle
    // to your CMake or ndk-build script.
    externalNativeBuild {

      // For ndk-build, instead use ndkBuild {}
      cmake {

        // Passes optional arguments to CMake.
        arguments "-DANDROID_ARM_NEON=TRUE", "-DANDROID_TOOLCHAIN=clang"

        // Sets optional flags for the C compiler.
        cFlags "-D_EXAMPLE_C_FLAG1", "-D_EXAMPLE_C_FLAG2"

        // Sets a flag to enable format macro constants for the C++ compiler.
        cppFlags "-D__STDC_FORMAT_MACROS"
      }
    }
  }

  buildTypes {}

  productFlavors {
    demo {
      externalNativeBuild {
        cmake {
          // Specifies which native libraries to build and package for this
          // product flavor. If you don't configure this property, Gradle
          // builds and packages all shared object libraries that you define
          // in your CMake or ndk-build project.
          targets "native-lib-demo"
        }
      }
    }

    paid {
      externalNativeBuild {
        cmake {
          targets "native-lib-paid"
        }
      }
    }
  }

  // Use this block to link Gradle to your CMake or ndk-build script.
  externalNativeBuild {
    cmake {}
    // or ndkBuild {}
  }
}
```

>指定 ABI

>默认情况下，Gradle 会针对 NDK 支持的 ABI 将您的原生库构建到单独的 .so 文件中，并将其全部打包到您的 APK 中。如果您希望 Gradle 仅构建和打包原生库的特定 ABI 配置，您可以在模块级 build.gradle 文件中使用 ndk.abiFilters 标志指定这些配置，如下所示：

```
android {
  defaultConfig {
    externalNativeBuild {
      cmake {}
      // or ndkBuild {}
    }

    ndk {
      // Specifies the ABI configurations of your native
      // libraries Gradle should build and package with your APK.
      abiFilters 'x86', 'x86_64', 'armeabi', 'armeabi-v7a',
                   'arm64-v8a'
    }
  }
  buildTypes {}
  externalNativeBuild {}
}
```

## CMake构建脚本

1. 要指示 CMake 从原生源代码创建一个原生库，请将 cmake_minimum_required() 和 add_library() 命令添加到您的构建脚本中()

```
# Sets the minimum version of CMake required to build your native library.
# This ensures that a certain set of CMake features is available to
# your build.

cmake_minimum_required(VERSION 3.4.1)

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
             src/main/cpp/native-lib.cpp )
```

2. 为了确保 CMake 可以在编译时定位您的标头文件，您需要将 include_directories() 命令添加到 CMake 构建脚本中并指定标头的路径, CMake 使用以下规范来为库文件命名: lib库名称.so

例如，如果您在构建脚本中指定“native-lib”作为共享库的名称，CMake 将创建一个名称为 libnative-lib.so 的文件。不过，在 Java 代码中加载此库时，使用System.loadLibrary(“native-lib”);

```
add_library()

# Specifies a path to native header files.
include_directories(src/main/cpp/include/)
```

3. 添加 NDK API

>预构建的 NDK 库已经存在于 Android 平台上，因此，您无需再构建或将其打包到 APK 中。由于 NDK 库已经是 CMake 搜索路径的一部分，您甚至不需要在您的本地 NDK 安装中指定库的位置 - 只需要向 CMake 提供您希望使用的库的名称，并将其关联到您自己的原生库。

>将 find_library() 命令添加到您的 CMake 构建脚本中以定位 NDK 库，并将其路径存储为一个变量。您可以使用此变量在构建脚本的其他部分引用 NDK 库。以下示例可以定位 Android 特定的日志支持库并将其路径存储在 log-lib 中：

```
find_library( # Defines the name of the path variable that stores the
              # location of the NDK library.
              log-lib

              # Specifies the name of the NDK library that
              # CMake needs to locate.
              log )
```

>为了确保您的原生库可以在 log 库中调用函数，您需要使用 CMake 构建脚本中的 target_link_libraries() 命令关联库：

```
find_library()

# Links your native library against one or more other native libraries.
target_link_libraries( # Specifies the target library.
                       native-lib

                       # Links the log library to the target library.
                       ${log-lib} )
```

>NDK 还以源代码的形式包含一些库，您在构建和关联到您的原生库时需要使用这些代码。您可以使用 CMake 构建脚本中的 add_library() 命令，将源代码编译到原生库中。要提供本地 NDK 库的路径，您可以使用 ANDROID_NDK 路径变量，Android Studio 会自动为您定义此变量。

>以下命令可以指示 CMake 构建 android_native_app_glue.c，后者会将 NativeActivity 生命周期事件和触摸输入置于静态库中并将静态库关联到 native-lib：

```
add_library( app-glue
             STATIC
             ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c )

# You need to link static libraries against your shared native library.
target_link_libraries( native-lib app-glue ${log-lib} )
```

4. 添加其他预构建库

>添加预构建库与为 CMake 指定要构建的另一个原生库类似。不过，由于库已经预先构建，您需要使用 IMPORTED 标志告知 CMake 您只希望将库导入到项目中

```
add_library( imported-lib
             SHARED
             IMPORTED )
```

>然后，您需要使用 set_target_properties() 命令指定库的路径，如下所示

```
add_library()
set_target_properties( # Specifies the target library.
                       imported-lib

                       # Specifies the parameter you want to define.
                       PROPERTIES IMPORTED_LOCATION

                       # Provides the path to the library you want to import.
                       imported-lib/src/${ANDROID_ABI}/libimported-lib.so )
```

>为了确保 CMake 可以在编译时定位您的标头文件，您需要使用 include_directories() 命令，并包含标头文件的路径：

>(注：如果您希望打包一个并不是构建时依赖项的预构建库（例如在添加属于 imported-lib 依赖项的预构建库时），则不需要执行以下说明来关联库)

```
include_directories( imported-lib/include/ )
```

>要将预构建库关联到您自己的原生库，请将其添加到 CMake 构建脚本的 target_link_libraries() 命令中

```
target_link_libraries( native-lib imported-lib app-glue ${log-lib} )
```


# 其他版本(待测试)

1. 创建 jni 目录, 并将一系列 c/mk等文件创建好
2. gradle 中配置 
```
defaultConfig {
  ...
  ndk {
    moduleName "MyJni" // 生成的so包名称
    abiFilters 'armeabi-v7a', 'armeabi'
  }
}
```
3. gradle.properties 中添加配置 android.useDeprecatedNdk=true 



