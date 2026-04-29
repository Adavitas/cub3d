/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_cleanup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 12:00:00 by adavitas          #+#    #+#             */
/*   Updated: 2026/04/29 12:00:00 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	destroy_world_images(t_game *game)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		if (game->tex[i].img)
		{
			mlx_destroy_image(game->mlx, game->tex[i].img);
			game->tex[i].img = NULL;
		}
		i++;
	}
}

void	destroy_mlx_resources(t_game *game)
{
	if (!game->mlx)
		return ;
	destroy_world_images(game);
	destroy_wand_images(game);
	if (game->screen.img)
	{
		mlx_destroy_image(game->mlx, game->screen.img);
		game->screen.img = NULL;
	}
	if (game->win)
	{
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	game->mlx = NULL;
}

int	fail_mlx_init(t_game *game)
{
	destroy_mlx_resources(game);
	return (0);
}
