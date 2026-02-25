/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzhyrgal <zzhyrgal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 17:34:26 by zzhyrgal          #+#    #+#             */
/*   Updated: 2026/02/22 21:19:10 by zzhyrgal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

// Extract texture path from line: "NO ./path/to/texture.xpm"

static char *extract_path(char *line)
{
    char *path;
    char *trimmed;
    int i;
    
    if(!line)
        return(NULL);
    i = 0;
    while(line[i] && !isspace(line[i]))
        i++;
    while(line[i] && isspace(line[i]))
        i++;
    path = &line[i];
    if(!path || *path == '\0')
        return(NULL);
    trimmed = trim_white_spaces(path);
    if(!trimmed || *trimmed == '\0')
        return(NULL);
    if(check_spaces_path(trimmed))
        return(NULL);
    if(extension_check(trimmed))
        return(NULL);
    return(ft_strdup(trimmed));
}

int parse_texture(char *line, t_tex *tex, t_text_id tex_id) //tex_id?
{
    if(tex->is_set)
    {
        printf("Duplicate texture: '%d'\n", tex_id);
        return(1);
    }
    
    tex->path = extract_path(line);
    if(!tex->path)
    {
        printf("Path extraction failed.\n");
        return(1);
    }
    tex->is_set = true;
    return(0);
}
