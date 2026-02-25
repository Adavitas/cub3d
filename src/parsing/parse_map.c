/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzhyrgal <zzhyrgal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 17:02:23 by zzhyrgal          #+#    #+#             */
/*   Updated: 2026/02/10 16:49:40 by zzhyrgal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
//.cub file has 2 info:
    //Configuration: wall, floor color, ceiling color;
    //the map: 2d layout of walls, spaces, player.
//0 -> space, 1 -> wall:

int valid_map(char *line)
{
    int i = 0;
    
    while(line[i])
    {
        while(isspace(line[i]))
            i++;
        if(line[i] == 1 || line[i] == 0
            || line[i] == 'N'|| line[i] == 'W',
                        line[i] == 'S', line[i] == 'E')
                        i++;

        else
            return(1);
    }
    return(0);
}

int parse_map(char *line, t_game *game)
{
    int i = 0;
    
    while(line[i])
    {
        //should i store spaces into a map?
        game->map.grid[i] = line[i];
        if(line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
            game->player.init_player = 1;//keep track of player num;
        i++;
    }
    game->map.height++;
    if(i > game->map.width)
        game->map.width = i;
    return(0);
}

// int main(void)
// {
    
// }