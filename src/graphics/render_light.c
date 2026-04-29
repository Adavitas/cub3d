/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 12:00:00 by adavitas          #+#    #+#             */
/*   Updated: 2026/04/29 12:00:00 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static float	wand_light_power(t_game *game, float distance, int y)
{
	float	dist_falloff;
	float	screen_falloff;
	float	center_y;

	dist_falloff = 1.0f - distance / WAND_LIGHT_RANGE;
	dist_falloff = light_clamp_float(dist_falloff, 0.0f, 1.0f);
	dist_falloff = dist_falloff * dist_falloff;
	center_y = (float)WIN_H * WAND_LIGHT_CENTER_Y;
	screen_falloff = fabsf((float)y - center_y);
	screen_falloff = 1.0f - screen_falloff
		/ ((float)WIN_H * WAND_LIGHT_SCREEN_RANGE);
	screen_falloff = light_clamp_float(screen_falloff, 0.0f, 1.0f);
	return (wand_state_light(game) * dist_falloff
		* screen_falloff * WAND_LIGHT_POWER);
}

int	apply_wand_fog(t_game *game, int color, float distance, int y)
{
	color = apply_fog(color, distance, RENDER_FOG_DIST);
	return (add_warm_light(color, wand_light_power(game, distance, y)));
}

int	apply_wand_sky(t_game *game, int color, int y)
{
	float	power;
	float	lift;

	lift = (float)y / ((float)WIN_H * 0.5f);
	lift = light_clamp_float(lift, 0.0f, 1.0f);
	power = wand_state_light(game) * lift * WAND_SKY_POWER;
	return (add_warm_light(color, power));
}
