/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wand.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 12:00:00 by adavitas          #+#    #+#             */
/*   Updated: 2026/04/29 12:00:00 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	put_wand_pixel(t_game *game, int x, int y, int color)
{
	int	stride;

	if ((color & 0x00FFFFFF) == WAND_TRANSPARENT_COLOR)
		return ;
	if (x < 0 || y < 0 || x >= WIN_W || y >= WIN_H)
		return ;
	stride = game->screen.line_len / 4;
	game->screen.addr[y * stride + x] = color;
}

static void	draw_scaled_pixel(t_game *game, t_tex *frame, int *pos, int *src)
{
	int	color;
	int	scale[2];
	int	dst[2];

	color = frame->addr[src[1] * (frame->line_len / 4) + src[0]];
	scale[1] = 0;
	while (scale[1] < WAND_SCALE)
	{
		scale[0] = 0;
		while (scale[0] < WAND_SCALE)
		{
			dst[0] = pos[0] + src[0] * WAND_SCALE + scale[0];
			dst[1] = pos[1] + src[1] * WAND_SCALE + scale[1];
			put_wand_pixel(game, dst[0], dst[1], color);
			scale[0]++;
		}
		scale[1]++;
	}
}

static void	draw_wand_row(t_game *game, t_tex *frame, int *pos, int row)
{
	int	src[2];

	src[0] = 0;
	src[1] = row;
	while (src[0] < frame->width)
	{
		draw_scaled_pixel(game, frame, pos, src);
		src[0]++;
	}
}

static void	get_wand_pos(t_game *game, t_tex *frame, int *pos)
{
	int	draw_w;
	int	draw_h;

	draw_w = frame->width * WAND_SCALE;
	draw_h = frame->height * WAND_SCALE;
	pos[0] = (WIN_W - draw_w) / 2 + (int)game->wand.bob_x;
	pos[1] = WIN_H - draw_h - WAND_BOTTOM_MARGIN
		+ (int)game->wand.bob_y;
}

void	draw_wand(t_game *game)
{
	t_tex	*frame;
	int		pos[2];
	int		row;

	frame = &game->wand.frame[game->wand.frame_id];
	if (!frame->img || !frame->addr)
		return ;
	get_wand_pos(game, frame, pos);
	row = 0;
	while (row < frame->height)
	{
		draw_wand_row(game, frame, pos, row);
		row++;
	}
}
