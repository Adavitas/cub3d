/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 17:39:01 by adavitas          #+#    #+#             */
/*   Updated: 2026/02/25 17:39:05 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# ifndef CUB_UTILS_H
# define CUB_UTILS_H

# include "game.h"

/*
 * src/parsing/flood_fill.c
 * Validates that the map is fully enclosed by walls.
 * Starts a flood-fill from (start_x, start_y) — the player's tile.
 * Returns 0 if the map is closed, 1 if it is open/invalid.
 */
int		flood_fill(t_map *map, int start_x, int start_y);

/*
 * src/parsing/ext_validate.c
 * Checks that `filename` ends with the expected extension (e.g. ".cub").
 * Returns 0 on success, 1 on failure.
 */
int		validate_file_extension(char *filename, char *ext);

/*
 * src/parsing/ext_validate.c
 * Verifies no map row has length 0.
 * Returns 0 if the map rows are all non-empty, 1 otherwise.
 */
int		validate_map_rows(t_map *map);

/*
 * src/utils/error.c
 * Prints "Error\n<message>\n" to stderr, calls free_game, then exit(1).
 * Mirrors so_long's error_exit but adapted to not return a value.
 */
void	error_exit(t_game *game, char *message);

#endif
