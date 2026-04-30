/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_light_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 12:00:00 by adavitas          #+#    #+#             */
/*   Updated: 2026/04/29 12:00:00 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	light_clamp_channel(int value)
{
	if (value < 0)
		return (0);
	if (value > 255)
		return (255);
	return (value);
}

float	light_clamp_float(float value, float min, float max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

float	wand_state_light(t_game *game)
{
	return (light_clamp_float(game->wand.light_level, 0.0f, 1.0f));
}

int	add_warm_light(int color, float power)
{
	int	r;
	int	g;
	int	b;

	if (power <= 0.0f)
		return (color);
	r = ((color >> 16) & 255) + (int)(WAND_LIGHT_R * power);
	g = ((color >> 8) & 255) + (int)(WAND_LIGHT_G * power);
	b = (color & 255) + (int)(WAND_LIGHT_B * power);
	return (rgb_to_int(light_clamp_channel(r), light_clamp_channel(g),
			light_clamp_channel(b)));
}
