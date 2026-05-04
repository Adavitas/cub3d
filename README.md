<div align="center">

# 🧊 cub3D

### *A 42 School raycasting project that renders a textured first-person maze with doors, minimap, mouse look, multiple wall types, and a dynamic wand-light mechanic.*

[![42 School](https://img.shields.io/badge/School-000000?style=for-the-badge&logo=42&logoColor=white)](https://42.fr)
[![Language](https://img.shields.io/badge/Language-C-blue?style=for-the-badge)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Norminette](https://img.shields.io/badge/Norminette-passing-success?style=for-the-badge)](https://github.com/42School/norminette)
![Graphics](https://img.shields.io/badge/Graphics-MiniLibX-orange?style=for-the-badge)

</div>

---

## 📋 Table of Contents

- [About](#-about)
- [Features](#-features)
- [Algorithm](#-algorithm)
- [Installation](#-installation)
- [Usage](#-usage)
- [Controls & Map Symbols](#-controls--map-symbols)
- [Project Structure](#-project-structure)
- [Performance](#-performance)
- [Error Handling](#️-error-handling)
- [Make Commands](#️-make-commands)
- [Testing Examples](#-testing-examples)
- [Author](#-author)
- [License](#-license)

---

## 🎯 About

**cub3D** is a 42 School project inspired by classic raycasting engines such as *Wolfenstein 3D*. The goal is to render a first-person 3D view from a 2D `.cub` map using the MiniLibX graphics library.

The project parses a custom map file, validates textures and colors, initializes the player, casts one ray per screen column, and renders textured walls, floor, sky, doors, minimap, and a first-person wand HUD with a lighter-style illumination effect.

The current version also expands the basic cub3D experience with map-driven wall texture types: wall characters `1`, `2`, `3`, and `4` can select different wall textures instead of relying only on north/south/east/west wall direction.

---

## ✨ Features

- **Raycasting renderer** using DDA traversal for real-time first-person projection
- **Textured walls, floor, sky, and doors** loaded from XPM files
- **Multiple wall tile types**: `1`, `2`, `3`, and `4` map to different wall texture slots
- **Door interaction** with open/closed collision and raycast behavior
- **First-person wand HUD** with off, turning-on, on, and turning-off states
- **Dynamic wand lighting** with darker ambience when the wand is off and warmer light when it is on
- **Procedural wand-tip sparkles** for a small magical shine effect without heavy rendering cost
- **Minimap overlay** showing walls, doors, player position, and direction
- **Mouse look toggle** and keyboard rotation support
- **Strict `.cub` parser** with map validation, RGB validation, texture validation, and flood-fill enclosure checks
- **Memory cleanup** for map data, textures, MiniLibX images, window, display, and wand resources

---

## 🧮 Algorithm

The rendering strategy is based on a classic grid raycaster:

### Raycasting Pipeline
- Cast one ray for each vertical screen column
- Convert the screen column into a camera-space ray direction
- Use DDA traversal to step through the map grid
- Stop when the ray hits a wall tile or a closed door
- Compute perpendicular wall distance to avoid fish-eye distortion
- Project the wall slice height onto the screen

### Texture Selection
- Door tiles use the dedicated door texture
- Wall tiles are selected directly from the map character:
  - `1` → `TEX_NO`
  - `2` → `TEX_SO`
  - `3` → `TEX_WE`
  - `4` → `TEX_EA`
- This allows room design to choose wall textures explicitly from the map

### Floor, Sky, and Lighting
- The sky texture is sampled by ray angle
- The floor is rendered using floor casting and bilinear texture sampling
- Fog and wand lighting are applied to world pixels
- Wand light values are cached once per frame to avoid repeating expensive calculations per pixel

### Wand HUD
- The wand is drawn as a clipped HUD overlay after the 3D world and minimap
- `WAND_OFF`, `WAND_TURNING_ON`, `WAND_ON`, and `WAND_TURNING_OFF` control animation state
- Procedural sparkles are drawn around the wand tip when the light level is high enough

---

## 🔧 Installation

```bash
# Clone the repository
git clone https://github.com/Adavitas/cub3d.git
cd cub3d

# Compile the project
make

# This creates the cub3D executable
```

### Compilation Flags
The project is compiled with: `-Wall -Wextra -Werror`

### Dependencies
This project uses MiniLibX and requires the usual Linux graphical dependencies:

```bash
sudo apt-get install gcc make xorg libxext-dev libbsd-dev
```

---

## 🚀 Usage

```bash
# Run with a valid map
./cub3D maps/file.cub

# Run a room map
./cub3D maps/room.cub

# Run a maze map
./cub3D maps/maze.cub

# Run a door test map
./cub3D maps/valid_door.cub
```

The program expects exactly one `.cub` file argument:

```bash
./cub3D <map.cub>
```

Example `.cub` texture/color header:

```text
NO ./textures/walls/wall_1.xpm
SO ./textures/walls/wall_2.xpm
WE ./textures/walls/wall_3.xpm
EA ./textures/walls/wall_4.xpm

F 30,30,40
C 120,160,220
```

Example map body:

```text
111111111
100000001
102030401
1000D0001
111111111
```

---

## 🎮 Controls & Map Symbols

### Controls

| Key / Input | Action |
|-------------|--------|
| `W` | Move forward |
| `S` | Move backward |
| `A` | Strafe left |
| `D` | Strafe right |
| `←` | Rotate left |
| `→` | Rotate right |
| `Mouse Button 1` | Toggle mouse look |
| `R` | Open / close door in front of the player |
| `F` | Toggle wand light on / off |
| `Esc` | Exit the game |

### Map Symbols

| Symbol | Meaning |
|--------|---------|
| `0` | Empty walkable space |
| `1` | Solid wall using `NO` texture slot |
| `2` | Solid wall using `SO` texture slot |
| `3` | Solid wall using `WE` texture slot |
| `4` | Solid wall using `EA` texture slot |
| `D` | Door tile |
| `N` | Player start, facing north |
| `S` | Player start, facing south |
| `E` | Player start, facing east |
| `W` | Player start, facing west |
| Space / Tab | Void outside the playable map |

---

## 📂 Project Structure

```text
cub3d/
├── 📄 Makefile                         # Build configuration
├── 📂 includes/                        # Header files
│   ├── game.h                          # Main game structs, constants, wand/light config
│   ├── parse.h                         # Parser structs, texture IDs, validation prototypes
│   ├── player.h                        # Player movement, input, and controls
│   └── raycast.h                       # Raycasting/rendering prototypes
├── 📂 maps/                            # Valid and invalid .cub test maps
│   ├── file.cub
│   ├── room.cub
│   ├── maze.cub
│   ├── big.cub
│   ├── valid_door.cub
│   └── invalid_*.cub
├── 📂 textures/                        # XPM textures and HUD assets
│   └── wand/                           # Wand HUD animation frames
├── 📂 libraries/
│   ├── libft/                          # Custom libft library
│   ├── get_next_line/                  # Line-reading utility
│   └── minilibx-linux/                 # MiniLibX graphics library
├── 📂 src/
│   ├── 📂 parsing/                     # .cub parsing and validation
│   │   ├── parse.c
│   │   ├── parse_color.c
│   │   ├── parse_map.c
│   │   ├── parse_map_utils.c
│   │   ├── parse_texture.c
│   │   ├── parse_dispatch.c
│   │   ├── post_validation.c
│   │   └── post_validation_utils.c
│   ├── 📂 player_movement/             # Movement, rotation, doors, wand state
│   │   ├── move.c
│   │   ├── collision.c
│   │   ├── update_player.c
│   │   ├── player_rotate.c
│   │   ├── mouse_rotate.c
│   │   ├── door.c
│   │   ├── wand_state.c
│   │   └── wand_light.c
│   ├── 📂 graphics/                    # MLX setup, raycasting, rendering, minimap, wand HUD
│   │   ├── init_mlx.c
│   │   ├── raycasting.c
│   │   ├── raycasting_utils.c
│   │   ├── render.c
│   │   ├── render_utils.c
│   │   ├── render_light.c
│   │   ├── render_light_utils.c
│   │   ├── wand.c
│   │   ├── wand_draw_utils.c
│   │   ├── wand_sparkles.c
│   │   ├── wand_sparkles_utils.c
│   │   ├── wand_resources.c
│   │   ├── wand_cleanup.c
│   │   ├── minimap.c
│   │   ├── minimap_utils.c
│   │   ├── game_loop.c
│   │   ├── close_game.c
│   │   └── mlx_cleanup.c
│   ├── 📂 clean_up/                    # Memory cleanup
│   │   └── free_game.c
│   ├── 📂 utils/                       # General utility functions
│   │   ├── init.c
│   │   └── utils.c
│   └── main.c                          # Program entry point
└── 📂 docs/
    └── cub3d_wand_feature.md           # Wand feature documentation
```

---

## 📊 Performance

The renderer is built around a simple and predictable software pipeline:

| System | Optimization |
|--------|--------------|
| Raycasting | One DDA ray per screen column |
| Wall rendering | Draws only the projected vertical slice for each ray |
| Floor rendering | Uses floor casting and texture sampling per visible floor pixel |
| Lighting | Wand light values are prepared once per frame and reused during shading |
| HUD wand | Uses `WAND_SCALE == 1` and a clipped unscaled draw path |
| Sparkles | Tiny procedural HUD overlay near the wand tip, not a full-screen effect |

The current window size is `1280x720`. The wand art is drawn as a HUD overlay, so it does not affect collision or ray traversal.

---

## ⚠️ Error Handling

The program validates multiple failure cases before starting the game:

- Wrong argument count
- Invalid file extension; input must be `.cub`
- Missing texture or color definitions
- Duplicate or unknown texture identifiers
- Invalid texture paths or non-XPM textures
- Invalid RGB values or malformed color lines
- Invalid map characters
- Missing player start position
- Multiple player start positions
- Map not enclosed by walls
- Door tiles without valid opposite wall support
- MLX image/window allocation failure

Parser and cleanup paths are designed to release allocated memory before exiting on failure.

---

## 🛠️ Make Commands

```bash
make          # Compile cub3D
make clean    # Remove object files
make fclean   # Remove object files and executable
make re       # Recompile everything
```

The Makefile also builds `libft` and `minilibx-linux` before linking the final executable.

---

## 🧪 Testing Examples

```bash
# Compile
make

# Run common valid maps
./cub3D maps/file.cub
./cub3D maps/room.cub
./cub3D maps/maze.cub
./cub3D maps/big.cub

# Test door behavior
./cub3D maps/valid_door.cub
./cub3D maps/test_door.cub

# Invalid parser cases should fail cleanly
./cub3D maps/invalid_no_player.cub
./cub3D maps/invalid_multiple_players.cub
./cub3D maps/invalid_not_enclosed.cub
./cub3D maps/invalid_rgb_out_of_range.cub
./cub3D maps/invalid_duplicate_texture.cub
./cub3D maps/invalid_empty_line.cub
```

Manual checks:

```bash
# Verify style
norminette includes src

# Rebuild from scratch
make fclean && make
```

---

## 👨‍💻 Author

**Aleksandre Davitashvili** (Adavitas) - *42 Student*

[![GitHub](https://img.shields.io/badge/GitHub-Adavitas-181717?style=flat&logo=github)](https://github.com/Adavitas)

---

## 📝 License

This project is part of the 42 School curriculum.

---

*This project was created as part of the 42 School common core curriculum.*
