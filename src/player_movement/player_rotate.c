/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzhyrgal <zzhyrgal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 18:06:45 by zzhyrgal          #+#    #+#             */
/*   Updated: 2026/02/22 21:56:03 by zzhyrgal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void rotate_left(t_game *game)
{
    float old_dir_x;
    float old_plane_x;
    float rot;

    rot = ROTATE_SPEED;
    old_dir_x = game->player.dir_x;
    old_plane_x = game->player.plane_x;

    game->player.dir_x = game->player.dir_x * cos(rot)
            - game->player.dir_y * sin(rot);
    game->player.dir_y = old_dir_x * sin(rot)
            + game->player.dir_y * cos(rot);
    
    game->player.plane_x = game->player.plane_x * cos(rot)
            - game->player.plane_y * sin(rot);
    game->player.plane_y = old_plane_x * sin(rot)
            + game->player.plane_y * cos(rot);
}

void rotate_right(t_game *game)
{
    float old_dir_x;
    float old_plane_x;
    float rot;

    rot = -ROTATE_SPEED;
    old_dir_x = game->player.dir_x;
    old_plane_x = game->player.plane_x;

    game->player.dir_x = game->player.dir_x * cos(rot)
            - game->player.dir_y * sin(rot);
    game->player.dir_y = old_dir_x * sin(rot)
            + game->player.dir_y * cos(rot);
    //camera plane
    game->player.plane_x = game->player.plane_x * cos(rot)
            - game->player.plane_y * sin(rot);
    game->player.plane_y = old_plane_x * sin(rot)
            + game->player.plane_y * cos(rot);
}
