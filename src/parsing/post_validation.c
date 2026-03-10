/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzhyrgal <zzhyrgal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 21:01:21 by zzhyrgal          #+#    #+#             */
/*   Updated: 2026/03/10 16:14:21 by zzhyrgal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	validate_door(t_map *map, int i, int j)
{
	int	row_len;
	int	has_horizontal;
	int	has_vertical;

	row_len = ft_strlen(map->grid[i]);
	has_horizontal = (j > 0 && j < row_len - 1
			&& map->grid[i][j - 1] == '1' && map->grid[i][j + 1] == '1');
	has_vertical = (i > 0 && i < map->height - 1
			&& map->grid[i - 1][j] == '1' && map->grid[i + 1][j] == '1');
	if (!has_horizontal && !has_vertical)
	{
		printf("Door must have walls on opposite sides\n");
		return (1);
	}
	return (0);
}

int	validate_chars(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->grid[i])
	{
		j = 0;
		while (map->grid[i][j])
		{
			if (map->grid[i][j] != '0' && map->grid[i][j] != '1'
				&& map->grid[i][j] != ' ' && map->grid[i][j] != '\t'
				&& map->grid[i][j] != 'D')
			{
				printf("Invalid character in map: '%c'\n", map->grid[i][j]);
				return (1);
			}
			if (map->grid[i][j] == 'D')
				if (validate_door(map, i, j))
					return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	validate_player(t_game *game)
{
	int	row_len;
	int	row;
	int	col;

	row = (int)game->player.y;
	col = (int)game->player.x;
	if (row < 0 || col < 0 || row >= game->map.height)
		return (1);
	row_len = strlen(game->map.grid[row]);
	if (col >= row_len)
		return (1);
	return (0);
}

int	post_validation(t_game *game)
{
	if (validate_chars(&game->map))
	{
		printf("validation did not pass, unknown token.\n");
		return (1);
	}
	if (validate_player(game))
		return (1);
	if (validate_map(game))
	{
		printf("not enclosed with walls.\ncheck_walls.\n");
		return (1);
	}
	return (0);
}
