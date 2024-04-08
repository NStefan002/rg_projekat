# Manual

**Run the following commands from the terminal:**

1. `git clone https://github.com/NStefan002/rg_projekat.git` --> clones this project
2. `cd /path/to/rg_projekat` --> positions into the root directory of the project
3. `./compile.sh;` --> runs the script that compiles the code
4. `./rg_projekat` --> runs program

# Controls
- `a`, `w`, `s`, `d` - move in the desired direction
- `q` / `Esc` - exit
- `F1` - toggle ImGui
- `space` - toggle hdr
- `i`, `o` - increase/decrease exposure (when `hdr` is on)

# Project structure
```
├─ cmake/           CMake utils
├─ include/         h/hpp files
├─ libs/            external libraries
├─ resources/
│  ├─ objects/      3d models
│  ├─ shaders/      vertex and fragment shaders
│  └─ textures/     skyboxes, textures
└─ src/             cpp files
```

# Sources

- [Models](https://www.cadnav.com/3d-models/)
- [Textures](https://www.cadnav.com/textures) and some other [textures](https://www.transparenttextures.com/)
- [Skybox](https://opengameart.org/content/park-skyboxes)
- [Parts of the code](https://github.com/JoeyDeVries/LearnOpenGL)

> [!NOTE]
> Group A --> Cubemaps, Group B --> HDR, Bloom

# Showcase
[YouTube](https://youtu.be/ip6DghDATA8)
