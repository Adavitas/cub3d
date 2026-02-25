/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzhyrgal <zzhyrgal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 17:07:44 by zzhyrgal          #+#    #+#             */
/*   Updated: 2026/02/11 19:29:03 by zzhyrgal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

char *delete_white_spaces(char *line, int *comma_count)
{
    char *new_str;
    int i = 0;
    if(!line)
        return(1);
    int start = 0;
    int end = 0;
    
    while(isspace(line[i]))
        i++;
    start = i;
    while(line[i] != '\0')
        i++;
    if(isspace(line[i]))
    {
        while(isspace(line[i]))
            i--;
        if(line[i] && !isspace(line[i]))
            end = i;
    }
    int new_size = start - end;//or use strlen() instead?
    new_str = malloc(new_size + 1);
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

int check_digits(const char **parts)
{
    int i = 0;
    int j;

    while(parts[i])
    {
        j = 0;
        while(parts[i][j])
        {
            if((parts[i][j] >= '0' && parts[i][j] <= '9') 
                        || isspace(parts[i][j]) || parts[i][j] == ',')
                j++;
            else
                return(1);
        }
        i++;
    }
    return(0);
}


//After trimming + shifting, memory becomes:
//parts[0] = '2       75';//invalid input - reject;
//parts[1] = '   100   ';//delete leading and trailing white spaces;
//parts[2] = '0    ';//delete trailing white spaces;

int find_start(char *parts)
{
    int i;

    i = 0;
    while(isspace((unsigned char)parts[i]))
        i++;
    if(parts[i] == '\0')
        return(-1);
    return(i);
}

int find_end(char *parts)
{
    int i;
    
    i = 0;
    if(parts[0] == '\0')
        return(-1);
    while(parts[i])
        i++;
    i--;
    while(i > 0 && isspace((unsigned char)parts[i]))
        i--;
    if(i < 0)
        return(-1);
    return(i);
}

int shift_memory(char *parts, int start, int end)
{
    int i;

    i = 0;
    while(start <= end)
    {
        if(!isdigit((unsigned char)parts[i]))
            return(-1);
        parts[i] = parts[start];
        start++;
        i++;
    }
    parts[i] = '\0';
    return(0);
}

int normalize_parts(char **parts)
{
   int i;
   int start;
   int end;
   int valid;

   i = 0;
   while(parts[i])
   {
        start = find_start(parts[i]);
        if(start == -1)
            return(1);
        end = find_end(parts[i]);
        if(end == -1 || end < start)
            return(1);
        if(end < start)
            return(1);
        valid = shift_memory(parts[i], start, end);
        if(valid == 1)
            return(1);
        i++;
   }
   return(0);
}

