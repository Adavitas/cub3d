/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzhyrgal <zzhyrgal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 14:07:05 by zzhyrgal          #+#    #+#             */
/*   Updated: 2026/03/10 16:10:22 by zzhyrgal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	read_file_lines(int fd, t_game *game, t_node **raw_map)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		if (is_empty(line))
		{
			if (game->map_started)
			{
				free(line);
				return (1);
			}
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (dispatch_line(line, game, raw_map))
		{
			free(line);
			return (1);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

int	process_map_validation(t_game *game, t_node *raw_map, int fd)
{
	if (parse_map(game, raw_map))
	{
		free_list_maplines(&raw_map);
		close(fd);
		return (1);
	}
	free_list_maplines(&raw_map);
	set_up_dir_plane(&game->player);
	if (post_validation(game))
	{
		close(fd);
		return (1);
	}
	return (0);
}

int	parse(const char *file, t_game *game)
{
	int		fd;
	t_node	*raw_map;

	raw_map = NULL;
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		printf("File opening failed.\n");
		return (1);
	}
	if (read_file_lines(fd, game, &raw_map))
	{
		free_list_maplines(&raw_map);
		close(fd);
		return (1);
	}
	if (process_map_validation(game, raw_map, fd))
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}
