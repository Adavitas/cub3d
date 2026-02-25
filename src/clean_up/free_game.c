/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzhyrgal <zzhyrgal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 17:33:13 by zzhyrgal          #+#    #+#             */
/*   Updated: 2026/02/14 18:46:43 by zzhyrgal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"//!t_game GAME is created on STACK!

//Double free: if one of the helper functions alaready
//frees internal members and set pointers to NULL - thats good;
//but if they don't set to NULL and cleanup runs TWICE ->twice
//Only internal allocations are freed.

/*free in reverse order of allocation*/
/*destroy->mlx images->window->textures->map.grid->remaining*/
void free_game(t_game *game)
{
    if(!game)
        return;
    //mlxes;
    //windows; // free_tex(&(*game)->tex); i want to know the diff;
    free_tex(game->tex);
    free_map(&game->map);
    free_player(&game->player);
    // free(game);If t_game game; was declared 
    //on stack → ❌ NEVER free it.
    // free(*game); because it is not dynamically allocated;
    // *game = NULL;
}

void free_map(t_map *map)
{
    int i;

    if(!map || !map->grid)
        return;
    if(map->grid)
    {
        i = 0;
        while(i < map->height)
        {
            free(map->grid[i]);
            i++;
        }
        free(map->grid);
        map->grid = NULL;
    }
}

// void free_colors(t_color *object); not allocated by dynamically

void free_tex(t_tex *tex[])
{
    //Leqso's part needs to be tracked and freed;
    //my part is only *path as of now;
    //i have array of textures;
    int index;
    index = 0;
    int i;
    //access the path?
    while(tex[index])
    {
        i = 0;
        if(tex[index]->path[i] != NULL)
            free(tex[index]->path[i++]);
        free(tex[index]->path);
        index++;
    }
}

void free_player(t_player *player);

//Leqso needs to write his frees;