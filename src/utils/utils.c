/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzhyrgal <zzhyrgal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 16:38:28 by zzhyrgal          #+#    #+#             */
/*   Updated: 2026/02/08 07:56:03 by zzhyrgal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void ft_bzero(void *s, size_t n)
{
    unsigned char *p = s;
    while(n--)
        *p++ = 0;
}

int is_space(char c)
{
    if(c == ' ' || c == '\t')
        return(0);
    return(1);
}
//forgot why?
int convert_tabs_tospaces(t_map *map);