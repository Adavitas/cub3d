/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzhyrgal <zzhyrgal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 16:21:40 by zzhyrgal          #+#    #+#             */
/*   Updated: 2026/02/22 21:33:17 by zzhyrgal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
//bzero only modifies already-existing memory;
//A pointer with all bits set to zero is guaranteed 
                            //to be a NULL pointer.
//Uninitialized memory contains garbage.

// Initialize all game state to safe defaults for parsing
void initialize_player(t_player *player)
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

void init_game(t_game *game)
{
    int i;
    
    ft_bzero(game, sizeof(t_game));// Zero out entire struct first
    i = 0;
    while (i < 4)// Initialize texture paths and flags
    {
        game->tex[i].path = NULL;
        game->tex[i].is_set = false;
        game->tex[i].img = NULL;
        game->tex[i].addr = NULL;
        i++;
    }
    game->floor.is_set = false;
    game->ceiling.is_set = false;
    game->map.grid = NULL;
    game->map.height = 0;
    game->map.width = 0;
    game->map.raw_max_width = 0;
    game->map_started = false;
    // Initialize graphics (Leqso's part)
    game->mlx = NULL;
    game->win = NULL;
}

// Note: ft_bzero sets all bytes to 0, which means:
// - All pointers become NULL
// - All ints become 0
// - All bools become false
// - All floats become 0.0
// The explicit initializations above are for clarity and safety    