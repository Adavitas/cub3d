/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 17:07:44 by zzhyrgal          #+#    #+#             */
/*   Updated: 2026/03/10 02:08:34 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

// int check_digits(char **parts)
// {
//     int i = 0;
//     int j;

//     while(parts[i])
//     {
//         j = 0;
//         while(parts[i][j])
//         {
//             if(parts[i][j] >= '0' && parts[i][j] <= '9') 
//                 j++;
//             else
//                 return(1);
//         }
//         i++;
//     }
//     return(0);
// }

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
        if(!isdigit((unsigned char)parts[start]))
            return(1);
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
        valid = shift_memory(parts[i], start, end);
        if(valid == 1)
            return(1);
        i++;
   }
   return(0);
}
