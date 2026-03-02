/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 14:34:29 by adavitas          #+#    #+#             */
/*   Updated: 2026/03/02 04:57:47 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "game.h"


//Draw the ceiling region (row 0 to draw_start) for column x.

static void	draw_ceiling(t_game *game, int x, int draw_start)
{
	int	y;
	int	color;

	color = rgb_to_int(game->ceiling.r, game->ceiling.g, game->ceiling.b);
	y = 0;
	while (y < draw_start)
	{
		game->screen.addr[y * WIN_W + x] = color;
		y++;
	}
}

// Draw the floor region (draw_end to WIN_H) for column x.

static void	draw_floor(t_game *game, int x, int draw_end)
{
	int	y;
	int	color;

	color = rgb_to_int(game->floor.r, game->floor.g, game->floor.b);
	y = draw_end + 1;
	while (y < WIN_H)
	{
		game->screen.addr[y * WIN_W + x] = color;
		y++;
	}
}

// Draw a single textured wall column from draw_start to draw_end.
// tex_x  : horizontal pixel coordinate within the texture (0..TEX_W-1).
// step   : how much to advance in texture-Y per screen pixel.
// tex_pos: current fractional position inside the texture column.
static void	draw_wall_column(t_game *game, t_ray *ray, int x)
{
	int		tex_x;
	float	step;
	float	tex_pos;
	int		y;
	int		tex_y;
	int		tw;
	int		th;

	tw = game->tex[ray->tex_id].width;
	th = game->tex[ray->tex_id].height;
	tex_x = (int)(ray->wall_x * tw);
	if ((ray->side == 0 && ray->ray_dir_x > 0)
		|| (ray->side == 1 && ray->ray_dir_y < 0))
		tex_x = tw - 1 - tex_x;
	step = (float)th / (float)ray->line_h;
	tex_pos = (ray->draw_start - WIN_H / 2 + ray->line_h / 2) * step;
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		tex_y = (int)tex_pos & (th - 1);
		tex_pos += step;
		game->screen.addr[y * WIN_W + x]
			= get_tex_color(game, ray, tex_x, tex_y);
		y++;
	}
}

// render_frame — cast one ray per screen column, draw ceiling + wall + floor.
// After the loop, flush the completed image to the window in one call.
void	render_frame(t_game *game)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < WIN_W)
	{
		cast_single_ray(game, &ray, x);
		draw_ceiling(game, x, ray.draw_start);
		draw_wall_column(game, &ray, x);
		draw_floor(game, x, ray.draw_end);
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->screen.img, 0, 0);
}
