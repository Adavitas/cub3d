/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 14:34:29 by adavitas          #+#    #+#             */
/*   Updated: 2026/03/04 11:35:53 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "game.h"


// Draw the sky region (row 0 to draw_start) for column x.
// Uses perspective-correct vertical mapping: the sky is treated as a dome,
// so near the horizon the texture compresses naturally (no stretching).

static void	draw_ceiling(t_game *game, t_ray *ray, int x, int draw_start)
{
	int		y;
	int		tx;
	int		ty;
	int		stride;
	int		tw;
	int		th;
	float	angle;

	tw = game->tex[TEX_SKY].width;
	th = game->tex[TEX_SKY].height;
	stride = game->tex[TEX_SKY].line_len / 4;
	angle = atan2f(ray->ray_dir_y, ray->ray_dir_x);
	if (angle < 0)
		angle += 2.0f * M_PI;
	tx = (int)(angle / (2.0f * M_PI) * tw);
	if (tx >= tw)
		tx = tw - 1;
	y = 0;
	while (y < draw_start)
	{
		ty = (int)((float)y / (float)(WIN_H / 2) * (float)(th - 1));
		if (ty >= th)
			ty = th - 1;
		game->screen.addr[y * WIN_W + x]
			= game->tex[TEX_SKY].addr[ty * stride + tx];
		y++;
	}
}

// Draw the textured floor region (draw_end to WIN_H) for column x.
// Uses floor-casting: for each pixel below the wall, project back
// into world space and sample the floor texture.

static void	draw_floor(t_game *game, t_ray *ray, int x, int draw_end)
{
	int		y;
	float	current_dist;
	float	weight;
	float	floor_x;
	float	floor_y;
	int		tw;
	int		th;
	float	wall_fx;
	float	wall_fy;

	if (ray->side == 0)
	{
		wall_fx = ray->map_x + ray->perp_wall_dist * ray->ray_dir_x;
		if (ray->ray_dir_x > 0)
			wall_fx = ray->map_x;
		else
			wall_fx = ray->map_x + 1.0f;
		wall_fy = game->player.y + ray->perp_wall_dist * ray->ray_dir_y;
	}
	else
	{
		wall_fx = game->player.x + ray->perp_wall_dist * ray->ray_dir_x;
		if (ray->ray_dir_y > 0)
			wall_fy = ray->map_y;
		else
			wall_fy = ray->map_y + 1.0f;
	}
	tw = game->tex[TEX_FLOOR].width;
	th = game->tex[TEX_FLOOR].height;
	y = draw_end + 1;
	while (y < WIN_H)
	{
		current_dist = (float)WIN_H / (2.0f * y - WIN_H);
		weight = current_dist / ray->perp_wall_dist;
		floor_x = weight * wall_fx + (1.0f - weight) * game->player.x;
		floor_y = weight * wall_fy + (1.0f - weight) * game->player.y;
		game->screen.addr[y * WIN_W + x]
			= apply_fog(sample_tex_bilinear(&game->tex[TEX_FLOOR],
				floor_x * tw, floor_y * th), current_dist, 16.0f);
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
			= apply_fog(get_tex_color(game, ray, tex_x, tex_y),
				ray->perp_wall_dist, 16.0f);
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
		draw_ceiling(game, &ray, x, ray.draw_start);
		draw_wall_column(game, &ray, x);
		draw_floor(game, &ray, x, ray.draw_end);
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->screen.img, 0, 0);
}
