/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzhyrgal <zzhyrgal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 15:31:30 by zzhyrgal          #+#    #+#             */
/*   Updated: 2026/02/22 15:33:56 by zzhyrgal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

char *delete_white_spaces(char *line)
{
    char *new_str;
    int i = 0;
    int start = 0;
    int end = 0;
    int new_size;
    
    if(!line)
        return (NULL);
    while(line[i] && isspace(line[i]))
        i++;
    start = i;
    if(line[start] == '\0')
        return(strdup(""));
    i = strlen(line) - 1;
    while(line[i] && isspace(line[i]))
        i--;
    end = i;
    new_size = end - start + 1;
    new_str = malloc(sizeof(char) * (new_size + 1));
    if(!new_str)
        return(NULL);
    int j = 0;
    while(j < new_size)
    {
        new_str[j] = line[start];
        start++;
        j++;
    }
    new_str[j] = '\0';
    return(new_str);
}

int comma_count(const char *str)
{
    int i = 0;
    int comma_count = 0;

    if(!str)
        return(1);

    while(str[i])
    {
        if(str[i] == ',')
            comma_count++;
        i++;
    }
    return(comma_count);
}

int col_len_arr(char **parts)
{
    int i;

    i = 0;
    while(parts[i])
        i++;
    return(i);
}

int checking_functions(char **parts)
{
    if(!parts || col_len_arr(parts) != 3)  // MISSING FUNCTION: col_len_arr
        return(1);
    if(normalize_parts(parts) == 1)
        return(1);
    // if(check_digits(parts) == 1)
    //     return(1);
    return(0);
}
