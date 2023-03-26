# Keystrokes

跨平台的键盘检测工具。

目前支持的平台有：
- Windows
- Linux

## 功能

在后台检测键盘按键，将检测到的键对应的虚拟键码存储到 `lastInput.txt` 文件。

## 构建

### 环境要求

### CMake

项目已写好 `CMakeLists.txt`　，使用 `CMake` 构建即可。

Linux：
```sh
mkdir build
cd build
cmake ..
make
```

Windows:
```bat
md build
cd build
cmake ..
make
```