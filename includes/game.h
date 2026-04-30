/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 12:46:13 by zzhyrgal          #+#    #+#             */
/*   Updated: 2026/03/13 13:19:32 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdbool.h>
# include <math.h>
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif
# include "mlx.h"
# include "libft.h"
# include "parse.h"
# include "player.h"
# include "raycast.h"

# define WIN_W 1280
# define WIN_H 720
# define TEX_W 64
# define TEX_H 64
# define MAP_W 200
# define MAP_H 200
# define MAP_PAD 10
# define MOUSE_SENS 0.001
# define WAND_FRAME_COUNT 6
# define WAND_SCALE 1
# define WAND_BOTTOM_MARGIN 24
# define WAND_X_OFFSET 120
# define WAND_Y_OFFSET 24
# define WAND_TURN_TICKS 6
# define WAND_FLICKER_TICKS 18
# define WAND_BOB_SPEED 24.0f
# define WAND_BOB_X 10.0f
# define WAND_BOB_Y 12.0f
# define WAND_BOB_RETURN 0.82f
# define WAND_MOVE_EPSILON 0.00005f
# define WAND_TRANSPARENT_COLOR 0x00FF00FF
# define WAND_KEY_R_MIN 210
# define WAND_KEY_G_MAX 90
# define WAND_KEY_B_MIN 210
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

typedef struct s_img
{
	void	*img;
	int		*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

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
	float			light_level;
	float			phase;
	float			bob_x;
	float			bob_y;
	float			last_x;
	float			last_y;
}	t_wand;

typedef struct s_light_cache
{
	float	level;
	float	fog_dist;
	float	ambient;
	float	sky_power;
	float	screen_falloff[WIN_H];
}	t_light_cache;

typedef struct s_game
{
	t_map			map;
	t_tex			tex[7];
	t_color			floor;
	t_color			ceiling;
	bool			map_started;
	t_player		player;
	t_key			key;
	t_wand			wand;
	int				mouse_active;
	void			*mlx;
	void			*win;
	t_img			screen;
	t_light_cache	light;
}	t_game;

void	init_game(t_game *game);
int		init_mlx(t_game *game);
int		close_game(t_game *game);
int		init_wand(t_game *game);
int		fail_mlx_init(t_game *game);
void	destroy_mlx_resources(t_game *game);
void	destroy_wand_images(t_game *game);
void	free_wand(t_wand *wand);

#endif
