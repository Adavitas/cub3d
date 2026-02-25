/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzhyrgal <zzhyrgal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 14:07:05 by zzhyrgal          #+#    #+#             */
/*   Updated: 2026/02/08 10:12:35 by zzhyrgal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

//If a variable must survive across multiple lines → 
                            //it cannot be local.
//checking if map has started -> it is reading line by line
t_color_id get_color_id(char *line)
{
    int i;

    i = 0;
    while(is_space(line[i]))
        i++;
    if(line[i] == 'F' && is_space(line[i+1]))
        return(COLOR_FLOOR);
    else if(line[i] == 'C' && is_space(line[i+1]))
        return(COLOR_CEILING);
    else
        return(COLOR_UNKNOWN);
}
t_text_id get_tex_id(char *line)
{
    int i;

    i = 0;
    while(is_space(line[i]))
        i++;
    if(line[i] == 'N' && line[i+1] == 'O' && is_space(line[i+2]))
        return TEX_NO;
    if(line[i] == 'S' && line[i+1] == 'O' && is_space(line[i+2]))
        return TEX_SO;
    if(line[i] == 'W' && line[i+1] == 'E' && is_space(line[i+2]))
        return TEX_WE;
    if(line[i] == 'E' && line[i+1] == 'A' && is_space(line[i+2]))
        return TEX_EA;
    return (TEX_UNKNOWN);//what should be the negative outcome?
}
//serious issues!
int select_parse(char *line, t_game *game)
{
    int i;
    i = 0;
    t_text_id tex_id;
    t_color_id color_id;
    
    tex_id = get_tex_id(line);
    color_id = get_color_id(line);
    if(tex_id != TEX_UNKNOWN)
        if(parse_texture(line, game->tex[tex_id], tex_id) == 1)
            return(1);
    if(color_id == COLOR_FLOOR)
        if(parse_color(line, &game->floor) == 1)
            return(1);
    if(color_id == COLOR_CEILING)
        if(parse_color(line, &game->ceiling) == 1)
            return(1);
    return(1);
}

int dispatch_line(char *line, t_game *game)
{
    int i = 0;
    //0 - success and 1 - failure;
    while(line[i] == ' ' || line[i] == '\t')
        i++;
    if(line[i] == '\n' || line[i] == '\0')
        return(0);
    
    if(game->map_started)//if started, pre-validity is already checked.
    {
        if(parse_map(line, game))
            return(1);
        else
            return(0);
    } //map has to start last: need to add this condition;
    else if(!game->map_started && valid_map(line) && !order(game))
    {
        game->map_started = true;
        if(parse_map(line, game))
            return (1);
        return(0);
    } //need to respect the order
    else if(select_parse(&line[i], game) == 0 && order(game))
        return(0);
    else
        return (1); //unknown token;
    return(0);
}

int parse(const char *file, t_game *game)
{
    int fd;
    char *line;

    fd = open(file, O_RDONLY);
    if(fd < 0)
    {
        printf("File opening failed.\n");
        return(-1);
    }
    
    while(get_next_line(fd, &line))
    {
        if(is_empty(line))
        {
            free(line);
            continue;//from where do dispatch_line start?
        }
        if(dispatch_line(line, game) == 1)
            return(1);
        free(line);
    }
    if(post_validation(game) == 1)//failed post-validation;
    {
        close(fd);
        return(1);
    }
    close(fd);
    return(0);
}
