/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzhyrgal <zzhyrgal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 13:06:30 by zzhyrgal          #+#    #+#             */
/*   Updated: 2026/03/10 16:10:22 by zzhyrgal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	set_up_dir_plane(t_player *player)
{
	if (player->p_orientation == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
	}
	else if (player->p_orientation == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
	}
	else if (player->p_orientation == 'E')
	{
		player->dir_x = 1;
		player->dir_y = 0;
	}
	else if (player->p_orientation == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
	}
	player->plane_x = -player->dir_y * 0.66;
	player->plane_y = player->dir_x * 0.66;
}
