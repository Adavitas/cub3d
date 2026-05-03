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
	if (level < 0.35f)
		return (2);
	if (level < 0.60f)
		return (4);
	if (level < 0.85f)
		return (5);
	return (WAND_SPARKLE_COUNT);
}

void	set_wand_spark(int *spark, int id, int pattern, int *tip)
{
	spark[0] = tip[0] - 8 + (id % 3) * 8;
	spark[1] = tip[1] - 7 + (id / 3) * 8;
	spark[2] = 1;
	spark[3] = 0x00FFF3A0;
	if (id == 0)
		spark[2] = WAND_SPARKLE_RADIUS;
	if (id == 3 || id == 4)
		spark[2] = 0;
	if (id == 2 || id == 3)
		spark[3] = 0x00FFD45A;
	if (id == 0 || id == 5)
		spark[3] = 0x00FFFFFF;
	if (pattern == 1 && id % 2 == 0)
		spark[0] += 1;
	else if (pattern == 1)
		spark[1] -= 1;
	else if (pattern == 2 && id < 3)
		spark[1] += 1;
	else if (pattern == 2)
		spark[0] -= 1;
	if ((id == 4 && pattern == 1) || (id == 3 && pattern == 2))
		spark[2] = 1;
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
	int		rgb[3];
	int		i;
	int		color;
	float	power;

	power = 0.35f + light_clamp_float(game->light.level, 0.0f, 1.0f)
		* 0.65f;
	rgb[0] = (int)(((spark[3] >> 16) & 255) * power);
	rgb[1] = (int)(((spark[3] >> 8) & 255) * power);
	rgb[2] = (int)((spark[3] & 255) * power);
	color = rgb_to_int(light_clamp_channel(rgb[0]),
			light_clamp_channel(rgb[1]), light_clamp_channel(rgb[2]));
	i = -spark[2];
	while (i <= spark[2])
	{
		put_spark_pixel(game, spark[0] + i, spark[1], color);
		put_spark_pixel(game, spark[0], spark[1] + i, color);
		i++;
	}
}
