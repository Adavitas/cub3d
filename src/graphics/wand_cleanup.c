/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wand_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 12:00:00 by adavitas          #+#    #+#             */
/*   Updated: 2026/04/29 12:00:00 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	destroy_wand_images(t_game *game)
{
	int	i;

	i = 0;
	while (i < WAND_FRAME_COUNT)
	{
		if (game->wand.frame[i].img)
		{
			mlx_destroy_image(game->mlx, game->wand.frame[i].img);
			game->wand.frame[i].img = NULL;
		}
		i++;
	}
}

void	free_wand(t_wand *wand)
{
	int	i;

	i = 0;
	while (i < WAND_FRAME_COUNT)
	{
		if (wand->frame[i].path)
		{
			free(wand->frame[i].path);
			wand->frame[i].path = NULL;
		}
		i++;
	}
}
