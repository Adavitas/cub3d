/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wand_sparkles.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 13:30:00 by adavitas          #+#    #+#             */
/*   Updated: 2026/05/03 13:30:00 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static int	get_spark_anchor(int frame_id, int *anchor)
{
	if (frame_id == WAND_FRAME_TURN_1)
	{
		anchor[0] = WAND_TIP_TURN1_X;
		anchor[1] = WAND_TIP_TURN1_Y;
		return (1);
	}
	if (frame_id == WAND_FRAME_TURN_2)
	{
		anchor[0] = WAND_TIP_TURN2_X;
		anchor[1] = WAND_TIP_TURN2_Y;
		return (1);
	}
	if (frame_id == WAND_FRAME_TURN_3)
	{
		anchor[0] = WAND_TIP_TURN3_X;
		anchor[1] = WAND_TIP_TURN3_Y;
		return (1);
	}
	anchor[0] = WAND_TIP_ON_X;
	anchor[1] = WAND_TIP_ON_Y;
	return (frame_id == WAND_FRAME_ON_A || frame_id == WAND_FRAME_ON_B);
}

static void	put_spark_pixel(t_game *game, int x, int y, int color)
{
	int	stride;

	if (x < 0 || y < 0 || x >= WIN_W || y >= WIN_H)
		return ;
	stride = game->screen.line_len / 4;
	game->screen.addr[y * stride + x] = color;
}

static void	draw_spark_cross(t_game *game, int x, int y, int color)
{
	int	i;

	i = -WAND_SPARKLE_RADIUS;
	while (i <= WAND_SPARKLE_RADIUS)
	{
		put_spark_pixel(game, x + i, y, color);
		put_spark_pixel(game, x, y + i, color);
		i++;
	}
}

static void	draw_spark_pattern(t_game *game, int *pos, int *anchor, int tick)
{
	int	limit;

	limit = 1;
	if (game->light.level > 0.45f)
		limit = 2;
	if (game->light.level > 0.75f)
		limit = WAND_SPARKLE_COUNT;
	draw_spark_cross(game, pos[0] + anchor[0] - 8 + tick % 3,
		pos[1] + anchor[1] - 5, 0x00FFFFFF);
	if (limit > 1)
		draw_spark_cross(game, pos[0] + anchor[0] + 7,
			pos[1] + anchor[1] - 2 + tick % 2, 0x00FFF3A0);
	if (limit > 2)
		draw_spark_cross(game, pos[0] + anchor[0] - 2,
			pos[1] + anchor[1] + 6 - tick % 3, 0x00FFD45A);
	if (limit > 3 && tick % WAND_SPARKLE_COUNT != 0)
		draw_spark_cross(game, pos[0] + anchor[0] + 2,
			pos[1] + anchor[1] - 9, 0x00FFFFFF);
}

void	draw_wand_sparkles(t_game *game)
{
	t_tex	*frame;
	int		pos[2];
	int		anchor[2];
	int		size[2];
	int		tick;

	if (game->light.level <= WAND_TIP_GLOW_MIN)
		return ;
	frame = &game->wand.frame[game->wand.frame_id];
	if (!frame->img || !frame->addr)
		return ;
	if (!get_spark_anchor(game->wand.frame_id, anchor))
		return ;
	size[0] = frame->width * WAND_SCALE;
	size[1] = frame->height * WAND_SCALE;
	pos[0] = (WIN_W - size[0]) / 2 + WAND_X_OFFSET
		+ (int)game->wand.bob_x;
	pos[1] = WIN_H - size[1] - WAND_BOTTOM_MARGIN
		+ WAND_Y_OFFSET + (int)game->wand.bob_y;
	tick = game->wand.anim_tick / WAND_SPARKLE_TICKS;
	draw_spark_pattern(game, pos, anchor, tick);
}
