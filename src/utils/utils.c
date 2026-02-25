/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzhyrgal <zzhyrgal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 16:38:28 by zzhyrgal          #+#    #+#             */
/*   Updated: 2026/02/22 21:45:02 by zzhyrgal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int cub_file_check(char *filename)
{
    int len;

    if(!filename)
        return(0);
    len = strlen(filename);
    if(len <= 4)
        return(0);
    if(filename[len - 4] == '.'
        && filename[len - 3] == 'c'
        && filename[len - 2] == 'u'
        && filename[len - 1] == 'b')
            return(1);
    return(0);
}

void ft_bzero(void *s, size_t n)
{
    unsigned char *p = s;
    while(n--)
        *p++ = 0;
}

int ft_isspace(char c)
{
    if(c == ' ' || c == '\t')
        return(0);
    return(1);
}

// Check if line contains only whitespace or is empty
int is_empty(char *line)
{
    int i;
    
    if (!line)
        return (1);
    i = 0;
    while (line[i])
    {
        if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n' && line[i] != '\r')
            return (0);
        i++;
    }
    return (1);
}

// //forgot why?
// int convert_tabs_tospaces(t_node *node);