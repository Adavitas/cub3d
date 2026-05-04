<div align="center">

# 🧊 cub3D

### *A 42 School raycasting engine that renders a textured first-person maze with doors, minimap, mouse look, map-driven wall textures, and a dynamic wand-light mechanic.*

[![42 School](https://img.shields.io/badge/School-000000?style=for-the-badge&logo=42&logoColor=white)](https://42.fr)
[![Language](https://img.shields.io/badge/Language-C-blue?style=for-the-badge)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Graphics](https://img.shields.io/badge/Graphics-MiniLibX-orange?style=for-the-badge)](https://harm-smits.github.io/42docs/libs/minilibx)
[![Renderer](https://img.shields.io/badge/Renderer-Raycasting-purple?style=for-the-badge)](https://en.wikipedia.org/wiki/Ray_casting)
[![Style](https://img.shields.io/badge/Style-Norminette-success?style=for-the-badge)](https://github.com/42School/norminette)
![Grade](https://img.shields.io/badge/Grade-115%2F100-success?style=for-the-badge)

</div>

---

## 📋 Table of Contents

- [About](#-about)
- [Features](#-features)
- [Rendering Pipeline](#️-rendering-pipeline)
- [Map Format](#️-map-format)
- [Controls](#-controls)
- [Installation](#-installation)
- [Usage](#-usage)
- [Project Structure](#-project-structure)
- [Rendering Performance](#-rendering-performance)
- [Error Handling](#️-error-handling)
- [Make Commands](#️-make-commands)
- [Testing Examples](#-testing-examples)
- [Authors](#-authors)
- [License](#-license)

---

## 🎯 About

**cub3D** is a 42 School graphics project inspired by classic raycasting games such as *Wolfenstein 3D*.  
The project renders a first-person 3D view from a 2D `.cub` map using **C** and **MiniLibX**.

The engine parses a custom map file, validates textures and colors, initializes the player, casts one ray per screen column, and draws a complete frame with textured walls, floor, sky, doors, minimap, and a first-person wand HUD.

The current version expands the base cub3D requirements with gameplay and visual features such as interactive doors, map-driven wall texture types, mouse look, darker/lighter room ambience, and a wand with animated lighting and sparkles.

---

## ✨ Features

- **Classic raycasting renderer** using DDA traversal through a 2D grid
- **Textured walls, floor, sky, and doors** loaded from XPM files
- **Map-driven wall textures** using wall symbols `1`, `2`, `3`, and `4`
- **Door interaction** with closed-door collision and raycast blocking
- **First-person wand HUD** with off, turning-on, on, and turning-off states
- **Dynamic wand lighting** that darkens the world when off and warms nearby surfaces when on
- **Procedural wand-tip sparkles** for a lightweight magical shine effect
- **Minimap overlay** showing walls, doors, player position, and player direction
- **Keyboard movement**, keyboard rotation, and mouse-look toggle
- **Strict `.cub` parsing** for textures, colors, map symbols, player start, and wall enclosure
- **Resource cleanup** for parsed map data, texture paths, MiniLibX images, window, display, and wand assets

---

## 🖼️ Rendering Pipeline

The renderer is built around a classic raycasting pipeline.

### Raycasting

- Cast one ray for each vertical screen column
- Convert the screen column into a camera-space ray direction
- Use DDA traversal to step through the 2D map grid
- Stop when the ray hits a wall tile or a closed door
- Compute perpendicular wall distance to avoid fish-eye distortion
- Project the wall slice height onto the screen

### Texture Selection

Wall texture selection is controlled directly by the map character:

| Map Tile | Texture Slot |
|----------|--------------|
| `1` | `NO` |
| `2` | `SO` |
| `3` | `WE` |
| `4` | `EA` |
| `D` | Door texture |

This means wall visuals are no longer limited to north, south, west, and east boundaries.  
A level designer can choose the wall texture by placing `1`, `2`, `3`, or `4` directly in the map.

### Floor, Sky, and Lighting

- The sky texture is sampled by ray angle
- The floor is rendered with floor casting
- Fog and wand lighting are applied to world pixels
- Wand light values are cached once per frame before ray rendering
- HUD elements are drawn after the 3D world so the minimap and wand remain readable

### Wand HUD

- The wand is drawn as a clipped first-person HUD sprite
- `WAND_OFF`, `WAND_TURNING_ON`, `WAND_ON`, and `WAND_TURNING_OFF` control animation state
- The wand light level is separate from the sprite frame, allowing smoother light transitions
- Small procedural sparkles are drawn near the wand tip while the wand is active

---

## 🗺️ Map Format

A `.cub` file contains texture paths, floor/ceiling colors, and a map.

### Texture and Color Header

```text
NO ./textures/wall_ironfold.xpm
SO ./textures/wall_moria.xpm
WE ./textures/wall_mithrin.xpm
EA ./textures/wall_gundabad.xpm

F 135,135,135
C 70,130,180
```

### Map Symbols

| Symbol | Meaning |
|--------|---------|
| `0` | Empty walkable space |
| `1` | Solid wall using the `NO` texture slot |
| `2` | Solid wall using the `SO` texture slot |
| `3` | Solid wall using the `WE` texture slot |
| `4` | Solid wall using the `EA` texture slot |
| `D` | Door tile |
| `N` | Player start, facing north |
| `S` | Player start, facing south |
| `E` | Player start, facing east |
| `W` | Player start, facing west |
| Space / Tab | Void outside the playable map |

### Example Map

```text
111111111
100000001
102030401
1000D0001
100000001
111111111
```

Rules:

- The map must be enclosed by wall tiles
- Exactly one player start position must exist
- Doors must be placed between valid opposite wall tiles
- Invalid characters, missing textures, malformed colors, and open maps are rejected

---

## 🎮 Controls

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

The project is compiled with:

```text
-Wall -Wextra -Werror
```

### Linux Dependencies

MiniLibX requires common X11 development packages:

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
├── 📂 textures/                        # XPM wall, floor, sky, door, and HUD textures
│   └── wand/                           # Wand animation frames
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
│   ├── 📂 player_movement/             # Movement, collision, rotation, doors, wand state
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
```

---

## 📊 Rendering Performance

The engine uses a software-rendered frame buffer and keeps expensive operations predictable.

| System | Approach |
|--------|----------|
| Raycasting | One DDA ray per screen column |
| Walls | Draw only the projected vertical wall slice |
| Floor | Floor casting for visible floor pixels |
| Lighting | Precompute wand light values once per frame |
| Wand HUD | Use `WAND_SCALE == 1` and a clipped unscaled draw path |
| Sparkles | Draw only a small number of HUD pixels near the wand tip |

The wand is a HUD overlay, so it does not affect collision, DDA traversal, or map validation.

---

## ⚠️ Error Handling

The program validates many failure cases before starting the game:

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
- MiniLibX image, window, or display allocation failure

Cleanup paths release allocated memory and MiniLibX resources before exiting on failure.

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

## 👨‍💻 Authors

**Aleksandre Davitashvili** (Adavitas) - *42 Student*  

[![GitHub](https://img.shields.io/badge/GitHub-Adavitas-181717?style=flat&logo=github)](https://github.com/Adavitas)

**Zhanat Zhyrgalbayeva** (zzhyrgal) - *42 Student*

[![GitHub](https://img.shields.io/badge/GitHub-zhibeeek-181717?style=flat&logo=github)](https://github.com/zhibeeek)

---

## 📝 License

This project is part of the 42 School curriculum.

---

*This project was created as part of the 42 School common core curriculum.*
