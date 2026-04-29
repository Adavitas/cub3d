# Cub3D Wand Feature

The wand is a first-person HUD overlay with a lighter-style warm room lift.
It is kept separate from `game->tex[7]` in `t_game.wand`, and its six XPM
frames are loaded from `./textures/wand/`.

## Control

- `R` keeps the existing door behavior.
- `F` toggles the wand between off and on.

## States

- `WAND_OFF` draws `wand_off_idle.xpm`.
- `WAND_TURNING_ON` plays `wand_turn_1.xpm`, `wand_turn_2.xpm`,
  then `wand_turn_3.xpm`.
- `WAND_ON` alternates `wand_on_idle_a.xpm` and `wand_on_idle_b.xpm`.
- `WAND_TURNING_OFF` reuses the turn frames in reverse order.

## Rendering

`draw_wand()` writes into `game->screen` after the world and minimap are
drawn and before `mlx_put_image_to_window()`. Pixels matching
`WAND_TRANSPARENT_COLOR` are skipped, so the wand sprites use magenta as
their configurable color key.

The bob and sway are computed after movement from the actual player position
delta between frames. If collision blocks movement, the position does not
change and the bob decays instead of advancing.

## Lighting

The lighter effect extends the existing fog/shading path only. Walls and floor
receive a warm additive lift with distance and screen-space falloff. The sky
uses a smaller warm lift so the room reacts without adding real dynamic
shadows.

## Assets

- `textures/wand/wand_off_idle.xpm`
- `textures/wand/wand_turn_1.xpm`
- `textures/wand/wand_turn_2.xpm`
- `textures/wand/wand_turn_3.xpm`
- `textures/wand/wand_on_idle_a.xpm`
- `textures/wand/wand_on_idle_b.xpm`

## Tunable Constants

The main constants live in `includes/game.h`: `WAND_SCALE`,
`WAND_BOTTOM_MARGIN`, `WAND_TURN_TICKS`, `WAND_FLICKER_TICKS`,
`WAND_BOB_SPEED`, `WAND_BOB_X`, `WAND_BOB_Y`, `WAND_BOB_RETURN`,
`WAND_TRANSPARENT_COLOR`, `RENDER_FOG_DIST`, `WAND_LIGHT_RANGE`,
`WAND_LIGHT_POWER`, `WAND_LIGHT_CENTER_Y`, `WAND_LIGHT_SCREEN_RANGE`,
`WAND_LIGHT_R`, `WAND_LIGHT_G`, `WAND_LIGHT_B`, and `WAND_SKY_POWER`.
