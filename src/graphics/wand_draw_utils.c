/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wand_draw_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 17:30:00 by adavitas          #+#    #+#             */
/*   Updated: 2026/04/30 17:30:00 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	is_wand_transparent(int color)
{
	int	rgb;
	int	r;
	int	g;
	int	b;

	rgb = color & 0x00FFFFFF;
	if (rgb == WAND_TRANSPARENT_COLOR)
		return (1);
	if ((color & 0xFF000000) == 0xFF000000)
		return (1);
	r = (rgb >> 16) & 255;
	g = (rgb >> 8) & 255;
	b = rgb & 255;
	if (r >= WAND_KEY_R_MIN && g <= WAND_KEY_G_MAX
		&& b >= WAND_KEY_B_MIN)
		return (1);
	return (0);
}

static void	put_wand_pixel(t_game *game, int x, int y, int color)
{
	int	stride;

	if (is_wand_transparent(color))
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

void	draw_wand_unscaled(t_game *game, t_tex *frame, int *pos,
		int *clip)
{
	int	stride[2];
	int	color;
	int	x;
	int	y;

	stride[0] = frame->line_len / 4;
	stride[1] = game->screen.line_len / 4;
	y = clip[2];
	while (y < clip[3])
	{
		x = clip[0];
		while (x < clip[1])
		{
			color = frame->addr[y * stride[0] + x];
			if (!is_wand_transparent(color))
				game->screen.addr[(pos[1] + y) * stride[1]
					+ pos[0] + x] = color;
			x++;
		}
		y++;
	}
}

void	draw_wand_scaled(t_game *game, t_tex *frame, int *pos, int *clip)
{
	int	src[2];

	src[1] = clip[2];
	while (src[1] < clip[3])
	{
		src[0] = clip[0];
		while (src[0] < clip[1])
		{
			draw_scaled_pixel(game, frame, pos, src);
			src[0]++;
		}
		src[1]++;
	}
}
