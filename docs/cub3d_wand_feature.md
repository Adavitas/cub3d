# Cub3D Wand Feature

## Feature Overview

The wand is a first-person HUD overlay with a lighter-style warm room
illumination effect. Press `F` to raise or lower it. Door interaction remains
on `R`.

The feature has four runtime states: off, turning on, on, and turning off. The
wand is always visible as a HUD item; `WAND_OFF` draws the idle-off frame while
leaving the lighter illumination disabled.

## Why Wand Assets Are Separate From World Textures

World raycast textures stay in `game->tex[7]`. The wand uses `t_game.wand`
instead, with its own `t_tex frame[WAND_FRAME_COUNT]` array. This keeps HUD
art out of the wall/floor/sky/door texture slots and avoids relying on the
out-of-range `game->tex[7]` index.

## Files Changed

- `Makefile`
- `includes/game.h`
- `includes/player.h`
- `includes/raycast.h`
- `src/player_movement/update_player.c`
- `src/player_movement/wand_state.c`
- `src/graphics/init_mlx.c`
- `src/graphics/close_game.c`
- `src/graphics/mlx_cleanup.c`
- `src/graphics/render.c`
- `src/graphics/render_light.c`
- `src/graphics/render_light_utils.c`
- `src/graphics/wand.c`
- `src/graphics/wand_resources.c`
- `src/graphics/wand_cleanup.c`
- `src/clean_up/free_game.c`
- `textures/wand/wand_off_idle.xpm`
- `textures/wand/wand_turn_1.xpm`
- `textures/wand/wand_turn_2.xpm`
- `textures/wand/wand_turn_3.xpm`
- `textures/wand/wand_on_idle_a.xpm`
- `textures/wand/wand_on_idle_b.xpm`
- `docs/cub3d_wand_feature.md`

## State Machine

- `WAND_OFF`: draws `wand_off_idle.xpm` with no lighting lift.
- `WAND_TURNING_ON`: plays `wand_turn_1.xpm`, `wand_turn_2.xpm`,
  `wand_turn_3.xpm` in order.
- `WAND_ON`: alternates `wand_on_idle_a.xpm` and `wand_on_idle_b.xpm` for
  subtle flicker.
- `WAND_TURNING_OFF`: plays the turn frames in reverse and returns to
  `WAND_OFF`.

`F` input is latched with `game->key.f`, so holding the key through X11
auto-repeat does not repeatedly toggle the state. Extra presses during a turn
animation are ignored because `toggle_wand()` only acts from `WAND_OFF` or
`WAND_ON`.

## Asset Filenames

- `./textures/wand/wand_off_idle.xpm`
- `./textures/wand/wand_turn_1.xpm`
- `./textures/wand/wand_turn_2.xpm`
- `./textures/wand/wand_turn_3.xpm`
- `./textures/wand/wand_on_idle_a.xpm`
- `./textures/wand/wand_on_idle_b.xpm`

## Render Order

The frame loop updates movement, mouse rotation, and wand animation before
rendering. `render_frame()` draws the sky, walls, and floor into
`game->screen`, draws the minimap, draws the wand HUD overlay, then presents
the completed buffer with `mlx_put_image_to_window()`.

## Transparent Blit Behavior

`draw_wand()` composites into the off-screen `game->screen` buffer. The source
XPM color key is magenta, configured by `WAND_TRANSPARENT_COLOR`. The blitter
uses `(color & 0x00FFFFFF) == WAND_TRANSPARENT_COLOR`, so any unused high byte
from MLX does not affect transparency. Destination writes are bounds-checked
before touching `game->screen.addr`.

## Bobbing Logic

`update_wand()` runs after player movement. It compares the current player
position to `game->wand.last_x` and `game->wand.last_y`. If the player actually
moved, the bob phase advances from that position delta. If collision blocked
movement, the position does not change, so bob and sway decay instead of
advancing.

## Lighting Logic

The lighter effect extends the existing fog path only. Walls and floor use
`apply_wand_fog()`, which first applies the normal distance fog and then adds a
warm local lift based on wand state, wall/floor distance, and vertical
screen-space falloff. The sky uses `apply_wand_sky()` with a softer warm lift.
There are no real dynamic shadows or extra light rays.

When the wand is off, `wand_state_light()` returns zero. That leaves wall,
floor, and sky colors at the original fog/texture result while the off-idle HUD
frame remains visible.

## Tunable Constants

The main knobs live in `includes/game.h`:

- `WAND_FRAME_COUNT`
- `WAND_SCALE`
- `WAND_BOTTOM_MARGIN`
- `WAND_TURN_TICKS`
- `WAND_FLICKER_TICKS`
- `WAND_BOB_SPEED`
- `WAND_BOB_X`
- `WAND_BOB_Y`
- `WAND_BOB_RETURN`
- `WAND_MOVE_EPSILON`
- `WAND_TRANSPARENT_COLOR`
- `RENDER_FOG_DIST`
- `WAND_LIGHT_RANGE`
- `WAND_LIGHT_POWER`
- `WAND_LIGHT_CENTER_Y`
- `WAND_LIGHT_SCREEN_RANGE`
- `WAND_LIGHT_R`
- `WAND_LIGHT_G`
- `WAND_LIGHT_B`
- `WAND_SKY_POWER`

## Cleanup / Destroy Paths

Wand frame images are loaded by `init_wand()` in `src/graphics/wand_resources.c`.
Normal shutdown calls `close_game()`, which delegates MLX resource destruction
to `destroy_mlx_resources()`. That destroys world texture images, wand frame
images through `destroy_wand_images()`, the screen image, the window, and the
MLX display.

Heap-owned texture paths are released by `free_game()`: world texture paths go
through `free_tex()`, and wand frame paths go through `free_wand()`.

If initialization fails after MLX resources exist, `init_mlx()` returns through
`fail_mlx_init()`, which delegates to `destroy_mlx_resources()`. `main()` then
calls `free_game()` for the remaining parsed map and path allocations.

## Known Limitations

- The HUD uses fixed pixel scaling for the current `1280x720` window.
- Transparency is color-key based, not alpha blended.
- The lighter effect is a stylized fog/brightness lift, not dynamic shadows.
- Wand art is loaded from XPM files only.
- Animation timing is frame-count based, not time-delta based.

## How To Replace The Art Safely

Keep the same six filenames in `./textures/wand/` unless you also update
`get_wand_path()` in `src/graphics/wand_resources.c`. Preserve magenta
`#FF00FF` for transparent pixels or update `WAND_TRANSPARENT_COLOR` to match
the new key. Keep dimensions small enough for `WAND_SCALE` and
`WAND_BOTTOM_MARGIN` to fit on screen. After replacing art, run `make` so MLX
loads every frame and run the manual checklist below.

## Manual Test Checklist

- Run `make`.
- Run `norminette` on changed `.c` and `.h` files.
- Launch a valid map.
- Confirm wand-off view shows `wand_off_idle.xpm` without warm lighting.
- Press `F` once and confirm the three turn-on frames play in order.
- Hold `F` and confirm key repeat does not toggle repeatedly.
- Press `F` again after the wand is on and confirm turn-off frames play in
  reverse.
- Walk forward and strafe; confirm bob/sway follows actual movement.
- Walk into a wall; confirm blocked movement does not advance bob.
- Confirm warm lighting appears on walls and floor while the wand is on.
- Confirm the sky gets only a softer warm lift.
- Confirm `R` still opens and closes doors.
- Confirm the minimap is drawn before the wand overlay.
- Close the window or press Escape and confirm the program exits cleanly.
