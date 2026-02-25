/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzhyrgal <zzhyrgal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 16:39:00 by zzhyrgal          #+#    #+#             */
/*   Updated: 2026/02/22 21:56:29 by zzhyrgal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int move_player(t_game *game, float newx, float newy)
{
    float new_x;
    float new_y;

    new_x = game->player.x + newx;//updating the position;
    new_y = game->player.y + newy;
    if(check_collusion(new_x, new_y, game) == 1)
        return(1);
    game->player.x = new_x;
    game->player.y = new_y;
    return(0);
}
//RADIUS added later with graphics???
