/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 12:10:32 by adavitas          #+#    #+#             */
/*   Updated: 2026/03/12 20:25:03 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

/*
** Load a single XPM texture file into game->tex[i].
** mlx_xpm_file_to_image reads the file and gives us a void *img handle.
** mlx_get_data_addr turns that handle into a raw int * pixel array so
** the raycaster can do tex.addr[y * TEX_W + x] to sample a colour.
*/
static int	load_texture(t_game *game, int i)
{
	int	w;
	int	h;

	game->tex[i].img = mlx_xpm_file_to_image(game->mlx,
			game->tex[i].path, &w, &h);
	if (!game->tex[i].img)
	{
		printf("Error\nCould not load texture: %s\n", game->tex[i].path);
		return (0);
	}
	game->tex[i].width = w;
	game->tex[i].height = h;
	game->tex[i].addr = (int *)mlx_get_data_addr(game->tex[i].img,
			&game->tex[i].bpp,
			&game->tex[i].line_len,
			&game->tex[i].endian);
	return (1);
}

/*
** Create the off-screen image buffer (game->screen).
** Every frame the raycaster writes pixels into screen.addr,
** then a single mlx_put_image_to_window call flushes it to the window.
** This is much faster than calling mlx_pixel_put() per pixel.
*/
static int	create_screen_image(t_game *game)
{
	game->screen.img = mlx_new_image(game->mlx, WIN_W, WIN_H);
	if (!game->screen.img)
	{
		printf("Error\nCould not create screen image buffer.\n");
		return (0);
	}
	game->screen.addr = (int *)mlx_get_data_addr(game->screen.img,
			&game->screen.bpp,
			&game->screen.line_len,
			&game->screen.endian);
	return (1);
}

/*
** Set up extra texture paths and load all textures.
*/
static int	load_all_textures(t_game *game)
{
	int	i;

	game->tex[TEX_FLOOR].path = ft_strdup("./textures/floor_concrete.xpm");
	game->tex[TEX_FLOOR].is_set = true;
	game->tex[TEX_SKY].path = ft_strdup("./textures/sky.xpm");
	game->tex[TEX_SKY].is_set = true;
	game->tex[TEX_DOOR].path = ft_strdup("./textures/door_durin.xpm");
	game->tex[TEX_DOOR].is_set = true;
	i = 0;
	while (i < 7)
	{
		if (!load_texture(game, i))
			return (0);
		i++;
	}
	return (1);
}

static int	init_door_state(t_game *game)
{
	int	i;

	game->map.door_open = ft_calloc(game->map.height, sizeof(bool *));
	if (!game->map.door_open)
		return (0);
	i = 0;
	while (i < game->map.height)
	{
		game->map.door_open[i] = ft_calloc(game->map.raw_max_width,
				sizeof(bool));
		if (!game->map.door_open[i])
			return (0);
		i++;
	}
	return (1);
}

/*
** init_mlx - connects to X server, opens window, loads textures.
*/
int	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		printf("Error\nmlx_init failed.\n");
		return (0);
	}
	game->win = mlx_new_window(game->mlx, WIN_W, WIN_H, "cub3D");
	if (!game->win)
	{
		printf("Error\nCould not open window.\n");
		return (fail_mlx_init(game));
	}
	if (!create_screen_image(game))
		return (fail_mlx_init(game));
	if (!init_door_state(game))
		return (fail_mlx_init(game));
	if (!load_all_textures(game))
		return (fail_mlx_init(game));
	if (!init_wand(game))
		return (fail_mlx_init(game));
	return (1);
}
