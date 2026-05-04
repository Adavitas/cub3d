/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 12:46:13 by zzhyrgal          #+#    #+#             */
/*   Updated: 2026/05/04 05:33:41 by adavitas         ###   ########.fr       */
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
# include "wand.h"

# define WIN_W 1280
# define WIN_H 720
# define TEX_W 64
# define TEX_H 64
# define MAP_W 200
# define MAP_H 200
# define MAP_PAD 10
# define MOUSE_SENS 0.001

typedef struct s_img
{
	void	*img;
	int		*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_light_cache
{
	float	level;
	float	fog_dist;
	float	ambient;
	float	sky_power;
	float	inv_range;
	float	screen_falloff[WIN_H];
	float	warm_power[WIN_H];
	float	sky_row_power[WIN_H];
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
int		fail_mlx_init(t_game *game);
void	destroy_mlx_resources(t_game *game);

#endif
