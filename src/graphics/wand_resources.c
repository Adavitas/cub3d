/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wand_resources.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 12:00:00 by adavitas          #+#    #+#             */
/*   Updated: 2026/04/29 12:00:00 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static char	*get_wand_path(int i)
{
	if (i == WAND_FRAME_OFF)
		return ("./textures/wand/wand_off_idle.xpm");
	if (i == WAND_FRAME_TURN_1)
		return ("./textures/wand/wand_turn_1.xpm");
	if (i == WAND_FRAME_TURN_2)
		return ("./textures/wand/wand_turn_2.xpm");
	if (i == WAND_FRAME_TURN_3)
		return ("./textures/wand/wand_turn_3.xpm");
	if (i == WAND_FRAME_ON_A)
		return ("./textures/wand/wand_on_idle_a.xpm");
	return ("./textures/wand/wand_on_idle_b.xpm");
}

static int	set_wand_paths(t_wand *wand)
{
	int	i;

	i = 0;
	while (i < WAND_FRAME_COUNT)
	{
		wand->frame[i].path = ft_strdup(get_wand_path(i));
		if (!wand->frame[i].path)
			return (0);
		i++;
	}
	return (1);
}

static int	load_wand_frame(t_game *game, int i)
{
	int	w;
	int	h;

	game->wand.frame[i].img = mlx_xpm_file_to_image(game->mlx,
			game->wand.frame[i].path, &w, &h);
	if (!game->wand.frame[i].img)
	{
		printf("Error\nCould not load texture: %s\n",
			game->wand.frame[i].path);
		return (0);
	}
	game->wand.frame[i].width = w;
	game->wand.frame[i].height = h;
	game->wand.frame[i].addr = (int *)mlx_get_data_addr(
			game->wand.frame[i].img, &game->wand.frame[i].bpp,
			&game->wand.frame[i].line_len, &game->wand.frame[i].endian);
	return (1);
}

static int	fail_wand_init(t_game *game)
{
	destroy_wand_images(game);
	free_wand(&game->wand);
	return (0);
}

int	init_wand(t_game *game)
{
	int	i;

	ft_bzero(&game->wand, sizeof(t_wand));
	game->wand.state = WAND_OFF;
	game->wand.frame_id = WAND_FRAME_OFF;
	game->wand.last_x = game->player.x;
	game->wand.last_y = game->player.y;
	if (!set_wand_paths(&game->wand))
		return (fail_wand_init(game));
	i = 0;
	while (i < WAND_FRAME_COUNT)
	{
		if (!load_wand_frame(game, i))
			return (fail_wand_init(game));
		i++;
	}
	return (1);
}
