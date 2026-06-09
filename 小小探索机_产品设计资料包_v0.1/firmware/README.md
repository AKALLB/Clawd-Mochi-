# 固件目录说明

v0.1 资料包不提供未经实机验证的固件成品。本目录用于后续存放 Arduino C++
工程和测试记录。

`board_bringup_test/` 是唯一例外：它是主板到货验收程序，只测试 USB 串口和
GPIO16 上的板载 WS2812，不代表整机固件。

## 计划结构

```text
firmware/
  little-explorer/
    little-explorer.ino
    config.h
    input_touch.*
    input_motion.*
    ui_display.*
    output_light.*
    output_sound.*
    app_state.*
    diagnostics.*
  tests/
  board_bringup_test/
    board_bringup_test.ino
  README.md
```

## 开发前置条件

1. 确认 RP2040-Zero 可烧录基础闪灯程序。
2. 分别验证 ST7789、MPU6050、TTP223、蜂鸣器和 WS2812。
3. 将最终屏幕引脚、偏移和背光方式写入 `config.h`。
4. 固定 Arduino Core 和第三方库版本，并在本文件记录。
5. 再集成状态机，不直接从完整交互程序开始排错。

## 发布固件的验收门槛

- 编译无错误、无未解释警告。
- 在实际采购的模块上通过所有分模块测试。
- 连续完成 20 轮心情选择。
- 传感器断开时不会阻塞或反复重启。
- 静音、休眠、触摸唤醒和拿起唤醒均通过。
- README 写明开发板包、库版本、烧录步骤和已知问题。

固件发布时应另行选择代码许可；当前仓库的“保留全部权利”默认覆盖本目录。
