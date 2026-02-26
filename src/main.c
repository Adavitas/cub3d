/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 20:11:03 by zzhyrgal          #+#    #+#             */
/*   Updated: 2026/02/26 21:28:35 by adavitas         ###   ########.fr       */
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
    if (!init_mlx(&game))
    {
        free_game(&game);
        return (1);
    }

    // 3. Register input callbacks
    mlx_hook(game.win, 2, 1L<<0, (int (*)())key_press, &game.key);
    mlx_hook(game.win, 3, 1L<<1, (int (*)())key_release, &game.key);
    mlx_hook(game.win, 17, 0, (int (*)())close_game, &game);

    // 4. Game loop hook (raycaster goes here — Step 3)
    // mlx_loop_hook(game.mlx, game_loop, &game);

    // 5. Start runtime
    mlx_loop(game.mlx);
    return (0);
}
