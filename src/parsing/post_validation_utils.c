/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_validation_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzhyrgal <zzhyrgal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 17:43:39 by zzhyrgal          #+#    #+#             */
/*   Updated: 2026/03/10 16:06:09 by zzhyrgal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	free_map_copy(char **map, int height)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (i < height)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

int	flood_fill(char **map_copy, int x, int y, int height)
{
	int	row_len;

	if (x < 0 || y < 0 || x >= height)
		return (1);
	row_len = ft_strlen(map_copy[x]);
	if (y >= row_len)
		return (1);
	if (map_copy[x][y] == ' ' || map_copy[x][y] == '\t')
		return (1);
	if (is_wall_tile(map_copy[x][y]) || map_copy[x][y] == 'V'
		|| map_copy[x][y] == 'D')
		return (0);
	map_copy[x][y] = 'V';
	if (flood_fill(map_copy, x + 1, y, height))
		return (1);
	if (flood_fill(map_copy, x - 1, y, height))
		return (1);
	if (flood_fill(map_copy, x, y + 1, height))
		return (1);
	if (flood_fill(map_copy, x, y - 1, height))
		return (1);
	return (0);
}

char	**copy_map(t_map *map)
{
	char	**copy_map;
	int		i;

	copy_map = malloc(sizeof(char *) * (map->height + 1));
	if (!copy_map)
		return (NULL);
	i = 0;
	while (i < map->height)
	{
		copy_map[i] = ft_strdup(map->grid[i]);
		if (!copy_map)
			return (NULL);
		if (!copy_map[i])
		{
			free_map_copy(copy_map, i);
			return (NULL);
		}
		i++;
	}
	copy_map[i] = NULL;
	return (copy_map);
}

int	validate_map(t_game *game)
{
	char	**copy_karta;
	int		result;
	int		row;
	int		col;

	copy_karta = copy_map(&game->map);
	row = (int)game->player.y;
	col = (int)game->player.x;
	result = flood_fill(copy_karta, row, col, game->map.height);
	free_map_copy(copy_karta, game->map.height);
	return (result);
}
