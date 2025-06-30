# RTGP Project — Real-Time Graphics Pattern Renderer

**RTGP (Real-Time Graphics Project)** is an interactive OpenGL-based application that showcases real-time procedural texturing on 3D models using custom GLSL shaders. The project renders a 3D bunny model with dynamically generated textures, controlled via a graphical interface powered by ImGui. It's a visual sandbox for exploring GPU-based procedural patterns, camera movement, and shader manipulation.

---

## Features

- **Procedural Patterns**: Stripes, circles, triangles, and hexagons rendered directly in GLSL fragment shaders.
- **3D Scene Rendering**: Displays a low-poly bunny and ground plane with realistic lighting.
- **Live GUI Controls**: Modify pattern type, scale, rotation, stripe width, shape sizes, and colors in real-time.
- **Pattern-to-Texture Pipeline**: Procedural pattern is rendered into a framebuffer object (FBO) as a texture.
- **Camera Control**: Navigate freely with WASD + mouse look.
- **Lighting Setup**: Dynamic Phong-style lighting with controllable light position.

---

## Dependencies

Ensure the following libraries are available (typically through vcpkg, system packages, or precompiled sources):

- [GLFW](https://www.glfw.org/) — Window and input handling
- [GLAD](https://glad.dav1d.de/) — OpenGL function loader
- [ImGui](https://github.com/ocornut/imgui) — Immediate-mode GUI
- [ASSIMP](https://github.com/assimp/assimp) — Asset/model loading
- [GLM](https://github.com/g-truc/glm) — OpenGL Mathematics

---

## Build Instructions

### Windows (MakefileWin)
```bash
make -f MakefileWin
```


## Controls

- `W`, `A`, `S`, `D` – Move camera
- Mouse Movement – Look around
- `ESC` – Toggle ImGui GUI

### GUI Parameters
- Pattern Type: Stripes, Circles, Triangles, Hexagons
- Scale, Rotation, Stripe Width
- Shape-specific size (Circle Radius, Triangle Size, Hexagon Size)
- RGB Color Editor

---

## Project Structure

```
RTGP/
├── include/              # Header files
├── libs/                 # Third-party libraries (e.g., ImGui, GLFW)
├── project/              # Source files & shaders
│   ├── main.cpp
│   ├── PatternRenderer.*       # FBO rendering and shader controls
│   ├── Shader.*                # Shader compilation/utilities
│   ├── Camera.*                # Fly camera controls
│   ├── Model.*                 # Model loading via Assimp
│   ├── GuiController.*         # ImGui control binding
│   ├── *.vert / *.frag         # GLSL Shaders
├── MakefileWin           # Windows-specific makefile
├── .vscode/              # VSCode project settings
└── README.md             # You are here
```

---

## Author Notes

- Modular C++ structure; renderer decoupled from scene logic
- Easy to extend with new patterns or shapes
- Focused on educational and experimental uses in real-time graphics

---

## License

This project is for educational and non-commercial use only.

