# Cub3D Wand Feature

## Feature Overview

The wand is a top-half first-person HUD overlay with a lighter-style warm room
illumination effect. Press `F` to raise or lower it. Door interaction remains
on `R`.

The feature has four runtime states: off, turning on, on, and turning off. The
wand is always visible as a HUD item; `WAND_OFF` draws the idle-off frame while
leaving the lighter illumination disabled.

The current art enters from the right-hand side. The lower shaft is
intentionally cropped by the bottom of the screen so it feels like it continues
off-screen instead of floating above the HUD. The off frame is lowered and
slightly left-inclined, the turn frames raise the wand, and the on frames are
straighter and more upright. A hand was intentionally not added in this pass:
no hand art is generated, loaded, or drawn by the wand feature.

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
- `src/player_movement/wand_light.c`
- `src/graphics/init_mlx.c`
- `src/graphics/close_game.c`
- `src/graphics/mlx_cleanup.c`
- `src/graphics/render.c`
- `src/graphics/render_light.c`
- `src/graphics/render_light_utils.c`
- `src/graphics/wand.c`
- `src/graphics/wand_draw_utils.c`
- `src/graphics/wand_sparkles.c`
- `src/graphics/wand_sparkles_utils.c`
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

MiniLibX key auto-repeat is disabled while the game is running and restored
during MLX cleanup. `F` input is also latched with `game->key.f`, so holding the
key does not repeatedly toggle the state. Pressing `F` during
`WAND_TURNING_ON` reverses into `WAND_TURNING_OFF`, and pressing it during
`WAND_TURNING_OFF` reverses into `WAND_TURNING_ON`. The current turn frame is
kept, so the visual transition changes direction without restarting from the
endpoints.

The smooth transition fix is `wand.light_level`, which is separate from
`frame_id`. Sprite animation still advances every `WAND_TURN_TICKS`, but
lighting now approaches its target with separate turn-on and turn-off gains.
This gives the first part of the fade a quicker response while still easing
into the endpoint. Rapid `F` reversals fade from the current `light_level`
instead of snapping to an endpoint.

## Asset Filenames

The same six XPM filenames are required:

- `./textures/wand/wand_off_idle.xpm`
- `./textures/wand/wand_turn_1.xpm`
- `./textures/wand/wand_turn_2.xpm`
- `./textures/wand/wand_turn_3.xpm`
- `./textures/wand/wand_on_idle_a.xpm`
- `./textures/wand/wand_on_idle_b.xpm`

The current art is `240x320` for every frame and `WAND_SCALE` is `1`, so the
HUD draw path samples exactly one source pixel per destination pixel. At
`1280x720`, `get_wand_pos()` places the wand at
`(WIN_W - 240) / 2 + WAND_X_OFFSET` and
`WIN_H - 320 - WAND_BOTTOM_MARGIN + WAND_Y_OFFSET`, plus movement bob offsets.
With the current constants, the lower shaft is intentionally cropped by the
bottom of the screen.

## Render Order

The frame loop updates movement, mouse rotation, and wand animation before
rendering. `render_frame()` draws the sky, walls, and floor into
`game->screen`, draws the minimap, draws the wand HUD overlay, draws wand-tip
sparkles, then presents the completed buffer with `mlx_put_image_to_window()`.

`draw_wand()` has a clipped unscaled path for `WAND_SCALE == 1`. It computes the
visible source rectangle once, caches frame and screen strides, skips keyed
pixels, and writes directly into `game->screen`. The older scaled per-pixel path
remains only as a fallback if `WAND_SCALE` is raised again.

`draw_wand_sparkles()` runs after the wand blit and before presenting the frame.
It draws up to six clipped yellow, orange, and white HUD sparkles near the
current wand tip when cached `game->light.level` is above `WAND_TIP_GLOW_MIN`.
The sparkle pattern uses the current wand frame, a small `sparkle_tick`, the
same HUD position offsets, and the existing bob values, but it does not change
bob, movement, rotation, or world lighting. It does not scan the screen or XPM
data per frame.

## Transparent Blit Behavior

`draw_wand()` composites into the off-screen `game->screen` buffer. The current
XPM files use `None` for transparent pixels, and the blitter also supports the
old magenta `#FF00FF` key through `WAND_TRANSPARENT_COLOR`.

The pink artifact fix is two-part: wand assets avoid baked glow or JPEG-style
magenta fringe pixels, and `is_wand_transparent()` skips exact magenta, MLX/XPM
`None` pixels with the high byte set, near-magenta key pixels, and the broader
`WAND_PINK_*` purple-fringe range.

The ON idle frames are generated from the same lit base frame. Both contain the
same bulb/core at the wand tip; `wand_on_idle_b.xpm` changes only a small set of
warm highlight pixels so the idle animation reads as shine instead of switching
between bulb and no-bulb art. The procedural sparkle overlay provides the moving
shine, so future ON XPMs should keep the bulb/core stable instead of baking a
large halo into either frame.

Because XPM color-key transparency has no alpha blending, do not bake soft glow
halos over a magenta background. Those pixels become visible pink or purple
edges at runtime. The wand tip should stay solid art pixels, or a small glow can
be drawn procedurally later.

## Bobbing Logic

`update_wand()` runs after player movement. It compares the current player
position to `game->wand.last_x` and `game->wand.last_y`. If the player actually
moved, the bob phase advances from that position delta. If collision blocked
movement, the position does not change, so bob and sway decay instead of
advancing.

The walking and bob behavior was intentionally preserved for the sparkle pass.
`update_wand_bob()` and the `WAND_BOB_*` constants were not retuned.

Movement and keyboard rotation still use fixed per-frame constants:
`M_SPEED == 0.02` and `ROTATE_SPEED == 0.02`. Frame-time scaling was not added
because this repo does not include a cub3d subject or allowed-functions file
that verifies a timing function such as `gettimeofday`. The equal-feel fix for
wand OFF versus ON therefore comes from reducing the ON render cost so the frame
rate stays close to the OFF path.

## Lighting Logic

The lighter effect extends the existing fog path only. Walls and floor use
`apply_wand_fog()`, which uses values cached by `prepare_wand_light()` at the
start of `render_frame()`. The cache stores the current 0.0 to 1.0 light level,
fog distance, ambient brightness, sky power, inverse light range,
`screen_falloff[WIN_H]`, `warm_power[WIN_H]`, and `sky_row_power[WIN_H]` for the
frame. Per-pixel wall, floor, and sky lighting then reuses those cached values
instead of recalculating wand state, distance constants, and row powers for
every shaded pixel.

When the wand is off, the world is intentionally darker: nearby surfaces keep
some readable ambient light, while distant walls and floor fall into shorter,
darker fog. During turn-on and turn-off, the same wand light value ramps the
fog distance, ambient brightness, and warm lift smoothly. When the wand is on,
nearby walls and floor get a stronger warm boost while far surfaces remain
darker.

The sky uses `apply_wand_sky()` with the same ambient lerp and a softer warm
lift controlled by `WAND_SKY_POWER`. There are no real dynamic shadows or extra
light rays.

The minimap and wand HUD are drawn after the sky, walls, and floor are shaded,
so the darker world lighting does not darken either overlay.

## Tunable Constants

The main knobs live in `includes/game.h`:

- `WAND_FRAME_COUNT`
- `WAND_SCALE` (`1` for the current `240x320` art)
- `WAND_BOTTOM_MARGIN` (`24`)
- `WAND_X_OFFSET` (`120`)
- `WAND_Y_OFFSET` (`24`)
- `WAND_TURN_TICKS`
- `WAND_FLICKER_TICKS`
- `WAND_BOB_SPEED`
- `WAND_BOB_X`
- `WAND_BOB_Y`
- `WAND_BOB_RETURN`
- `WAND_MOVE_EPSILON`
- `WAND_TRANSPARENT_COLOR` (`0x00FF00FF`)
- `WAND_KEY_R_MIN` (`210`)
- `WAND_KEY_G_MAX` (`90`)
- `WAND_KEY_B_MIN` (`210`)
- `WAND_PINK_R_MIN`
- `WAND_PINK_B_MIN`
- `WAND_PINK_RGAP`
- `WAND_PINK_BGAP`
- `WAND_SPARKLE_TICKS`
- `WAND_SPARKLE_RADIUS`
- `WAND_SPARKLE_COUNT`
- `WAND_TIP_GLOW_MIN`
- `WAND_LIGHT_ON_GAIN`
- `WAND_LIGHT_OFF_GAIN`
- `WAND_LIGHT_SNAP`
- `WAND_TIP_TURN1_X`
- `WAND_TIP_TURN1_Y`
- `WAND_TIP_TURN2_X`
- `WAND_TIP_TURN2_Y`
- `WAND_TIP_TURN3_X`
- `WAND_TIP_TURN3_Y`
- `WAND_TIP_ON_X`
- `WAND_TIP_ON_Y`
- `WAND_LIGHT_MIN`
- `RENDER_DARK_FOG_DIST`
- `RENDER_LIT_FOG_DIST`
- `WAND_DARK_AMBIENT`
- `WAND_LIT_AMBIENT`
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
- Transparency is still color-key based, not alpha blended; near-magenta
  skipping is a cleanup guard for borders, not real alpha support.
- Wand-off darkness and wand-on warmth are stylized fog, ambient, and
  brightness lifts, not physical lighting or dynamic shadows.
- Wand art is loaded from XPM files only.
- Hand art is not included unless all six replacement hand+wand XPM frames are
  supplied.
- Movement, keyboard rotation, sprite animation, and light easing are still
  frame-count based, not time-delta based.

## How To Replace The Art Safely

Keep the same six filenames in `./textures/wand/` unless you also update
`get_wand_path()` in `src/graphics/wand_resources.c`.

Future asset-generation rules:

- Generate from PNG or clean source art, not JPEG.
- For hand art, provide one combined hand+wand XPM per required filename:
  `wand_off_idle.xpm`, `wand_turn_1.xpm`, `wand_turn_2.xpm`,
  `wand_turn_3.xpm`, `wand_on_idle_a.xpm`, and `wand_on_idle_b.xpm`.
- Treat hand art as a complete matching pack: all six frames must share the
  same dimensions and alignment, and partial hand replacements should not be
  mixed with the current handless wand frames.
- Prefer XPM `None` transparency for the background.
- If using a color key, keep it exact `#FF00FF`; do not antialias or blur into
  the keyed background.
- Do not bake translucent glow onto transparent/keyed pixels.
- Keep ON idle A/B generated from the same palette style and transparency rules
  as the turn/off frames.
- Avoid pink, purple, or magenta tones in visible wand art unless the blitter
  thresholds are retuned, because those colors may be treated as transparent.
- Keep all six frames the same dimensions.
- If dimensions change from `240x320`, retune `WAND_SCALE`,
  `WAND_BOTTOM_MARGIN`, `WAND_X_OFFSET`, and `WAND_Y_OFFSET`.
- Keep `WAND_SCALE == 1` unless the replacement art is intentionally authored
  for nearest-neighbor scaling; larger scales use the slower fallback path.

After replacing art, run `make` so MLX loads every frame and run the manual
checklist below.

## Manual Test Checklist

- Run `make`.
- Run `norminette` on changed `.c` and `.h` files.
- Launch a valid map.
- Confirm the wand is not blocky or visibly pixelated.
- Confirm there is no pink border around the wand.
- Confirm wand-off view shows `wand_off_idle.xpm` and the world is darker.
- Press `F` once and confirm the three turn-on frames play in order.
- Hold `F` and confirm key repeat does not toggle repeatedly.
- Press `F` again after the wand is on and confirm turn-off frames play in
  reverse.
- Walk forward and strafe; confirm bob/sway follows actual movement.
- Walk into a wall; confirm blocked movement does not advance bob.
- Confirm the room brightens during the turn-on animation.
- Confirm stronger warm lighting appears on nearby walls and floor while the
  wand is on.
- With the wand on, confirm only tiny yellow, orange, and white tip sparkles
  appear and no pink or magenta pixels are visible.
- Confirm far walls and floor remain darker than nearby surfaces.
- Confirm the sky gets only a softer ambient and warm lift.
- Confirm the minimap and wand HUD remain readable and are not darkened.
- Confirm `R` still opens and closes doors.
- Confirm the minimap is drawn before the wand overlay.
- Close the window or press Escape and confirm the program exits cleanly.
