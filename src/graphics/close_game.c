/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 01:33:05 by adavitas          #+#    #+#             */
/*   Updated: 2026/03/02 14:56:29 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

/*
** close_game — hooked to the window's red-X button (event 17)
** and optionally to the ESC key.
** Destroys all MLX resources in reverse order of creation,
** frees parsed game data, then exits cleanly.
*/
int	close_game(t_game *game)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (game->tex[i].img)
			mlx_destroy_image(game->mlx, game->tex[i].img);
		i++;
	}
	if (game->screen.img)
		mlx_destroy_image(game->mlx, game->screen.img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	free_game(game);
	exit(0);
}
