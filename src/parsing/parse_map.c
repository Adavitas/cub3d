/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 17:02:23 by zzhyrgal          #+#    #+#             */
/*   Updated: 2026/03/12 16:06:18 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	fill_void_spaces(char *row, int start, int max_width)
{
	while (start < max_width)
	{
		row[start] = ' ';
		start++;
	}
	row[start] = '\0';
}

void	check_player_position(t_game *game, char c, int row, int col)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		game->player.player_count++;
		game->player.x = (float)col + 0.5;
		game->player.y = (float)row + 0.5;
		game->player.p_orientation = c;
	}
}

int	parse_row(t_game *game, t_node *node, int i)
{
	int	j;
	int	len;

	len = ft_strlen(node->line);
	game->map.grid[i] = malloc(sizeof(char) * (game->map.raw_max_width + 1));
	if (!game->map.grid[i])
		return (1);
	j = 0;
	while (j < len)
	{
		game->map.grid[i][j] = node->line[j];
		check_player_position(game, node->line[j], i, j);
		if (node->line[j] == 'N' || node->line[j] == 'S'
			|| node->line[j] == 'E' || node->line[j] == 'W')
			game->map.grid[i][j] = '0';
		j++;
	}
	fill_void_spaces(game->map.grid[i], j, game->map.raw_max_width);
	return (0);
}

int	reading_raw_map(char *line, t_game *game, t_node **raw_map)
{
	int		i;
	int		line_len;
	t_node	*node;

	i = 0;
	line_len = 0;
	while (line[i] && line[i] != '\n')
		i++;
	line_len = i;
	if (line_len > game->map.raw_max_width)
		game->map.raw_max_width = line_len;
	game->map.height += 1;
	node = new_node(line);
	if (!node)
		return (1);
	add_back(raw_map, node);
	return (0);
}

int	parse_map(t_game *game, t_node *raw_map)
{
	t_node	*node;
	int		i;

	node = raw_map;
	game->map.grid = malloc(sizeof(char *) * (game->map.height + 1));
	if (!game->map.grid)
		return (1);
	i = 0;
	while (node)
	{
		if (parse_row(game, node, i))
		{
			free_partial_grid(game, i);
			return (1);
		}
		node = node->next;
		i++;
	}
	game->map.grid[i] = NULL;
	if (game->player.player_count != 1)
	{
		printf("more than one player\n");
		return (1);
	}
	return (0);
}

/*
read line
   ↓
validate line
   ↓
store line in temp array
   ↓
after reading all map lines:
    calculate height
    calculate max width
    allocate grid[height][width]
    copy lines
*/