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

static int	apply_ambient(int color, float ambient)
{
	int	r;
	int	g;
	int	b;

	r = (int)(((color >> 16) & 255) * ambient);
	g = (int)(((color >> 8) & 255) * ambient);
	b = (int)((color & 255) * ambient);
	return (rgb_to_int(light_clamp_channel(r), light_clamp_channel(g),
			light_clamp_channel(b)));
}

static void	set_light_falloff(t_game *game)
{
	int		y;
	float	screen_falloff;
	float	center_y;

	center_y = (float)WIN_H * WAND_LIGHT_CENTER_Y;
	y = 0;
	while (y < WIN_H)
	{
		screen_falloff = fabsf((float)y - center_y);
		screen_falloff = 1.0f - screen_falloff
			/ ((float)WIN_H * WAND_LIGHT_SCREEN_RANGE);
		game->light.screen_falloff[y] = light_clamp_float(screen_falloff,
				0.0f, 1.0f);
		y++;
	}
}

void	prepare_wand_light(t_game *game)
{
	float	light;

	light = light_clamp_float(wand_state_light(game), 0.0f, 1.0f);
	game->light.level = light;
	game->light.fog_dist = RENDER_DARK_FOG_DIST
		+ (RENDER_LIT_FOG_DIST - RENDER_DARK_FOG_DIST) * light;
	game->light.ambient = WAND_DARK_AMBIENT
		+ (WAND_LIT_AMBIENT - WAND_DARK_AMBIENT) * light;
	game->light.sky_power = light * WAND_SKY_POWER;
	if (light > WAND_LIGHT_MIN)
		set_light_falloff(game);
}

int	apply_wand_fog(t_game *game, int color, float distance, int y)
{
	float	dist_falloff;
	float	power;

	color = apply_fog(color, distance, game->light.fog_dist);
	color = apply_ambient(color, game->light.ambient);
	if (game->light.level <= WAND_LIGHT_MIN)
		return (color);
	dist_falloff = 1.0f - distance / WAND_LIGHT_RANGE;
	dist_falloff = light_clamp_float(dist_falloff, 0.0f, 1.0f);
	if (dist_falloff <= 0.0f)
		return (color);
	dist_falloff = dist_falloff * dist_falloff;
	power = game->light.level * dist_falloff
		* game->light.screen_falloff[y] * WAND_LIGHT_POWER;
	return (add_warm_light(color, power));
}

int	apply_wand_sky(t_game *game, int color, int y)
{
	float	power;
	float	lift;

	color = apply_ambient(color, game->light.ambient);
	if (game->light.level <= WAND_LIGHT_MIN)
		return (color);
	lift = (float)y / ((float)WIN_H * 0.5f);
	lift = light_clamp_float(lift, 0.0f, 1.0f);
	power = game->light.sky_power * lift;
	return (add_warm_light(color, power));
}
