/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzhyrgal <zzhyrgal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 14:07:05 by zzhyrgal          #+#    #+#             */
/*   Updated: 2026/02/22 21:33:17 by zzhyrgal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int helper_dispatch_two(char *line, t_game *game, t_node **raw_map)
{
    if(valid_map(line) == 1)
        return(1);
    if(reading_raw_map(line, game, raw_map))
        return(1);
    return(0);
}

int helper_dispatch(char *line, t_game *game, t_node **raw_map)
{
    if(valid_map(line) == 0)
    {
        game->map_started = true;
        if(reading_raw_map(line, game, raw_map))
                return(1);
        return(0);
    }
    else
    {
        printf("Map validation failed.\n");
        return(1);
    }
    return(0);
}

int dispatch_line(char *line, t_game *game, t_node **raw_map)
{
    int i = 0;
    //0 - success and 1 - failure;
    while(isspace(line[i]))
        i++;
    if(order(game) != 0)
    {
        if(select_parse(&line[i], game) == 0)
            return(0);
        else
        {
            printf("texture/color parsing error.\n");
            return(1);
        }
    }
    if(!game->map_started)
    {
        if(helper_dispatch(line, game, raw_map))
            return(1);
        return(0);
    }
    if(game->map_started)
    {
        if(helper_dispatch_two(line, game, raw_map))
            return(1);
        return(0);
    }
    return(0);
}

int read_file_lines(int fd, t_game *game, t_node **raw_map)
{
    char *line;

    line = get_next_line(fd);
    while(line != NULL)
    {
        if(is_empty(line))
        {
            if(game->map_started)
            {
                free(line);
                printf("invalid structure: map cannot have empty lines once starts.\n");
                return(1);
            }
            free(line);
            line = get_next_line(fd);
            continue;
        }
        if(dispatch_line(line, game, raw_map))
        {
            free(line);
            return(1);
        }
        free(line);
        line = get_next_line(fd);
    }
    return(0);
}

int parse(const char *file, t_game *game)
{
    int fd;
    t_node *raw_map;

    raw_map = NULL;
    fd = open(file, O_RDONLY);
    if(fd < 0)
    {
        printf("File opening failed.\n");
        return(-1);
    }
    if(read_file_lines(fd, game, &raw_map))
    {
        free_list_maplines(&raw_map);
        close(fd);
        return(1);
    }
    if(parse_map(game, raw_map))
    {
        free_list_maplines(&raw_map);
        free_game(game);
        close(fd);
        return(1);
    }
    free_list_maplines(&raw_map);
    set_up_dir_plane(&game->player);
    if(post_validation(game))
    {
        free_game(game);
        close(fd);
        return(1);
    }
    close(fd);
    return(0);
}
