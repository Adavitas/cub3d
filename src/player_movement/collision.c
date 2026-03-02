/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 18:06:40 by zzhyrgal          #+#    #+#             */
/*   Updated: 2026/03/02 04:28:13 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int check_collusion(float new_x, float new_y, t_game *game)
{
    if(new_x < 0 || new_y < 0
        || new_y >= game->map.height
        || new_x >= game->map.raw_max_width)
            return(1);
    if(game->map.grid[(int)new_y][(int)new_x] == '1')
        return(1);
    return(0);
}
