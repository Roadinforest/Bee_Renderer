
# 🐝 Bee_Renderer: A Modern OpenGL Renderer

[English](#-english-version) | [简体中文](#-简体中文版)

Welcome to **Bee_Renderer**, a lightweight and modern 2D/3D rendering engine built from the ground up with C++ and OpenGL. This project serves as the core rendering hive for the **Beehive Game Engine**, designed for learning, experimentation, and building high-performance graphics applications.

This renderer is heavily inspired by the exceptional [OpenGL series by The Cherno](https://www.youtube.com/playlist?list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2), focusing on modern techniques, clean abstraction, and a deep understanding of the graphics pipeline.

---

## 🇬🇧 English Version

### ✨ Core Philosophy

The design of Bee_Renderer revolves around several key principles, much like the efficient structure of a beehive:

*   **Modularity**: Each component (VertexBuffer, Shader, Texture) is a self-contained "cell," responsible for a single, well-defined task.
*   **Abstraction**: We hide the complex, low-level OpenGL calls behind a clean, intuitive C++ interface, allowing you to focus on *what* to render, not *how*.
*   **Performance**: Techniques like batch rendering are implemented to ensure our "worker bees" (the GPU) are always busy processing large batches of data, minimizing CPU overhead.
*   **Clarity**: The code is written to be a learning resource, emphasizing readability and modern C++ practices (RAII, smart pointers, etc.).

### 🚀 Features

Bee_Renderer is buzzing with modern features:

*   **OpenGL Core Profile (3.3+)**: Utilizes the modern, shader-based pipeline.
*   **Clean C++ Abstractions**: RAII-based classes for `VertexBuffer`, `IndexBuffer`, `VertexArray`, `Shader`, and `Texture`.
*   **Flexible Rendering System**: A `Renderer` class to encapsulate drawing logic.
*   **Advanced Rendering Techniques**: A dynamic **Batch Renderer** for efficiently rendering thousands of 2D quads.
*   **Mathematical Foundations**: Seamless integration with **GLM** for all vector and matrix operations (MVP).
*   **Immediate Mode GUI**: Powered by **Dear ImGui** for powerful debugging and development tools.
*   **Test-Driven Framework**: A modular test system to easily switch between different rendering experiments.

### 🛠️ Getting Started

#### Prerequisites

*   A C++17 compatible compiler.
*   [GLFW](https://www.glfw.org/), [GLEW](http://glew.sourceforge.net/), [GLM](https://glm.g-truc.net/0.9.9/index.html), [Dear ImGui](https://github.com/ocornut/imgui), [stb_image](https://github.com/nothings/stb/blob/master/stb_image.h).

*(This project uses Premake5 to generate project files.)*

#### Building and Running

1.  Clone the repository:
    ```bash
    git clone https://github.com/your-username/Bee_Renderer.git
    cd Bee_Renderer
    ```
2.  Generate project files for your favorite IDE (e.g., Visual Studio 2022):
    ```bash
    premake5 vs2022
    ```
3.  Open the generated solution file (`.sln`), build, and run the project.

### 📂 Project Structure

```
Bee_Renderer/
├── res/                  # Resource hive: shaders, textures
├── src/                  # Source code hive
│   ├── vendor/           # Third-party libraries
│   ├── core/             # Core rendering classes
│   ├── tests/            # Individual rendering tests
│   └── Application.cpp   # Main entry point
└── premake5.lua          # Build system configuration
```


### 📜 Roadmap

*   [ ] 3D Rendering pipeline (Lighting, Materials)
*   [ ] Framebuffer abstraction for post-processing
*   [ ] Instanced rendering
*   [ ] Font rendering
*   [ ] Integration into the main **Beehive Game Engine**

### 🙏 Acknowledgements

A huge thank you to **[The Cherno](https://youtube.com/thecherno)** for creating the foundational tutorial series that made this project possible.

[Back to top](#-bee_renderer)

---
<br>

## 🇨🇳 简体中文版

### ✨ 核心理念

Bee_Renderer 的设计围绕着几项关键原则，如同一个高效运转的蜂巢：

*   **模块化 (Modularity)**: 每个组件（如 `VertexBuffer`, `Shader`, `Texture`）都是一个独立的“蜂房”，仅负责单一且明确定义的任务。
*   **抽象化 (Abstraction)**: 我们将复杂的底层 OpenGL 调用隐藏在一个清晰、直观的 C++ 接口之后，让你能专注于渲染*什么*，而不是*如何*渲染。
*   **高性能 (Performance)**: 通过实现批量渲染等技术，确保我们的“工蜂”（GPU）始终忙于处理大批量数据，从而最大限度地减少 CPU 开销。
*   **清晰易懂 (Clarity)**: 代码本身就是一份学习资源，强调可读性和现代 C++ 实践（如 RAII、智能指针等）。

### 🚀 主要特性

Bee_Renderer 充满了令人兴奋的现代特性：

*   **OpenGL 核心模式 (3.3+)**: 完全基于现代可编程着色器管线。
*   **清晰的 C++ 抽象**: 基于 RAII 原则封装了 `VertexBuffer`, `IndexBuffer`, `VertexArray`, `Shader`, 和 `Texture` 类。
*   **灵活的渲染系统**: 使用一个 `Renderer` 类来封装绘制逻辑。
*   **先进的渲染技术**: 实现了一个动态**批量渲染器**，能用一次绘制调用高效渲染成千上万的 2D 四边形。
*   **数学库集成**: 无缝集成 **GLM** 库，用于处理所有向量和矩阵运算（MVP）。
*   **即时模式图形界面**: 借助强大的 **Dear ImGui** 库，轻松创建调试和开发工具。
*   **测试驱动框架**: 一个模块化的测试系统，可以方便地在不同的渲染实验场景之间切换。

### 🛠️ 开始使用

#### 环境要求

*   支持 C++17 的编译器。
*   [GLFW](https://www.glfw.org/), [GLEW](http://glew.sourceforge.net/), [GLM](https://glm.g-truc.net/0.9.9/index.html), [Dear ImGui](https://github.com/ocornut/imgui), [stb_image](https://github.com/nothings/stb/blob/master/stb_image.h)。

*(本项目使用 Premake5 来生成工程文件。)*

#### 构建与运行

1.  克隆仓库：
    ```bash
    git clone https://github.com/your-username/Bee_Renderer.git
    cd Bee_Renderer
    ```
2.  为你偏好的 IDE 生成工程文件（例如：Visual Studio 2022）：
    ```bash
    premake5 vs2022
    ```
3.  打开生成的解决方案文件（`.sln`），构建并运行项目。

### 📂 项目结构

```
Bee_Renderer/
├── res/                  # 资源蜂巢：着色器、纹理
├── src/                  # 源码蜂巢
│   ├── vendor/           # 第三方库
│   ├── core/             # 核心渲染类
│   ├── tests/            # 独立的渲染测试
│   └── Application.cpp   # 主程序入口
└── premake5.lua          # 构建系统配置
```


### 📜 未来规划

蜂巢总是在不断扩张！未来计划实现的功能：

*   [ ] 3D 渲染管线（光照、材质）
*   [ ] 帧缓冲抽象，用于实现后处理效果
*   [ ] 实例化渲染，实现极致的绘制效率
*   [ ] 字体渲染
*   [ ] 集成到主游戏引擎 **Beehive Game Engine**

### 🙏 致谢

在此特别感谢 **[The Cherno](https://youtube.com/thecherno)**，他所创作的殿堂级 OpenGL 系列教程是这个项目得以诞生的基石。

[返回顶部](#-bee_renderer)
