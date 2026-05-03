/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wand_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 18:30:00 by adavitas          #+#    #+#             */
/*   Updated: 2026/04/30 18:30:00 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static float	abs_float(float value)
{
	if (value < 0.0f)
		return (-value);
	return (value);
}

static float	get_light_target(t_wand_state state)
{
	if (state == WAND_ON || state == WAND_TURNING_ON)
		return (1.0f);
	return (0.0f);
}

static void	update_sparkle_tick(t_game *game)
{
	if (game->wand.state == WAND_OFF && game->wand.light_level <= 0.0f)
	{
		game->wand.sparkle_tick = 0;
		return ;
	}
	game->wand.sparkle_tick++;
	if (game->wand.sparkle_tick > 100000)
		game->wand.sparkle_tick = 0;
}

static void	approach_wand_light(t_wand *wand, float target)
{
	float	delta;
	float	gain;

	delta = target - wand->light_level;
	gain = WAND_LIGHT_OFF_GAIN;
	if (target > 0.0f)
		gain = WAND_LIGHT_ON_GAIN;
	if (abs_float(delta) <= WAND_LIGHT_SNAP)
		wand->light_level = target;
	else
		wand->light_level += delta * gain;
	wand->light_level = light_clamp_float(wand->light_level, 0.0f, 1.0f);
}

void	update_wand_light(t_game *game)
{
	float	target;

	update_sparkle_tick(game);
	target = get_light_target(game->wand.state);
	approach_wand_light(&game->wand, target);
}
