/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 20:11:03 by zzhyrgal          #+#    #+#             */
/*   Updated: 2026/03/13 15:26:03 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	setup_hooks_and_loop(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, (int (*)())key_press, game);
	mlx_hook(game->win, 3, 1L << 1, (int (*)())key_release, game);
	mlx_hook(game->win, 4, 1L << 2, (int (*)())mouse_toggle, game);
	mlx_hook(game->win, 17, 0, (int (*)())close_game, game);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		printf("argument count should be equal to 2.");
		return (1);
	}
	if (!cub_file_check(argv[1]))
	{
		printf("file extension validation failed.");
		return (1);
	}
	init_game(&game);
	if (parse(argv[1], &game))
	{
		free_game(&game);
		return (1);
	}
	if (!init_mlx(&game))
	{
		free_game(&game);
		return (1);
	}
	setup_hooks_and_loop(&game);
	return (0);
}
