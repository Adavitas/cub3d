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

void	update_wand_light(t_game *game)
{
	float	target;
	float	step;

	target = 0.0f;
	if (game->wand.state == WAND_ON
		|| game->wand.state == WAND_TURNING_ON)
		target = 1.0f;
	step = 1.0f / ((float)WAND_TURN_TICKS * 3.0f);
	if (game->wand.light_level < target)
	{
		game->wand.light_level += step;
		if (game->wand.light_level > target)
			game->wand.light_level = target;
	}
	else if (game->wand.light_level > target)
	{
		game->wand.light_level -= step;
		if (game->wand.light_level < target)
			game->wand.light_level = target;
	}
}
