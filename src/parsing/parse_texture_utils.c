/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzhyrgal <zzhyrgal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 18:47:31 by zzhyrgal          #+#    #+#             */
/*   Updated: 2026/02/22 21:02:32 by zzhyrgal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
//all three(line, start, end point to the same memory place)
char *trim_white_spaces(char *line)
{
    char *start;
    char *end;

    if(!line)
        return(NULL);
    while(*line && isspace(*line))
        line++;
    if(*line == '\0')
        return(line);
    start = line;
    end = line;
    while(*end)
        end++;
    end--;//last char;
    while(end > start && isspace(*end))
        end--;
    *(end + 1) = '\0';//modifies the actual memory of the string line.
    return (start);
}
int check_spaces_path(char *path)
{
    int i;

    if(!path)
        return(1);
    i = 0;
    while(path[i])
    {
        if(isspace(path[i]))
            return(1);
        i++;
    }
    if(path[i] == '\0')
        return(0);
    return(1);
}
//no case sensisivity check;
int extension_check(char *path)
{
    int i;

    if(!path)
        return(1);
    i = 0;
    while(path[i])
        i++;
    if(i < 4)
        return(1); //reject if there are not a valid file;
    if(path[i-4] == '.' &&
        path[i-3] == 'x' &&
        path[i-2] == 'p' &&
        path[i-1] == 'm')
            return(0);
    return(1);
}
