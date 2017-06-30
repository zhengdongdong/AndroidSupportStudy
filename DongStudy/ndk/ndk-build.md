# NDK-Build

> Android.mk 文件，该文件定义特定于个别模块或库的属性。 
> Application.mk 文件，该文件为应用中使用的所有模块定义属性。

## Android.mk

Android.mk 文件位于项目 jni/ 目录的子目录中，用于向构建系统描述源文件和共享库。 它实际上是构建系统解析一次或多次的微小 GNU makefile 片段。 

Android.mk 文件用于定义 Application.mk、构建系统和环境变量所未定义的项目范围设置。 它还可替换特定模块的项目范围设置。

Android.mk 的语法用于将源文件分组为模块。 模块是静态库、共享库或独立可执行文件。 可在每个 Android.mk 文件中定义一个或多个模块，也可在多个模块中使用同一个源文件。 构建系统只会将共享库放入应用软件包。 此外，静态库可生成共享库。

除了封装库之外，构建系统还可为您处理各种其他详细信息。例如，您无需在 Android.mk 文件中列出标头文件或生成的文件之间的显式依赖关系。

### 一个最基本的 Android.mk

```
# 此变量表示源文件在开发树中的位置, 构建系统提供红函数 my-dir 将返回当前目录(包含Android.mk文件本身的目录)的路径 
LOCAL_PATH :=  $(call my-dir)

# CLEAR_VARS 变量，其值由构建系统提供, 变量指向特殊的GNU Makefile, 可清除许多 LOCAL_XXX 变量(不会清除LOCAL_PATH)
include $(CLEAR_VARS)

# LOCAL_MODULE 构建木块的名称, 每个模块只一个此变量. 每个模块名称必须唯一(默认以lib 开头)
LOCAL_MODULE :=  hello_jni
# LOCAL_SRC_FILE 枚举源文件, 空格分隔多个文件(也可以是so文件, 表示使用预构建库, so时下面include $(PREBUILT_SHARED_LIBRARY), 引入so包)
LOCAL_SRC_FILES :=  hello_jni.c

....

# BUILD_SHARED_LIBRARY 变量指向 GNU Makefile 脚本, 用于收集最近include后再LOCAL_XXX 变量中定义的所有信息, 此脚本确定要构建的内容及其操作方法, 使用此脚本必须至少已为 LOCAL_MODULE 和 LOCAL_SRC_FILES 赋值
include $(BUILD_SHARED_LIBRARY)

```

### NDK定义的变量

#### CLEAR_VARS -- 每个新模板最先调用

此变量指向的构建脚本用于取消定义下面“开发者定义的变量”一节中列出的几乎全部 LOCAL_XXX 变量。 在描述新模块之前，使用此变量包括此脚本。
```
include $(CLEAR_VARS)
```

#### BUILD_SHARED_LIBRARY  -- 生成 .so 扩展名的库文件

此变量指向的脚本用于收集您在 LOCAL_XXX 变量中提供的模块所有相关信息，以及确定如何从列出的源文件构建目标共享库。
```
include $(BUILD_SHARED_LIBRARY)
```

#### BUILD_STATIC_LIBRARY  -- 生成 .a 扩展名的库文件

用于构建静态库的 BUILD_SHARED_LIBRARY 的变体
```
include $(BUILD_STATIC_LIBRARY)
```

#### PREBUILT_SHARED_LIBRARY  -- 引入 .so 的库

指向用于指定预建共享库的构建脚本. 必须是指向预建共享库的单一路径，例如 foo/libfoo.so
```
include $(PREBUILT_SHARED_LIBRARY)
```

#### PREBUILT_STATIC_LIBRARY  -- 引入静态库

与 PREBUILT_SHARED_LIBRARY 相同，但用于预构建的静态库
```
include $(PREBUILT_SHARED_LIBRARY)
```

#### TARGET_ARCH

Android 开放源代码项目所指定的目标 CPU 架构的名称

#### TARGET_PLATFORM

作为构建系统目标的 [Android API 级别号](https://developer.android.google.cn/ndk/guides/stable_apis.html)
```
TARGET_PLATFORM := android-22
```

#### TARGET_ARCH_ABI

此变量将 CPU 和架构的名称存储到目标。 可以指定以下一个或多个值，使用空格作为多个目标之间的分隔符
```
TARGET_ARCH_ABI := arm64-v8a
```

#### TARGET_ABI

目标 Android API 级别与 ABI 的联接，特别适用于要针对实际设备测试特定目标系统映像的情况

例如，要指定在 Android API 级别 22 上运行的 64 位 ARM 设备：
```
TARGET_ABI := android-22-arm64-v8a
```

### 模块描述变量

#### LOCAL_PATH -- 开始

此变量用于指定当前文件的路径。必须在 Android.mk 文件的开头定义它
```
LOCAL_PATH := $(call my-dir)
```

#### LOCAL_MODULE / LOCAL_MODULE_FILENAME

此变量用于存储模块的名称

FILENAME 可让您覆盖构建系统默认用于其生成的文件的名称

例如，如果 LOCAL_MODULE 的名称为 foo，您可以强制系统将它生成的文件命名为 libnewfoo, 对于共享库模块，此示例将生成一个名为 libnewfoo.so 的文件
```
LOCAL_MODULE := foo
LOCAL_MODULE_FILENAME := libnewfoo
```

#### LOCAL_SRC_FILES

此变量包含构建系统用于生成模块的源文件列表。 只列出构建系统实际传递到编译器的文件

在构建文件中务必使用 Unix 样式的正斜杠 (/)

#### LOCAL_CPP_EXTENSION

可以使用此可选变量为 C++ 源文件指明 .cpp 以外的文件扩展名。 例如，以下行会将扩展名改为 .cxx。（设置必须包含点。）
```
LOCAL_CPP_EXTENSION := .cxx
```
从 NDK r7 开始，您可以使用此变量指定多个扩展名。例如：
```
LOCAL_CPP_EXTENSION := .cxx .cpp .cc
```

#### LOCAL_CPP_FEATURES

可以使用此可选变量指明您的代码依赖于特定 C++ 功能。它在构建过程中启用正确的编译器和链接器标志。 对于预构建的库，此变量还可声明二进制文件依赖哪些功能，从而帮助确保最终关联正确工作。 建议使用此变量，而不要直接在 LOCAL_CPPFLAGS 定义中启用 -frtti 和 -fexceptions。

使用此变量可让构建系统对每个模块使用适当的标志。使用 LOCAL_CPPFLAGS 会导致编译器对所有模块使用所有指定的标志，而不管实际需求如何。

例如，要指示您的代码使用 RTTI（运行时类型信息），请编写：
```
LOCAL_CPP_FEATURES := rtti
```
要指示您的代码使用 C++ 异常，请编写：
```
LOCAL_CPP_FEATURES := exceptions
```

您还可为此变量指定多个值。例如：
```
LOCAL_CPP_FEATURES := rtti features
```

#### LOCAL_C_INCLUDES

可以使用此可选变量指定相对于 NDK root 目录的路径列表，以便在编译所有源文件（C、C++ 和 Assembly）时添加到 include 搜索路径。 例如：
```
LOCAL_C_INCLUDES := sources/foo
甚至
LOCAL_C_INCLUDES := $(LOCAL_PATH)//foo
```
在通过 LOCAL_CFLAGS 或 LOCAL_CPPFLAGS 设置任何对应的 include 标志之前定义此变量。

#### LOCAL_LDLIBS

此变量包含在构建共享库或可执行文件时要使用的其他链接器标志列表。 它可让您使用 -l 前缀传递特定系统库的名称。 例如，以下示例指示链接器生成在加载时链接到 /system/lib/libz.so 的模块：
```
LOCAL_LDLIBS := -lz
LOCAL_LDLIBS := -llog
```

#### LOCAL_ARM_NEON

此变量仅在您针对 armeabi-v7a ABI 时才重要。它允许在 C 和 C++ 源文件中使用 ARM Advanced SIMD (NEON) GCC 内联函数，以及在 Assembly 文件中使用 NEON 指令。

请注意，并非所有基于 ARMv7 的 CPU 都支持 NEON 指令集扩展。因此，必须执行运行时检测以便在运行时安全地使用此代码。 如需了解详细信息，请参阅 [NEON 支持](https://developer.android.google.cn/ndk/guides/cpu-arm-neon.html)和 [cpufeatures 库](https://developer.android.google.cn/ndk/guides/cpu-features.html)。

#### LOCAL_THIN_ARCHIVE 

构建静态库时将此变量设置为 true。这样会生成一个瘦存档 ，即一个库文件，其中不含对象文件，而只包含它通常要包含的实际对象的文件路径。

这对于减小构建输出的大小非常有用。缺点是：这样的库无法移至不同的位置（其中的所有路径都是相对的）。

有效值为 true、false 或空白。可通过 APP_THIN_ARCHIVE 变量在 Application.mk 文件中设置默认值。

>注：对于非静态库模块或预构建的静态库模块会忽略此变量。


### NDK 提供的函数宏

#### my-dir

此宏返回最后包含的 makefile 的路径，通常是当前 Android.mk 的目录
```
LOCAL_PATH := $(call my-dir)
```

#### all-subdir-makefiles

返回位于当前 my-dir 路径所有子目录中的 Android.mk 文件列表。

可以使用此函数为构建系统提供深入嵌套的源目录层次结构。 默认情况下，NDK 只在包含 Android.mk 文件的目录中查找文件。

#### this-makefile

返回当前 makefile（构建系统从中调用函数）的路径。

#### parent-makefile

返回包含树中父 makefile 的路径（包含当前 makefile 的 makefile 路径）。

#### grand-parent-makefile

返回包含树中祖父 makefile 的路径（包含当前父 makefile 的 makefile 路径）。

#### import-module

用于按模块的名称查找和包含模块的 Android.mk 文件的函数。 典型的示例如下所示：
```
$(call import-module,<name>)
```
在此示例中，构建系统查找 NDK_MODULE_PATH 环境变量引用的目录列表中以 <name> 标记的模块，并且自动为您包含其Android.mk 文件。


## Application.mk

Application.mk 构建文件，此文件用于描述应用需要的原生模块。 模块可以是静态库、共享库或可执行文件。

>Application.mk 文件实际上是定义要编译的多个变量的微小 GNU Makefile 片段。 它通常位于 $PROJECT/jni/ 下，其中 $PROJECT 指向应用的项目目录。 

### 变量

#### APP_PROJECT_PATH

此变量用于存储应用项目根目录的绝对路径。构建系统使用此信息将生成的 JNI 共享库的简缩版放入 APK 生成工具已知的特定位置。

如果将 Application.mk 文件放在 $NDK/apps/<myapp>/ 下，则必须定义此变量。 如果将其放在 $PROJECT/jni/ 下，则此变量可选。

#### APP_BUILD_SCRIPT

默认情况下，NDK 构建系统在 jni/ 下查找名称为 Android.mk 的文件。

如果要改写此行为，可以定义 APP_BUILD_SCRIPT 指向替代构建脚本。 构建系统始终将非绝对路径解释为 NDK 顶级目录的相对路径。

#### APP_ABI

默认情况下，NDK 构建系统为 armeabi ABI 生成机器代码。 此机器代码对应于基于 ARMv5TE、采用软件浮点运算的 CPU。 您可以使用 APP_ABI 选择不同的 ABI。
```
APP_ABI := armeabi armeabi-v7a x86 mips
```

#### APP_PLATFORM

此变量包含目标 Android 平台的名称。例如，android-3 指定 Android 1.5 系统映像。 如需平台名称和对应 Android 系统映像的完整列表，请参阅 [Android NDK 原生 API](https://developer.android.google.cn/ndk/guides/stable_apis.html)。

#### APP_STL

默认情况下，NDK 构建系统为 Android 系统提供的最小 C++ 运行时库 (system/lib/libstdc++.so) 提供 C++ 标头。 此外，它随附您可以在自己的应用中使用或链接的替代 C++ 实现。请使用 APP_STL 选择其中一个。 如需了解有关支持的运行时及其功能的信息，请参阅 [NDK 运行时和功能](https://developer.android.google.cn/ndk/guides/cpp-support.html#runtimes)。
```
## 支持C++异常处理, 标准模板库
## 静态库比较大,省事,移植性好 
## APP_STL := gnustl_shared
APP_STL := gnustl_static
```

#### NDK_TOOLCHAIN_VERSION

将此变量定义为 4.9 或 4.8 以选择 GCC 编译器的版本。 64 位 ABI 默认使用版本 4.9 ，32 位 ABI 默认使用版本 4.8。要选择 Clang 的版本，请将此变量定义为 clang3.4、clang3.5 或 clang。 指定 clang 会选择 Clang 的最新版本。

#### APP_PIE

从 Android 4.1（API 级别 16）开始，Android 的动态链接器支持位置独立的可执行文件 (PIE)。 从 Android 5.0（API 级别 21）开始，可执行文件需要 PIE。要使用 PIE 构建可执行文件，请设置 -fPIE 标志。 此标志增大了通过随机化代码位置来利用内存损坏缺陷的难度。 默认情况下，如果项目针对 android-16 或更高版本，ndk-build 会自动将此值设置为 true。您可以手动将其设置为 true 或 false。

此标志仅适用于可执行文件。它在构建共享或静态库时没有影响。

>注：PIE 可执行文件无法在 4.1 版之前的 Android 上运行。

此限制仅适用于可执行文件。它在构建共享或静态库时没有影响。

#### APP_THIN_ARCHIVE

在 Android.mk 文件中为此项目中的所有静态库模块设置 LOCAL_THIN_ARCHIVE 的默认值。


## 重要注意事项

### C++ 异常

在高于 NDKr5 的所有 NDK 版本中，NDK 工具链可让您使用支持异常处理的 C++ 运行时。 但为确保与早期版本兼容，默认情况下它会编译所有支持 -fno-exceptions 的 C++ 来源。 您可以为整个应用或个别模块启用 C++ 异常。

要为整个应用启用异常处理支持，请将以下行添加到 Application.mk 文件中。要为个别模块启用异常处理支持，请将以下行添加到其各自的 Android.mk 文件中。
```
APP_CPPFLAGS += -fexceptions
```

### RTTI
在高于 NDKr5 的所有 NDK 版本中，NDK 工具链可让您使用支持 RTTI 的 C++ 运行时。 但为确保与早期版本兼容，默认情况下它会编译所有支持 -fno-rtti 的 C++ 来源。

要为整个应用启用 RTTI 支持，请将以下行添加到 Application.mk文件中：
```
APP_CPPFLAGS += -frtti
```
要为个别模块启用 RTTI 支持，请将以下行添加到其各自的 Android.mk 文件中：
```
LOCAL_CPP_FEATURES += rtti
或者，您也可以使用：
LOCAL_CPPFLAGS += -frtti
```

### 静态运行时

将 C++ 运行时的静态库变体添加到多个二进制文件可能导致意外行为。 例如，您可能会遇到：

* 内存在一个库中分配，在另一个库中释放，从而导致内存泄漏或堆损坏。
* libfoo.so 中引发的异常在 libbar.so 中未被捕获，从而导致您的应用崩溃。
* std::cout 的缓冲未正常运行

此外，如果您将两个共享库 – 或者一个共享库和一个可执行文件 – 链接到同一个静态运行时，每个共享库的最终二进制映像包含运行时代码的副本。 运行时代码有多个实例是表明有问题，因为运行时内部使用或提供的某些全局变量会重复。

此问题不适用于只包含一个共享库的项目。例如，您可以链接 stlport_static，并预期您的应用正确运行。 如果您的项目需要多个共享库模块，建议使用 C++ 运行时的共享库变体。

### 共享运行时

如果您的应用针对早于 Android 4.3（Android API 级别 18）的 Android 版本，并且您使用指定 C++ 运行时的共享库变体，则必须先加载共享库，再加载依赖它的任何其他库。

例如，应用可能具有以下模块：

* libfoo.so
* libfoo.so 使用的 libbar.so
* libfoo 和 libbar 使用的 libstlport_shared.so

必须以相反的依赖顺序加载库：
```
    static {
      System.loadLibrary("stlport_shared");
      System.loadLibrary("bar");
      System.loadLibrary("foo");
    }
```
>注：调用 System.loadLibrary() 时不要使用 lib 前缀。
