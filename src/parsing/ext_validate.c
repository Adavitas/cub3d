/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ext_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 17:38:40 by adavitas          #+#    #+#             */
/*   Updated: 2026/02/25 17:38:44 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*
 * Ported and adapted from Adavitas/so_long validate_file_extension
 * and validate_rectangle.
 *
 * validate_file_extension: generalized to accept the expected extension
 * as a parameter (so_long hardcoded ".ber"; here pass ".cub").
 *
 * validate_map_rows: replaces validate_rectangle — cub3d maps do NOT
 * need to be strictly rectangular (rows may differ in length), but every
 * row must be non-empty.  Use flood_fill for the actual closure check.
 */

#include "game.h"
#include <string.h>

/*
 * validate_file_extension
 * Checks that `filename` ends with `ext` (e.g. ".cub").
 * Returns 0 on success, 1 on failure.
 *
 * Usage during argument parsing:
 *   if (validate_file_extension(argv[1], ".cub") != 0)
 *       return (error_msg("File must have a .cub extension"));
 */
int	validate_file_extension(char *filename, char *ext)
{
	int	flen;
	int	elen;

	if (!filename || !ext)
		return (1);
	flen = (int)strlen(filename);
	elen = (int)strlen(ext);
	if (flen < elen)
		return (1);
	if (strcmp(filename + flen - elen, ext) != 0)
		return (1);
	return (0);
}

/*
 * validate_map_rows
 * Checks that the map has at least one row and no row has zero length.
 * cub3d maps can have rows of varying widths (spaces are valid padding),
 * but a zero-length row would break the parser and raycaster.
 * Returns 0 if all rows are non-empty, 1 otherwise.
 *
 * Usage in post-validation:
 *   if (validate_map_rows(&game->map) != 0)
 *       return (error_exit(game, "Map contains an empty row"), 1);
 */
int	validate_map_rows(t_map *map)
{
	int	i;

	if (!map || !map->grid || map->height <= 0)
		return (1);
	i = 0;
	while (i < map->height)
	{
		if (!map->grid[i] || map->grid[i][0] == '\0')
			return (1);
		i++;
	}
	return (0);
}
