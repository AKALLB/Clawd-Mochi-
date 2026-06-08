# Arduino IDE 烧录步骤

## 1. 安装 Arduino IDE
安装 Arduino IDE 2.x。

## 2. 添加 ESP32 开发板地址
打开 Arduino IDE：
`File / 文件` → `Preferences / 首选项` → `Additional boards manager URLs / 附加开发板管理器网址`

填入：
```text
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
```

## 3. 安装 ESP32 开发板支持
`Tools / 工具` → `Board / 开发板` → `Boards Manager / 开发板管理器`

搜索：
```text
esp32
```

安装：
```text
esp32 by Espressif Systems
```

## 4. 安装库
`Tools / 工具` → `Manage Libraries / 管理库`

安装这两个库：
```text
Adafruit GFX Library
Adafruit ST7735 and ST7789 Library
```

## 5. 板型设置
在 `Tools / 工具` 中设置：

| 设置项 | 值 |
|---|---|
| Board | ESP32C3 Dev Module |
| USB CDC On Boot | Enabled |
| CPU Frequency | 160 MHz |
| Upload Speed | 921600 |
| Port | 选择你的 ESP32-C3 串口 |

`USB CDC On Boot = Enabled` 很重要，不开可能串口识别和烧录不正常。

## 6. 烧录方式
1. 下载原项目仓库或使用本包里的测试代码。
2. 打开 `.ino` 文件。
3. 插入 ESP32-C3。
4. 选择正确端口。
5. 点击 Upload 上传。
6. 看到 `Hard resetting via RTS pin...` 通常表示上传成功。

## 7. 烧录后验证
- 屏幕应显示图形或颜色。
- 原项目固件会创建 WiFi 热点：`ClaWD-Mochi`，密码：`clawd1234`。
- 手机连接后打开：`http://192.168.4.1`。
