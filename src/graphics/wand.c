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

static void	get_wand_pos(t_game *game, t_tex *frame, int *pos)
{
	int	draw_w;
	int	draw_h;

	draw_w = frame->width * WAND_SCALE;
	draw_h = frame->height * WAND_SCALE;
	pos[0] = (WIN_W - draw_w) / 2 + WAND_X_OFFSET
		+ (int)game->wand.bob_x;
	pos[1] = WIN_H - draw_h - WAND_BOTTOM_MARGIN
		+ WAND_Y_OFFSET + (int)game->wand.bob_y;
}

static void	set_clip_axis(int pos, int len, int limit, int *clip)
{
	clip[0] = 0;
	clip[1] = len;
	if (pos < 0)
		clip[0] = (-pos + WAND_SCALE - 1) / WAND_SCALE;
	if (pos + len * WAND_SCALE > limit)
		clip[1] = (limit - pos + WAND_SCALE - 1) / WAND_SCALE;
	if (clip[0] < 0)
		clip[0] = 0;
	if (clip[1] > len)
		clip[1] = len;
}

static void	set_wand_clip(t_tex *frame, int *pos, int *clip)
{
	set_clip_axis(pos[0], frame->width, WIN_W, &clip[0]);
	set_clip_axis(pos[1], frame->height, WIN_H, &clip[2]);
}

void	draw_wand(t_game *game)
{
	t_tex	*frame;
	int		pos[2];
	int		clip[4];

	frame = &game->wand.frame[game->wand.frame_id];
	if (!frame->img || !frame->addr)
		return ;
	get_wand_pos(game, frame, pos);
	set_wand_clip(frame, pos, clip);
	if (clip[0] >= clip[1] || clip[2] >= clip[3])
		return ;
	if (WAND_SCALE == 1)
		draw_wand_unscaled(game, frame, pos, clip);
	else
		draw_wand_scaled(game, frame, pos, clip);
}
