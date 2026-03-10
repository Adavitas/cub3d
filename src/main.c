/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 20:11:03 by zzhyrgal          #+#    #+#             */
/*   Updated: 2026/03/10 00:37:46 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	main(int argc, char **argv)
{
	t_game	game;

	(void)argc;
	init_game(&game);
	parse(argv[1], &game);
	if (!init_mlx(&game))
	{
		free_game(&game);
		return (1);
	}
	mlx_hook(game.win, 2, 1L << 0, (int (*)())key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, (int (*)())key_release, &game);
	mlx_hook(game.win, 17, 0, (int (*)())close_game, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
