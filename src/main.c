/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 20:11:03 by zzhyrgal          #+#    #+#             */
/*   Updated: 2026/02/26 18:13:32 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int main(int argc, char **argv)
{
    t_game game;

    (void)argc;
    init_game(&game);

    // 1. Parse world
    parse(argv[1], &game);        // fills game.map and game.player start info

    // 2. Initialize graphics
    // init_mlx(&game);           // TODO: window, images, textures

    // 3. Register input callbacks
    // mlx_hook(game.win, 2, 1L<<0, key_press, &game);
    // mlx_hook(game.win, 3, 1L<<1, key_release, &game);

    // 4. Game loop hook
    // mlx_loop_hook(game.mlx, game_loop, &game);

    // 5. Start runtime
    // mlx_loop(game.mlx);
    return (0);
}
