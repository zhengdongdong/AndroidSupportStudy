# 支持的ABI

| ABI/配置指令 | 支持的指令集   | 说明                                          |
| ----------- | -------------- | --------------------------------------------- |
| armeabi	  | ARMV5TE 和更高版本 / Thumb-1 | 无硬浮点。|
| armeabi-v7a | armeabi / Thumb-2 / VFPv3-D16 / 其他（可选）| 与 ARMv5、v6 设备不兼容。|
| arm64-v8a   | AArch-64 |  |
| x86         | x86 (IA-32) / MMX / SSE/2/3 / SSSE3 | 不支持 MOVBE 或 SSE4。|
| x86_64      | x86-64 / MMX / SSE/2/3 / SSSE3 / SSE4.1、4.2 / POPCNT |  |
| mips        | MIPS32r1 及更高版本 | 使用硬浮点，并且假设 CPU:FPU 时钟比率为 2:1 以获取最大兼容性。 不提供 micromips 或 MIPS16。 |
| mips64      | MIPS64r6 |  |
| all         | 上面的所有 |  |


# 为特定 ABI 生成代码

默认情况下，NDK 为 armeabi ABI 生成机器代码。但您可以通过向 Application.mk 文件添加以下行生成 ARMv7-a 兼容的机器代码。

```
APP_ABI := armeabi-v7a
```

要为两个或更多不同的 ABI 构建机器代码，请使用空格作为分隔符。例如：

```
APP_ABI := armeabi armeabi-v7a
```

此设置指示 NDK 为机器代码构建两个版本：此行中所列的每个 ABI 一个。 如需了解有关可以为 APP_ABI 变量指定的值的详细信息，请参阅 [Android.mk](https://developer.android.google.cn/ndk/guides/android_mk.html)。

构建多个机器代码版本时，构建系统会将库复制到应用项目路径，并最终将它们封装到 APK 中，从而创建一个胖二进制文件。 胖二进制文件大于只包含一个系统的机器代码的二进制文件；权衡方式是兼容性更广，但 APK 更大。

在安装时，软件包管理器只解包最适合目标设备的机器代码。 如需了解详细信息，请参阅[安装时自动解压缩原生代码](https://developer.android.google.cn/ndk/guides/abis.html#aen)。


## armeabi

AAPCS 标准将 EABI 定义为类似但不同 ABI 的系列。 此外，Android 还采用小字节序 ARM GNU/Linux ABI。

此 ABI 不支持硬件辅助的浮点计算。 相反，所有浮点运算都使用编译器 libgcc.a 静态库中的软件帮助程序函数。

armeabi ABI 支持 ARM 的 Thumb（亦称 Thumb-1）指令集。NDK 默认生成 Thumb 代码，除非您在 Android.mk 文件中使用 LOCAL_ARM_MODE 变量指定不同的行为。

## armeabi-v7a
此 ABI 可扩展 armeabi 以包含多个 CPU 指令集扩展。 此 Android 特定 ABI 支持的指令扩展包括：

* Thumb-2 指令集扩展，其性能堪比 32 位 ARM 指令，简洁性类似于 Thumb-1。
* VFP 硬件 FPU 指令。更具体一点，包括 VFPv3-D16，它除了 ARM 核心中的 16 个 32 位寄存器之外，还包含 16 个专用 64 位浮点寄存器。

v7-a ARM 规格描述的其他扩展，包括 高级 SIMD（亦称 NEON）、VFPv3-D32 和 ThumbEE，都是此 ABI 可选的。 由于不能保证它们存在，因此系统在运行时应检查扩展是否可用。 如果不可用，则必须使用替代代码路径。此检查类似于系统在检查或使用 MMX、SSE2 及 x86 CPU 上其他专用指令集时所执行的检查。

如需了解有关如何执行这些运行时检查的信息，请参阅 [cpufeatures](https://developer.android.google.cn/ndk/guides/cpu-features.html) 库。另外，有关 NDK 支持为 NEON 构建机器代码的信息，请参阅 [NEON](https://developer.android.google.cn/ndk/guides/cpu-arm-neon.html) 支持。

armeabi-v7a ABI 使用 -mfloat-abi=softfp 开关强制实施规则，要求编译器在函数调用时必须传递核心寄存器对中的所有双精度值，而不是专用浮点值。 系统可以使用 FP 寄存器执行所有内部计算。 这样可极大地加速计算。

## arm64-v8a

此 ABI 适用于基于 ARMv8、支持 AArch64 的 CPU。它还包含 NEON 和 VFPv4 指令集。

如需了解详细信息，请参阅 [ARMv8](http://www.arm.com/files/downloads/ARMv8_Architecture.pdf) 技术预览，并联系 ARM 了解进一步的详细信息。

## x86

此 ABI 适用于支持通常称为“x86”或“IA-32”的指令集的 CPU。 此 ABI 的特性包括：

* 指令一般由具有编译器标志的 GCC 生成，如下所示：

```
-march=i686 -mtune=intel -mssse3 -mfpmath=sse -m32
```

这些标志指向 Pentium Pro 指令集，伴随 MMX、SSE、SSE2、SSE3 及 SSSE3 指令集扩展。生成的代码在顶层 Intel 32 位 CPU 之间进行了均衡优化。

如需了解有关编译器标志的详细信息，特别是与性能优化相关的信息，请参阅 [GCC x86 性能提示](http://software.intel.com/blogs/2012/09/26/gcc-x86-performance-hints)。

* 使用标准 Linux x86 32 位调用约定，与 SVR 使用的约定相反。如需了解详细信息，请参阅[不同 C++ 编译器和操作系统的调用约定](http://www.agner.org/optimize/calling_conventions.pdf)的第 6 节“寄存器的使用”。

ABI 不含任何其他可选的 IA-32 指令集扩展，例如：

* MOVBE
* SSE4 的任何变体。

您仍可使用这些扩展，只要您使用运行时功能探测来启用它们，并且为不支持它们的设备提供备用方法。

NDK 工具链假设在函数调用之前进行 16 位栈对齐。默认工具和选项强制执行此规则。 如果编写的是汇编代码，必须确保栈对齐，而且其他编译器也遵守此规则。

## x86_64

此 ABI 适用于支持通常称为“x86-64”的指令集的 CPU。 它支持 GCC 通常使用以下编译器标志生成的指令：

```
-march=x86-64 -msse4.2 -mpopcnt -m64 -mtune=intel
```

这些标志指向 x86-64 指令集（根据 GCC 文档），伴随 MMX、SSE、SSE2、SSE3、SSSE3、SSE4.1、SSE4.2 和 POPCNT 指令集扩展。 生成的代码在顶层 Intel 64 位 CPU 之间进行了均衡优化。

如需了解有关编译器标志的详细信息，特别是与性能优化相关的信息，请参阅 [GCC x86 性能](http://software.intel.com/blogs/2012/09/26/gcc-x86-performance-hints)。

此 ABI 不含任何其他可选的 x86-64 指令集扩展，例如：

* MOVBE
* SHA
* AVX
* AVX2

您仍可使用这些扩展，只要您使用运行时功能探测来启用它们，并且为不支持它们的设备提供备用方法。

## mips

此 ABI 适用于基于 MIPS、至少支持 MIPS32r1 指令集的 CPU。它包含以下功能：

* MIPS32 修订版 1 ISA
* 小字节序
* O32
* 硬浮点
* 无 DSP 应用特定的扩展

## mips64

此 ABI 适用于 MIPS64 R6。

