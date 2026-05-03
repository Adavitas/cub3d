/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 02:19:00 by adavitas          #+#    #+#             */
/*   Updated: 2026/03/12 20:25:03 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	draw_player_dot(t_game *game, int tsz)
{
	int	cx;
	int	cy;
	int	d[2];

	cx = MAP_PAD + (int)(game->player.x * tsz);
	cy = MAP_PAD + (int)(game->player.y * tsz);
	d[1] = -2;
	while (d[1] <= 2)
	{
		d[0] = -2;
		while (d[0] <= 2)
		{
			if (cy + d[1] >= MAP_PAD && cy + d[1] < MAP_PAD + MAP_H
				&& cx + d[0] >= MAP_PAD && cx + d[0] < MAP_PAD + MAP_W)
				game->screen.addr[(cy + d[1]) * WIN_W + (cx + d[0])]
					= rgb_to_int(200, 30, 30);
			d[0]++;
		}
		d[1]++;
	}
}

static void	draw_player_dir(t_game *game, int tsz)
{
	int		cx;
	int		cy;
	int		i;
	int		px;
	int		py;

	cx = MAP_PAD + (int)(game->player.x * tsz);
	cy = MAP_PAD + (int)(game->player.y * tsz);
	i = 0;
	while (i < 8)
	{
		px = cx + (int)(game->player.dir_x * i);
		py = cy + (int)(game->player.dir_y * i);
		if (py >= MAP_PAD && py < MAP_PAD + MAP_H
			&& px >= MAP_PAD && px < MAP_PAD + MAP_W)
			game->screen.addr[py * WIN_W + px] = rgb_to_int(200, 30, 30);
		i++;
	}
}

static int	get_tile_color(t_game *game, int mx, int my)
{
	int	wall_col;

	wall_col = rgb_to_int(game->ceiling.r / 2 + 40,
			game->ceiling.g / 2 + 40, game->ceiling.b / 2 + 40);
	if (is_wall_tile(game->map.grid[my][mx]))
		return (wall_col);
	if (game->map.grid[my][mx] == 'D' && !game->map.door_open[my][mx])
		return (rgb_to_int(180, 120, 40));
	if (game->map.grid[my][mx] == 'D' && game->map.door_open[my][mx])
		return (rgb_to_int(90, 60, 20));
	if (game->map.grid[my][mx] == '0')
		return (rgb_to_int(18, 18, 25));
	return (-1);
}

static void	draw_map_tiles(t_game *game, int tsz)
{
	int	mx;
	int	my;
	int	pos[2];
	int	color;

	my = 0;
	while (my < game->map.height)
	{
		mx = 0;
		while (mx < game->map.raw_max_width)
		{
			color = get_tile_color(game, mx, my);
			if (color >= 0)
			{
				pos[0] = mx;
				pos[1] = my;
				draw_tile(game, pos, tsz, color);
			}
			mx++;
		}
		my++;
	}
}

void	draw_minimap(t_game *game)
{
	int	tsz;
	int	tx;
	int	ty;

	tx = MAP_W / game->map.raw_max_width;
	ty = MAP_H / game->map.height;
	tsz = tx;
	if (ty < tx)
		tsz = ty;
	draw_border(game, tsz);
	draw_map_tiles(game, tsz);
	draw_player_dot(game, tsz);
	draw_player_dir(game, tsz);
}
