/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzhyrgal <zzhyrgal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 21:01:21 by zzhyrgal          #+#    #+#             */
/*   Updated: 2026/02/22 21:33:17 by zzhyrgal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
//check all textures are provided:all identifier's are unique;
//check for all colors: no duplicates;
//map validity:?
    //map must be fully enclosed by walls;
    //check that only valid chars exist;
    //player: exactly one player;
//check for unreachable areas?
    //flood-fill or BFS?! - is it in the conditions;
//MAP DIMENSIONS?!!!

//flood_fill validates walls and spaces inside the map!
        //if i start from inside map - can i reach outside: yes or no?
//can i escape the map?

//player's count is already validated during parsing;

int validate_chars(t_map *map)
{
    int i;
    int j;

    i = 0;
    while(map->grid[i])
    {
        j = 0;
        while(map->grid[i][j])
        {
            // Player characters are replaced with '0' during parsing
            if(map->grid[i][j] != '0' && map->grid[i][j] != '1'
            && map->grid[i][j] != ' ' && map->grid[i][j] != '\t')
            {
                printf("Invalid character in map: '%c'\n", map->grid[i][j]);
                return(1);
            }
            j++;
        }
        i++;
    }
    return(0);
}

// int validate_tex_colors(t_game *game)
// {
//     if(!game->floor.is_set || !game->ceiling.is_set)
//     {
//         printf("validation stage: floor or ceiling not passed.\n");
//         return(1);
//     }
//     if(!game->tex[TEX_NO].is_set
//         || !game->tex[TEX_SO].is_set
//         || !game->tex[TEX_WE].is_set
//         || !game->tex[TEX_EA].is_set)
//         {
//             printf("validation stage: texture not passed.\n");
//             return(1);
//         }
//     return(0);
// }
//NO SPACE inside the map -> already checked by the valid_map function;

int validate_player(t_game *game)
{
    int row_len;
    int row;
    int col;
    
    // if(game->player.player_count != 1)->this is done in parse_map;
    // {
    //     printf("validation stage: player count did not pass.\n");
    //     return(1);
    // }
    row = (int)game->player.y; // y is row
    col = (int)game->player.x; // x is column
    if (row < 0 || col < 0 || row >= game->map.height)
        return (1);
    row_len = strlen(game->map.grid[row]);
    if (col >= row_len)
        return (1);
    return(0);
}

int post_validation(t_game *game)
{
    if(validate_chars(&game->map))
    {
        printf("validation did not pass, unknown token.\n");
        return(1);
    }
    if(validate_player(game))
        return(1);
    if(validate_map(game))//it should be an algo function
    {
        printf("not enclosed with walls.\ncheck_walls.\n");
        return(1);
    }
    return(0);
}

//FLOAT!???? -short way to do it????//