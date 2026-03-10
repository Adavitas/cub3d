/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: test                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 16:30:00 by test              #+#    #+#             */
/*   Updated: 2026/03/10 16:30:00 by test             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	print_texture_info(t_game *game)
{
	printf("\n=== TEXTURES ===\n");
	printf("NO: %s (set: %d)\n", game->tex[TEX_NO].path, game->tex[TEX_NO].is_set);
	printf("SO: %s (set: %d)\n", game->tex[TEX_SO].path, game->tex[TEX_SO].is_set);
	printf("WE: %s (set: %d)\n", game->tex[TEX_WE].path, game->tex[TEX_WE].is_set);
	printf("EA: %s (set: %d)\n", game->tex[TEX_EA].path, game->tex[TEX_EA].is_set);
	if (game->tex[TEX_DOOR].is_set)
		printf("DO: %s (set: %d)\n", game->tex[TEX_DOOR].path, game->tex[TEX_DOOR].is_set);
}

static void	print_color_info(t_game *game)
{
	printf("\n=== COLORS ===\n");
	printf("Floor:   R=%d, G=%d, B=%d (set: %d)\n",
		game->floor.r, game->floor.g, game->floor.b, game->floor.is_set);
	printf("Ceiling: R=%d, G=%d, B=%d (set: %d)\n",
		game->ceiling.r, game->ceiling.g, game->ceiling.b, game->ceiling.is_set);
}

static void	print_map_info(t_game *game)
{
	int	i;

	printf("\n=== MAP ===\n");
	printf("Width: %d, Height: %d\n", game->map.width, game->map.height);
	printf("Player: (%.1f, %.1f) orientation: %c\n",
		game->player.x, game->player.y, game->player.p_orientation);
	printf("Direction: (%.2f, %.2f)\n", game->player.dir_x, game->player.dir_y);
	printf("Plane: (%.2f, %.2f)\n\n", game->player.plane_x, game->player.plane_y);
	printf("Map grid:\n");
	i = 0;
	while (i < game->map.height && game->map.grid[i])
	{
		printf("%s\n", game->map.grid[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		printf("Usage: %s <map.cub>\n", argv[0]);
		return (1);
	}
	if (!cub_file_check(argv[1]))
	{
		printf("Error: Invalid file extension (must be .cub)\n");
		return (1);
	}
	init_game(&game);
	printf("\n========================================\n");
	printf("Testing: %s\n", argv[1]);
	printf("========================================\n");
	if (parse(argv[1], &game))
	{
		printf("\n❌ PARSING FAILED\n");
		free_game(&game);
		return (1);
	}
	printf("\n✓ PARSING SUCCESSFUL\n");
	print_texture_info(&game);
	print_color_info(&game);
	print_map_info(&game);
	free_game(&game);
	printf("\n========================================\n");
	printf("✓ Test completed successfully\n");
	printf("========================================\n\n");
	return (0);
}
