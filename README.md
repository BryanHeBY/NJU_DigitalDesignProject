# RISCV32计算系统与AM应用程序

本项目为南京大学数字逻辑与计算机组成实验课程的期末课程作业，成功在DE10Standard开发板上实现和运行自己的RV32计算系统。

## 本项目有如下特色

- 实现4段流水线，时钟频率可达50MHz
- 实现支持ASNI颜色控制码的字符显存，实现图形显存
- 实现数码管，LED灯，开关等外设的读写支持
- 实现本地仿真模拟框架，实现测试集本地波形测试
- 移植AM运行时环境，拥有强大的库函数支持，并与架构解耦，实现本机调试，上板运行的需求
- 移植AM中CPU测试集部分，运行丰富应用时有CPU正确的保障
- 编写和移植IO测试集部分，保证IO设备正常运行
- 内建终端拥有退格，滚屏，提供shift/capslock按键支持，上下翻页，左右移动光标（移动后正常输入与退格）等功能
- 移植AM的打字小游戏与OSlab0小游戏，运行“来自未来的游戏”

## 工程目录结构

```SCSS
.
├── am_home                       本工程AM_HOME($MYCPU_AM_HOME)
│   ├── am                        riscv32-fpga架构AM目录
│   │   ├── include
│   │   │   ├── am-fpga.h       riscv32-fpga架构AM接口与部分实现
│   │   │   └── am.h            AM通用接口
│   │   └── src
│   │       ├── am-ioe           AM相关接口实现（TRM, IOE）
│   │       ├── fpga-ioe         riscv32-fpga架构AM接口实现
│   │       │   ├── builtin_shell    内置shell相关接口实现
│   │       │   ├── hex              七段数码管接口实现
│   │       │   └── kdb              ps2键盘接口实现
│   │       └── riscv-muldiv     rv32i内乘除法链接源码
│   ├── klib                      与架构无关的c库实现
│   │   ├── include
│   │   └── src
│   │       ├── stdio
│   │       ├── stdlib
│   │       └── string
│   ├── scripts
│   │   ├── dump.mk         fpga指令、数据存储器mif文件生成与自动更新规则
│   │   └── linker.ld       链接脚本
│   └── makefile             AM项目基础makefile
├── am_kernel                 AM上层软件
│   ├── asni_test            ASNI字符输出测试
│   ├── benchmarks           跑分程序
│   │   ├── coremark
│   │   └── dhrystone
│   ├── dummy
│   ├── fpga_test            AM内置CPU测试集
│   ├── myterm               基础要求：myTerminal实现
│   │   └── src             MyTerminal中可执行文件源码目录
│   ├── oslab0               oslab0小游戏
│   ├── typing-game          打字小游戏
│   └── vga_test             图形显存测试
├── hardware_src                    硬件相关源码
│   ├── cpu                        CPU源码
│   └── quartus_core               计算机系统硬件源码（TRM+IOE）
├── makefile                        CPU硬件更新/测试规则
└── cpu_test                        CPU测试集
    ├── cpu_batch                   官方测试集（流水线版本）
    ├── cpu_singlestep              单步测试集 (流水线版本)
    └── mytest                      个人程序测试集
```

