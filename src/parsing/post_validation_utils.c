/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_validation_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 17:43:39 by zzhyrgal          #+#    #+#             */
/*   Updated: 2026/02/25 19:27:13 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void free_map_copy(char **map, int height)
{
    int i;

    if(!map)
        return;
    i = 0;
    while(i < height)
    {
        free(map[i]);
        i++;
    }
    free(map);
}

// flood_fill: x = row index, y = column index (map[x][y])
int flood_fill(char **map_copy, int x, int y, int height)
{
    int row_len;
    //if out of bound;
    if(x < 0 || y < 0 || x >= height)
        return(1);
    row_len = strlen(map_copy[x]);
    if(y >= row_len)
        return(1);
    //if space inside a map;
    if(map_copy[x][y] == ' ' || map_copy[x][y] == '\t')
        return(1);
    //mark visited
    if(map_copy[x][y] == '1' || map_copy[x][y] == 'V')
        return(0);
        
    map_copy[x][y] = 'V';

    if(flood_fill(map_copy, x+1, y, height))
        return(1);
    if(flood_fill(map_copy, x-1, y, height))
        return(1);
    if(flood_fill(map_copy, x, y+1, height))
        return(1);
    if(flood_fill(map_copy, x, y-1, height))
        return(1);
    return(0);
}

//player's position is stored at parse_row();
char **copy_map(t_map *map)
{
    char **copy_map;
    int i;
    
    copy_map = malloc(sizeof(char *) * (map->height + 1));
    if(!copy_map)
        return(NULL);
    i = 0;
    while(i < map->height)
    {
        copy_map[i] = strdup(map->grid[i]);
        if(!copy_map)
            return(NULL);
        if(!copy_map[i])
        {
            free_map_copy(copy_map, i);
            return(NULL);
        }
        i++;
    }
    copy_map[i] = NULL;
    return(copy_map);
}

int validate_map(t_game *game)
{
    char **copy_karta;
    int result;
    int row;
    int col;
    
    copy_karta = copy_map(&game->map);
    row = (int)game->player.y; // y is row
    col = (int)game->player.x; // x is column
    result = flood_fill(copy_karta, row, col, game->map.height);
    free_map_copy(copy_karta, game->map.height);//*copy is freed here*;
    return(result);
}
