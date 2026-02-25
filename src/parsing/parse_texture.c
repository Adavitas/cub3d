/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzhyrgal <zzhyrgal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 17:34:26 by zzhyrgal          #+#    #+#             */
/*   Updated: 2026/02/14 19:23:29 by zzhyrgal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
//type ids are case sensitive!
//problem: what is the better parameters???
static char *extract_path(char *line, t_text_id tex_id)
{
    char *path;
    
    path = line;
    while(*path && isspace(*path))
        path++;
    //skip identifier:
    switch(tex_id)
    {
        case TEX_NO:
        case TEX_SO:
        case TEX_WE:
        case TEX_EA:
            path += 2;
            break;
        default:
            return(NULL);
    }
    //white spaces after identifier:
    while(*path && isspace(*path))
        path++;
    return(strdup(path));//does norminette allow this?
}

int parse_texture(char *line, t_tex tex[], t_text_id tex_id)
{
    if(tex[tex_id].is_set)
    {
        printf("Duplicate texture: '%d\n", tex_id);
        return(1);
    }
    
    tex[tex_id].path = extract_path(line, tex_id);
    if(!tex[tex_id].path)
    {
        printf("Path extraction failed.\n");
        return(1);
    }
    tex[tex_id].is_set = true;
    return(0);
}
