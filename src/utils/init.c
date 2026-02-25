/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 16:21:40 by zzhyrgal          #+#    #+#             */
/*   Updated: 2026/02/25 19:01:07 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
//bzero only modifies already-existing memory;
//A pointer with all bits set to zero is guaranteed 
                            //to be a NULL pointer.
//Uninitialized memory contains garbage.

// memset zeroes every byte → all pointers become NULL, all ints 0,
// all bools false. No need to set fields individually afterwards.
// Answering your question: setting a freed pointer to NULL before a
// second free() call IS safe — free(NULL) is a no-op by the C standard.

void    init_player(t_game *game)
{
    t_player    *p;

    p = &game->player;

    // Center of tile: tile index 0 occupies [0.0, 1.0], so center is 0.5
    p->pos_x = p->x + 0.5;
    p->pos_y = p->y + 0.5;

    if (p->dir == 'N')
    {
        p->dir_x = 0;    p->dir_y = -1;
        p->plane_x = 0.66; p->plane_y = 0;
    }
    else if (p->dir == 'S')
    {
        p->dir_x = 0;    p->dir_y = 1;
        p->plane_x = -0.66; p->plane_y = 0;
    }
    else if (p->dir == 'E')
    {
        p->dir_x = 1;    p->dir_y = 0;
        p->plane_x = 0;  p->plane_y = 0.66;
    }
    else if (p->dir == 'W')
    {
        p->dir_x = -1;   p->dir_y = 0;
        p->plane_x = 0;  p->plane_y = -0.66;
    }
}

void init_game(t_game *game)
{
    memset(game, 0, sizeof(t_game));
}