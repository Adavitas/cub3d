/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wand.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 04:30:12 by adavitas          #+#    #+#             */
/*   Updated: 2026/05/04 05:42:08 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef WAND_H
# define WAND_H
# include "raycast.h"

typedef struct s_game	t_game;

# define WAND_FRAME_COUNT 6
# define WAND_SCALE 1
# define WAND_BOTTOM_MARGIN 24
# define WAND_X_OFFSET 120
# define WAND_Y_OFFSET 24
# define WAND_TURN_TICKS 6
# define WAND_FLICKER_TICKS 18
# define WAND_BOB_SPEED 12.0f
# define WAND_BOB_X 10.0f
# define WAND_BOB_Y 12.0f
# define WAND_BOB_RETURN 0.82f
# define WAND_MOVE_EPSILON 0.00005f
# define WAND_TRANSPARENT_COLOR 0x00FF00FF
# define WAND_KEY_R_MIN 210
# define WAND_KEY_G_MAX 90
# define WAND_KEY_B_MIN 210
# define WAND_PINK_R_MIN 90
# define WAND_PINK_B_MIN 75
# define WAND_PINK_RGAP 30
# define WAND_PINK_BGAP 25
# define WAND_SPARKLE_TICKS 3
# define WAND_SPARKLE_RADIUS 3
# define WAND_SPARKLE_COUNT 9
# define WAND_TIP_GLOW_MIN 0.04f
# define WAND_TIP_GLOW_RADIUS 16
# define WAND_TIP_GLOW_POWER 0.45f
# define WAND_LIGHT_ON_GAIN 0.34f
# define WAND_LIGHT_OFF_GAIN 0.28f
# define WAND_LIGHT_SNAP 0.02f
# define WAND_TIP_TURN1_X 112
# define WAND_TIP_TURN1_Y 66
# define WAND_TIP_TURN2_X 130
# define WAND_TIP_TURN2_Y 76
# define WAND_TIP_TURN3_X 160
# define WAND_TIP_TURN3_Y 66
# define WAND_TIP_ON_X 125
# define WAND_TIP_ON_Y 62
# define WAND_LIGHT_MIN 0.001f
# define RENDER_DARK_FOG_DIST 8.0f
# define RENDER_LIT_FOG_DIST 18.0f
# define WAND_DARK_AMBIENT 0.38f
# define WAND_LIT_AMBIENT 0.86f
# define WAND_LIGHT_RANGE 10.0f
# define WAND_LIGHT_POWER 1.15f
# define WAND_LIGHT_CENTER_Y 0.68f
# define WAND_LIGHT_SCREEN_RANGE 0.78f
# define WAND_LIGHT_R 95
# define WAND_LIGHT_G 68
# define WAND_LIGHT_B 20
# define WAND_SKY_POWER 0.32f

typedef enum e_wand_state
{
	WAND_OFF,
	WAND_TURNING_ON,
	WAND_ON,
	WAND_TURNING_OFF
}	t_wand_state;

typedef enum e_wand_frame
{
	WAND_FRAME_OFF,
	WAND_FRAME_TURN_1,
	WAND_FRAME_TURN_2,
	WAND_FRAME_TURN_3,
	WAND_FRAME_ON_A,
	WAND_FRAME_ON_B
}	t_wand_frame;

typedef struct s_wand
{
	t_wand_state	state;
	t_tex			frame[WAND_FRAME_COUNT];
	int				frame_id;
	int				anim_tick;
	int				sparkle_tick;
	float			light_level;
	float			phase;
	float			bob_x;
	float			bob_y;
	float			last_x;
	float			last_y;
}	t_wand;

int		init_wand(t_game *game);
void	destroy_wand_images(t_game *game);
void	free_wand(t_wand *wand);
void	toggle_wand(t_game *game);
void	update_wand(t_game *game);
void	update_wand_light(t_game *game);

#endif
