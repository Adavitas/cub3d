/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 13:15:27 by zzhyrgal          #+#    #+#             */
/*   Updated: 2026/03/01 21:18:12 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

//If a variable must survive across multiple lines → 
                            //it cannot be local.
//checking if map has started -> it is reading line by line
int order(t_game *game)
{
    if(!game->tex[TEX_NO].is_set
        || !game->tex[TEX_SO].is_set
        || !game->tex[TEX_WE].is_set
        || !game->tex[TEX_EA].is_set)
        {
            return(1);
        }
    if(!game->floor.is_set || !game->ceiling.is_set)
        return(1);
    return(0);
}

t_color_id get_color_id(char *line)
{
    int i;

    i = 0;
    while(isspace(line[i]))
        i++;
    if(line[i] == 'F' && isspace(line[i+1]))
        return(COLOR_FLOOR);
    else if(line[i] == 'C' && isspace(line[i+1]))
        return(COLOR_CEILING);
    else
        return(COLOR_UNKNOWN);
}
t_text_id get_tex_id(char *line)
{
    int i;

    i = 0;
    while(isspace(line[i]))
        i++;
    if(line[i] == 'N' && line[i+1] == 'O' && isspace(line[i+2]))
        return TEX_NO;
    if(line[i] == 'S' && line[i+1] == 'O' && isspace(line[i+2]))
        return TEX_SO;
    if(line[i] == 'W' && line[i+1] == 'E' && isspace(line[i+2]))
        return TEX_WE;
    if(line[i] == 'E' && line[i+1] == 'A' && isspace(line[i+2]))
        return TEX_EA;
    return (TEX_UNKNOWN);
}

int select_parse(char *line, t_game *game)
{
    t_text_id tex_id;
    t_color_id color_id;
    
    tex_id = get_tex_id(line);
    color_id = get_color_id(line);
    
    printf("[SELECT_PARSE] tex_id=%d, color_id=%d for line: %s", tex_id, color_id, line);
    
    if(tex_id != TEX_UNKNOWN)
        return(parse_texture(line, &game->tex[tex_id], tex_id));
    if(color_id == COLOR_FLOOR)
        return(parse_color(line, &game->floor));
    if(color_id == COLOR_CEILING)
        return(parse_color(line, &game->ceiling));
    return(1); // unknown identifier
}
