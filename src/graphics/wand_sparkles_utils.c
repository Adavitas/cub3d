/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wand_sparkles_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 18:00:00 by adavitas          #+#    #+#             */
/*   Updated: 2026/05/03 18:00:00 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	get_wand_spark_anchor(int frame_id, int *anchor)
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

int	get_wand_spark_limit(float level)
{
	if (level <= WAND_TIP_GLOW_MIN)
		return (0);
	if (level < 0.14f)
		return (4);
	if (level < 0.35f)
		return (6);
	if (level < 0.70f)
		return (8);
	return (WAND_SPARKLE_COUNT);
}

void	set_wand_spark(int *spark, int id, int pattern, int *tip)
{
	static const int	offset[3][9][2] = {
	{{-22, -26}, {18, -20}, {0, -34}, {-30, -4}, {28, 4},
	{-8, 12}, {12, -8}, {34, -28}, {4, -14}},
	{{24, -28}, {-20, -18}, {4, -38}, {32, -2}, {-32, 6},
	{0, 14}, {-10, -6}, {16, -16}, {30, -34}},
	{{0, -32}, {-28, -8}, {30, -12}, {10, 12}, {-14, -28},
	{22, -34}, {-34, -24}, {36, 8}, {-4, -4}}
	};
	static const int	radius[3][9] = {
	{WAND_SPARKLE_RADIUS, 2, 0, 0, 2, 0, 1, 0, 1},
	{WAND_SPARKLE_RADIUS, 2, 0, 0, 2, 0, 1, 0, -1},
	{WAND_SPARKLE_RADIUS, 2, 2, 0, 2, 0, 1, 0, 1}
	};
	static const int	color[9] = {
		0x00FFFFFF, 0x00FFD45A, 0x00FFF3A0, 0x00FFB83D,
		0x00FFF3A0, 0x00FFF3A0, 0x00FFFFFF, 0x00FFD45A,
		0x00FFFFFF
	};

	if (pattern < 0 || pattern > 2)
		pattern = 0;
	spark[0] = tip[0] + offset[pattern][id][0];
	spark[1] = tip[1] + offset[pattern][id][1];
	spark[2] = radius[pattern][id];
	spark[3] = color[id];
}

static void	put_spark_pixel(t_game *game, int x, int y, int color)
{
	int	stride;

	if (x < 0 || y < 0 || x >= WIN_W || y >= WIN_H)
		return ;
	stride = game->screen.line_len / 4;
	game->screen.addr[y * stride + x] = color;
}

void	draw_wand_spark_cross(t_game *game, int *spark)
{
	int		i;
	int		color;
	float	power;

	if (spark[2] < 0)
		return ;
	power = 0.65f + light_clamp_float(game->light.level, 0.0f, 1.0f)
		* 0.35f;
	color = rgb_to_int(
			light_clamp_channel((int)(((spark[3] >> 16) & 255) * power)),
			light_clamp_channel((int)(((spark[3] >> 8) & 255) * power)),
			light_clamp_channel((int)((spark[3] & 255) * power)));
	i = -spark[2];
	while (i <= spark[2])
	{
		put_spark_pixel(game, spark[0] + i, spark[1], color);
		put_spark_pixel(game, spark[0], spark[1] - i, color);
		i++;
	}
}
