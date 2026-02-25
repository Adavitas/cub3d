/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 21:01:21 by zzhyrgal          #+#    #+#             */
/*   Updated: 2026/02/25 18:09:37 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int check_walls_player(t_map *map, t_game *game)
{
        // 1. all rows non-empty
    if (validate_map_rows(map) != 0)
        error_exit(game, "Map contains an empty row");

    // 2. find player tile (N/S/E/W) and get its x/y from the map grid
    //    (your parse already records player_x / player_y in t_player)
    if (flood_fill(map, game->player.x, game->player.y) != 0)
        error_exit(game, "Map is not enclosed by walls");

    return (0);
}