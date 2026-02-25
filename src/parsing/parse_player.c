/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzhyrgal <zzhyrgal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 13:06:30 by zzhyrgal          #+#    #+#             */
/*   Updated: 2026/02/22 21:33:17 by zzhyrgal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
//length = √(dir_x² + dir_y²) = 1 -> They represent the direction the player is facing in the 2D world.

//               (0, -1)
//                  N
//                  ↑
//                  |
// (-1, 0)  W  ← ---+--- →  E  (1, 0)
//                  |
//                  ↓
//                  S
//               (0, 1)

void set_up_dir_plane(t_player *player)
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

    // Setup camera plane (FOV ≈ 66°)
    player->plane_x = -player->dir_y * 0.66;
    player->plane_y = player->dir_x * 0.66;
}
