/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 02:39:29 by adavitas          #+#    #+#             */
/*   Updated: 2026/03/12 20:25:03 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	draw_bg(t_game *game, int mw, int mh)
{
	int	x;
	int	y;

	y = MAP_PAD - 2;
	while (y < MAP_PAD + mh + 2)
	{
		x = MAP_PAD - 2;
		while (x < MAP_PAD + mw + 2)
		{
			if (x >= 0 && x < WIN_W && y >= 0 && y < WIN_H)
				game->screen.addr[y * WIN_W + x] = rgb_to_int(5, 5, 8);
			x++;
		}
		y++;
	}
}

static void	draw_border_h(t_game *game, int mw, int mh, int color)
{
	int	x;
	int	y;

	x = MAP_PAD - 2;
	while (x < MAP_PAD + mw + 2)
	{
		y = MAP_PAD - 2;
		while (y < MAP_PAD)
		{
			if (x >= 0 && x < WIN_W && y >= 0 && y < WIN_H)
				game->screen.addr[y * WIN_W + x] = color;
			y++;
		}
		y = MAP_PAD + mh;
		while (y < MAP_PAD + mh + 2)
		{
			if (x >= 0 && x < WIN_W && y >= 0 && y < WIN_H)
				game->screen.addr[y * WIN_W + x] = color;
			y++;
		}
		x++;
	}
}

static void	draw_border_v(t_game *game, int mw, int mh, int color)
{
	int	x;
	int	y;

	y = MAP_PAD;
	while (y < MAP_PAD + mh)
	{
		x = MAP_PAD - 2;
		while (x < MAP_PAD)
		{
			if (x >= 0 && x < WIN_W && y >= 0 && y < WIN_H)
				game->screen.addr[y * WIN_W + x] = color;
			x++;
		}
		x = MAP_PAD + mw;
		while (x < MAP_PAD + mw + 2)
		{
			if (x >= 0 && x < WIN_W && y >= 0 && y < WIN_H)
				game->screen.addr[y * WIN_W + x] = color;
			x++;
		}
		y++;
	}
}

void	draw_border(t_game *game, int tsz)
{
	int	mw;
	int	mh;
	int	border_col;

	mw = game->map.raw_max_width * tsz;
	mh = game->map.height * tsz;
	if (mw > MAP_W)
		mw = MAP_W;
	if (mh > MAP_H)
		mh = MAP_H;
	border_col = rgb_to_int(game->ceiling.r / 2 + 50,
			game->ceiling.g / 2 + 50, game->ceiling.b / 2 + 50);
	draw_bg(game, mw, mh);
	draw_border_h(game, mw, mh, border_col);
	draw_border_v(game, mw, mh, border_col);
}

void	draw_tile(t_game *game, int *pos, int tsz, int color)
{
	int	px;
	int	py;
	int	sx;
	int	sy;

	py = 0;
	while (py < tsz)
	{
		px = 0;
		while (px < tsz)
		{
			sx = MAP_PAD + pos[0] * tsz + px;
			sy = MAP_PAD + pos[1] * tsz + py;
			if (sx < MAP_PAD + MAP_W && sy < MAP_PAD + MAP_H)
			{
				if (px == 0 || py == 0)
					game->screen.addr[sy * WIN_W + sx]
						= rgb_to_int(8, 8, 12);
				else
					game->screen.addr[sy * WIN_W + sx] = color;
			}
			px++;
		}
		py++;
	}
}
