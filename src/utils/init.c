/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 16:21:40 by zzhyrgal          #+#    #+#             */
/*   Updated: 2026/03/10 00:37:46 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	initialize_player(t_player *player)
{
	player->player_count = 0;
	player->x = 0.0f;
	player->y = 0.0f;
	player->dir_x = 0.0f;
	player->dir_y = 0.0f;
	player->plane_x = 0.0f;
	player->plane_y = 0.0f;
	player->p_orientation = '\0';
}

void	init_game(t_game *game)
{
	ft_bzero(game, sizeof(t_game));
}
