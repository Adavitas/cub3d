/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_testing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzhyrgal <zzhyrgal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 21:47:48 by zzhyrgal          #+#    #+#             */
/*   Updated: 2026/02/05 13:06:38 by zzhyrgal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"


int main(int argc, char **argv)
{
    t_game game;

    init_game(&game);

    if (argc != 2)
        return (error_msg("Usage: ./cub3D map.cub"));

    if (parse(argv[1], &game) != 0) //build the map
        return (free_game(&game), 1);

    if (validate_game(&game) != 0) //check the map
        return (free_game(&game), 1);

    init_player(&game); // 🔹 derive runtime state

    //start_game(&game);

    free_game(&game);
    
    return (0);
}

