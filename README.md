# Automotive Configuration Management

One-Box 集成制动控制器（线控制动）软件开发演示工程，用于向团队展示如何用 **Git 进行版本管理**。

> ⚠️ 本仓库仅用于培训演示：所有 C 源文件均为待填充的代码模板，不含实际产品逻辑，也不含构建脚本。

## 目录

- [项目简介](#项目简介)
- [工程结构](#工程结构)
- [代码模板约定](#代码模板约定)
- [Git 版本管理演示流程](#git-版本管理演示流程)
- [分支与提交规范](#分支与提交规范)
- [快速开始](#快速开始)

## 项目简介

本工程模拟一个基于 AUTOSAR 架构的 One-Box 集成制动控制器软件，涵盖：

- **ASW（应用软件层）**：驻车制动等应用逻辑
- **BSW（基础软件层）**：MCU、传感器、收发器、电机控制等驱动
- **CDD（复杂设备驱动）**：ASIC、EPB 电机控制、WSS/RPS 传感器、收发器
- **RTE（运行时环境）**：ASW 与 BSW 之间的通信与调度

每个模块提供一对同名 `.c` / `.h` 模板文件，便于在 Git 演示中逐模块修改、提交与合并。

## 工程结构

```text
automotive-configuration-management/
└── onebox/
    ├── asw/                        # ASW 应用软件层
    │   ├── asw.c
    │   └── asw.h
    ├── bsw/                        # BSW 基础软件层
    │   ├── bsw.c / bsw.h
    │   ├── autosar.cdds/           # 复杂设备驱动（CDD）
    │   │   ├── autosar_cdds.c / autosar_cdds.h
    │   │   ├── asic/               # ASIC 芯片驱动
    │   │   ├── epb.motor.control/  # EPB 电机控制驱动
    │   │   ├── mcu/                # MCU 微控制器驱动
    │   │   ├── sensor.rps/         # RPS 转子位置传感器驱动
    │   │   ├── sensor.wss/         # WSS 轮速传感器驱动
    │   │   └── transceiver/        # 通信收发器驱动
    │   ├── autosar.dynamic/        # AUTOSAR 动态代码
    │   └── autosar.static/         # AUTOSAR 静态代码
    ├── build/                      # 构建配置
    ├── public/                     # 公共基础模块
    └── rte/                        # RTE 运行时环境
```

> 目录名中的点号（`.`）在文件名中转换为下划线（`_`），如 `epb.motor.control/` → `epb_motor_control.c`。

## 代码模板约定

每个模块模板包含统一的骨架，便于团队按同一风格填充。

### 函数接口

| 函数 | 说明 |
| --- | --- |
| `Xxx_Init()` | 模块初始化，系统上电时调用一次 |
| `Xxx_MainFunction()` | 模块周期处理函数，由调度器周期调用 |
| `Xxx_GetVersion()` | 返回模块版本号字符串 |

### 版本号

`.h` 文件中定义版本宏，修改功能后同步更新：

```c
#define MCU_VERSION_STRING   "1.0.0"
```

### 文件头注释

每个文件头部包含 `@version`、`@date` 与「修改记录」表，用于教学对比：**文件内手工维护版本记录 vs `git log` 自动记录**。

### 待填充标记

所有待实现逻辑均以 `TODO: 在此填充...` 标注，并附有该模块职责相关的提示（如 EPB 电机控制的 PWM / H 桥配置、RTE 的 ASW/BSW 通信通道等）。

## Git 版本管理演示流程

### 1. 建立初始基线

```bash
git add .
git commit -m "[all] 初始版本：创建各模块代码模板 v1.0.0"
git tag v1.0.0
```

### 2. 功能分支开发（以 EPB 电机控制为例）

```bash
git checkout -b feature/epb-motor-control

# 修改 onebox/bsw/autosar.cdds/epb.motor.control/epb_motor_control.c
# 实现电机控制逻辑，并将版本宏更新为 1.1.0

git add onebox/bsw/autosar.cdds/epb.motor.control/
git commit -m "[epb-motor-control] 实现电机正反转控制逻辑"
```

### 3. 合并与发布

```bash
git checkout main
git merge --no-ff feature/epb-motor-control
git tag v1.1.0
```

### 4. 冲突解决演示

两个分支同时修改同一个模块（例如 `mcu.c`）后合并，演示 `git merge` 冲突的产生与解决：

```bash
git checkout -b feature/mcu-lowpower main
# 修改 mcu.c 的低功耗配置...

git checkout -b feature/mcu-clkcheck main
# 修改 mcu.c 的时钟监控逻辑...

git checkout main
git merge feature/mcu-lowpower
git merge feature/mcu-clkcheck   # ← 此处演示冲突解决
```

### 5. 历史追溯

```bash
git log --graph --oneline --all
```

## 分支与提交规范

- 主分支 `main` 始终保持可发布状态，不直接提交功能代码
- 功能分支命名：`feature/<模块名>`，如 `feature/epb-motor-control`
- 提交信息格式：`[模块] 变更说明`，如 `[mcu] 增加低功耗模式配置`
- 发布时在 `main` 上打版本 tag：`v1.0.0`、`v1.1.0`...

## 快速开始

```bash
git clone https://github.com/YorkLiu2018/automotive-configuration-management.git
```

---

本工程为演示用途，暂无构建脚本；后续可在 `onebox/build/` 下补充 Makefile / CMake。
