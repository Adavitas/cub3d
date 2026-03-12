/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 16:07:37 by adavitas          #+#    #+#             */
/*   Updated: 2026/03/12 20:25:03 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

/*
** Check if the player is standing inside the given door tile.
*/
static int	player_on_tile(t_game *game, int dx, int dy)
{
	if ((int)game->player.x == dx && (int)game->player.y == dy)
		return (1);
	return (0);
}

/*
** Find the door cell the player is facing and within DOOR_RANGE of.
** Will not close a door if the player is standing inside it.
*/
void	toggle_door(t_game *game)
{
	float	check[2];
	int		d[2];
	float	t;

	t = 0.0f;
	while (t < DOOR_RANGE)
	{
		t += 0.1f;
		check[0] = game->player.x + game->player.dir_x * t;
		check[1] = game->player.y + game->player.dir_y * t;
		d[0] = (int)check[0];
		d[1] = (int)check[1];
		if (d[0] < 0 || d[1] < 0 || d[1] >= game->map.height
			|| d[0] >= game->map.raw_max_width)
			return ;
		if (game->map.grid[d[1]][d[0]] == '1')
			return ;
		if (game->map.grid[d[1]][d[0]] != 'D')
			continue ;
		if (game->map.door_open[d[1]][d[0]] && player_on_tile(game, d[0], d[1]))
			return ;
		game->map.door_open[d[1]][d[0]] = !game->map.door_open[d[1]][d[0]];
		return ;
	}
}
