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

static int	get_wand_tip_pos(t_game *game, int *tip)
{
	t_tex	*frame;
	int		anchor[2];
	int		pos[2];
	int		size[2];

	frame = &game->wand.frame[game->wand.frame_id];
	if (!frame->img || !frame->addr)
		return (0);
	if (!get_wand_spark_anchor(game->wand.frame_id, anchor))
		return (0);
	size[0] = frame->width * WAND_SCALE;
	size[1] = frame->height * WAND_SCALE;
	pos[0] = (WIN_W - size[0]) / 2 + WAND_X_OFFSET;
	pos[1] = WIN_H - size[1] - WAND_BOTTOM_MARGIN + WAND_Y_OFFSET;
	pos[0] += (int)game->wand.bob_x;
	pos[1] += (int)game->wand.bob_y;
	tip[0] = pos[0] + anchor[0] * WAND_SCALE;
	tip[1] = pos[1] + anchor[1] * WAND_SCALE;
	return (1);
}

void	draw_wand_sparkles(t_game *game)
{
	int		tip[2];
	int		spark[4];
	int		pattern;
	int		limit;
	int		i;

	if (game->light.level <= WAND_TIP_GLOW_MIN)
		return ;
	if (!get_wand_tip_pos(game, tip))
		return ;
	pattern = (game->wand.sparkle_tick / WAND_SPARKLE_TICKS) % 3;
	limit = get_wand_spark_limit(game->light.level);
	i = 0;
	while (i < limit)
	{
		set_wand_spark(spark, i, pattern, tip);
		draw_wand_spark_cross(game, spark);
		i++;
	}
}
