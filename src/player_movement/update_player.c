/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 00:24:30 by zzhyrgal          #+#    #+#             */
/*   Updated: 2026/03/10 00:37:46 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	update_player(t_game *game)
{
	if (game->key.w)
		move_player(game, game->player.dir_x * M_SPEED,
			game->player.dir_y * M_SPEED);
	if (game->key.s)
		move_player(game, -game->player.dir_x * M_SPEED,
			-game->player.dir_y * M_SPEED);
	if (game->key.a)
		move_player(game, game->player.dir_y * M_SPEED,
			-game->player.dir_x * M_SPEED);
	if (game->key.d)
		move_player(game, -game->player.dir_y * M_SPEED,
			game->player.dir_x * M_SPEED);
	if (game->key.left)
		rotate_left(game);
	if (game->key.right)
		rotate_right(game);
}

int	key_press(int key, t_game *game)
{
	if (key == 65307)
		close_game(game);
	if (key == KEY_W)
		game->key.w = 1;
	else if (key == KEY_S)
		game->key.s = 1;
	else if (key == KEY_A)
		game->key.a = 1;
	else if (key == KEY_D)
		game->key.d = 1;
	else if (key == KEY_LEFT)
		game->key.left = 1;
	else if (key == KEY_RIGHT)
		game->key.right = 1;
	return (0);
}

int	key_release(int key, t_game *game)
{
	if (key == KEY_W)
		game->key.w = 0;
	else if (key == KEY_S)
		game->key.s = 0;
	else if (key == KEY_A)
		game->key.a = 0;
	else if (key == KEY_D)
		game->key.d = 0;
	else if (key == KEY_LEFT)
		game->key.left = 0;
	else if (key == KEY_RIGHT)
		game->key.right = 0;
	return (0);
}
