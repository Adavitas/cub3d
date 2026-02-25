/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzhyrgal <zzhyrgal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 17:33:13 by zzhyrgal          #+#    #+#             */
/*   Updated: 2026/02/22 20:44:56 by zzhyrgal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"//!t_game GAME is created on STACK!

//Double free: if one of the helper functions alaready
//frees internal members and set pointers to NULL - thats good;
//but if they don't set to NULL and cleanup runs TWICE ->twice

/*free in reverse order of allocation*/
/*destroy->mlx images->window->textures->map.grid->remaining*/
void free_game(t_game *game)
{
    if(!game)
        return;
    //mlxes;
    //windows;
    free_tex(game->tex);
    free_map(&game->map);
    // player has no dynamic memory - nothing to free
    // game itself is on stack - never free it
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

// Free texture paths - tex is an array of 4 structs, not pointers
void free_tex(t_tex *tex)
{
    int i;

    i = 0;
    while(i < 4)
    {
        if(tex[i].path != NULL)
        {
            free(tex[i].path);
            tex[i].path = NULL;
        }
        // Graphics part (img, addr) will be freed by Leqso's cleanup
        i++;
    }
}
void free_list_maplines(t_node **head)
{
    t_node *temp;
    
    if(!head || !(*head))
        return;
    while(*head)
    {
        temp = *head;
        *head = (*head)->next;
        free(temp->line);
        free(temp);
    }
    *head = NULL;
}

//Leqso needs to write his frees;