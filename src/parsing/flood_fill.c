/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 17:38:32 by adavitas          #+#    #+#             */
/*   Updated: 2026/02/25 17:38:36 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*
 * Ported and adapted from Adavitas/so_long flood_fill.
 *
 * Key differences from so_long:
 *  - No t_point; uses plain int x / y (avoids unsigned wrap-around on -1).
 *  - Works on t_map from map.h (grid, width, height).
 *  - ' ' (space) is treated as an open gap → map is NOT enclosed.
 *  - Player start tiles (N/S/E/W) are treated the same as '0' floors.
 *  - Returns 0 = map is closed, 1 = map is open / out-of-bounds reached.
 */

#include "game.h"
#include <string.h>

/* ── helpers ─────────────────────────────────────────────────── */

static char	**duplicate_grid(char **grid, int height)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < height)
	{
		copy[i] = strdup(grid[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[height] = NULL;
	return (copy);
}

static void	free_grid_copy(char **copy, int height)
{
	int	i;

	i = 0;
	while (i < height)
		free(copy[i++]);
	free(copy);
}

/* ── recursive fill ─────────────────────────────────────────── */

static void	fill(char **grid, int x, int y, int height, int *fail)
{
	int	row_len;

	if (*fail)
		return ;
	/* out-of-bounds vertically → not enclosed */
	if (y < 0 || y >= height || !grid[y])
	{
		*fail = 1;
		return ;
	}
	row_len = (int)strlen(grid[y]);
	/* out-of-bounds horizontally → not enclosed */
	if (x < 0 || x >= row_len)
	{
		*fail = 1;
		return ;
	}
	/* wall or already visited → stop */
	if (grid[y][x] == '1' || grid[y][x] == 'V')
		return ;
	/* space counts as an open gap → not enclosed */
	if (grid[y][x] == ' ')
	{
		*fail = 1;
		return ;
	}
	/* mark visited and recurse in 4 directions */
	grid[y][x] = 'V';
	fill(grid, x + 1, y, height, fail);
	fill(grid, x - 1, y, height, fail);
	fill(grid, x, y + 1, height, fail);
	fill(grid, x, y - 1, height, fail);
}

/* ── public interface ───────────────────────────────────────── */

/*
 * flood_fill - checks map closure.
 * start_x / start_y: the tile where the player starts (N/S/E/W cell).
 * Returns 0 if the map is fully enclosed by walls, 1 otherwise.
 *
 * Usage in post_validation / check_walls_player:
 *   if (flood_fill(&game->map, player_tile_x, player_tile_y) != 0)
 *       return (error_exit(game, "Map is not enclosed by walls"), 1);
 */
int	flood_fill(t_map *map, int start_x, int start_y)
{
	char	**copy;
	int		fail;

	if (!map || !map->grid)
		return (1);
	copy = duplicate_grid(map->grid, map->height);
	if (!copy)
		return (1);
	fail = 0;
	fill(copy, start_x, start_y, map->height, &fail);
	free_grid_copy(copy, map->height);
	return (fail);
}
