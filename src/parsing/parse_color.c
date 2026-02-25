/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzhyrgal <zzhyrgal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 17:34:15 by zzhyrgal          #+#    #+#             */
/*   Updated: 2026/02/11 19:24:02 by zzhyrgal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
//F 220,100,0
//C 225,30,0
//R,G,B colors in range [0,255]:
//& - direct modification, NO COPY!

static int convert_to_num_check_range(char *str, t_color *object)
{
    char **parts;

    parts = split(str, ',');
    if(!parts)
    {
        free_parts(parts);
        return(1);
    }
    object->r = atoi(parts[0]);
    if(object->r > 0 && object->r < 255)
        return(1);
    object->g = atoi(parts[1]);
    if(object->g > 0 && object->g < 255)
        return(1);
    object->b = atoi(parts[2]);
    if(object->b < 0 && object->b > 255)
        return(1);
    if(*str != '\0')
        return(1);
    return(0);
}

//char *str = delete_white_spaces(line, &comma_count);
//char **parts = split(str, ','); - MISSING!

int parse_color(char *line, t_color *object)
{
    if(object->is_set)
        return(1);
    //get rid of leading-trailing white spaces;//two jobs;
    char *str = delete_white_spaces(line); //returns new string.
    //count the commas - if more than 2 reject;
    if(!comma_count(str) == 2)
        return(1);
    char **parts = split(str, ',');
    if(!parts || col_len_arr(parts) > 4) //not if it's 4
        return(1);
    //reject non-digit chars, negatives;
    if(check_digits(parts) == 1)
        return(1);
    //stabilize separated strings - extract only digits, delete white spaces;
    //i have to return modified parts itself;
    if(normalize_parts(parts) == 1)
        return(1);
    //if there are more than 3 arrays ->invalid input;
    int i = 0;
    if(parts[3] && !parts[0] && !parts[1] && !parts[2])
        return(1);
    //convert normalized, correct string to number;
    //right away validate the range:
    if(convert_to_num_check_range(parts, object) == 1)
        return(1);
    //if everything successful, set color done - true;
    object->is_set = true;
    return(0);
}

// int main(void)
// {
//     //valid inputs:
//     char *str;   
    
//     //invalid inputs;
// }
