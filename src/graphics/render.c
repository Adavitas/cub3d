/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 14:34:29 by adavitas          #+#    #+#             */
/*   Updated: 2026/03/10 02:18:31 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

/*
** Draw the sky region (row 0 to draw_start) for column x.
*/
static void	draw_ceiling(t_game *game, t_ray *ray, int x, int draw_start)
{
	int		y;
	int		tx;
	int		ty;
	float	angle;
	float	ratio;

	ratio = (float)(game->tex[TEX_SKY].height - 1) / (float)(WIN_H / 2);
	angle = atan2f(ray->ray_dir_y, ray->ray_dir_x);
	if (angle < 0)
		angle += 2.0f * M_PI;
	tx = (int)(angle / (2.0f * M_PI) * game->tex[TEX_SKY].width);
	if (tx >= game->tex[TEX_SKY].width)
		tx = game->tex[TEX_SKY].width - 1;
	y = 0;
	while (y < draw_start)
	{
		ty = (int)((float)y * ratio);
		if (ty >= game->tex[TEX_SKY].height)
			ty = game->tex[TEX_SKY].height - 1;
		game->screen.addr[y * WIN_W + x] = apply_wand_sky(game,
				game->tex[TEX_SKY].addr[ty
				* (game->tex[TEX_SKY].line_len / 4) + tx], y);
		y++;
	}
}

/*
** Compute the wall hit point for floor casting.
*/
static void	get_wall_hit(t_game *game, t_ray *ray, float *wfx, float *wfy)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			*wfx = ray->map_x;
		else
			*wfx = ray->map_x + 1.0f;
		*wfy = game->player.y + ray->perp_wall_dist * ray->ray_dir_y;
	}
	else
	{
		*wfx = game->player.x + ray->perp_wall_dist * ray->ray_dir_x;
		if (ray->ray_dir_y > 0)
			*wfy = ray->map_y;
		else
			*wfy = ray->map_y + 1.0f;
	}
}

/*
** Draw the textured floor region (draw_end to WIN_H) for column x.
*/
static void	draw_floor(t_game *game, t_ray *ray, int x, int draw_end)
{
	int		y;
	float	cd;
	float	w;
	float	wf[2];
	float	fl[2];

	get_wall_hit(game, ray, &wf[0], &wf[1]);
	y = draw_end + 1;
	while (y < WIN_H)
	{
		cd = (float)WIN_H / (2.0f * y - WIN_H);
		w = cd / ray->perp_wall_dist;
		fl[0] = w * wf[0] + (1.0f - w) * game->player.x;
		fl[1] = w * wf[1] + (1.0f - w) * game->player.y;
		game->screen.addr[y * WIN_W + x]
			= apply_wand_fog(game, sample_tex_bilinear(
					&game->tex[TEX_FLOOR],
					fl[0] * game->tex[TEX_FLOOR].width,
					fl[1] * game->tex[TEX_FLOOR].height),
				cd, y);
		y++;
	}
}

/*
** Draw a single textured wall column from draw_start to draw_end.
*/
static void	draw_wall_column(t_game *game, t_ray *ray, int x)
{
	int		tex_x;
	float	step;
	float	tex_pos;
	int		y;
	int		tex_y;

	tex_x = (int)(ray->wall_x * game->tex[ray->tex_id].width);
	if ((ray->side == 0 && ray->ray_dir_x > 0)
		|| (ray->side == 1 && ray->ray_dir_y < 0))
		tex_x = game->tex[ray->tex_id].width - 1 - tex_x;
	step = (float)game->tex[ray->tex_id].height / (float)ray->line_h;
	tex_pos = (ray->draw_start - WIN_H / 2 + ray->line_h / 2) * step;
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		tex_y = (int)tex_pos & (game->tex[ray->tex_id].height - 1);
		tex_pos += step;
		game->screen.addr[y * WIN_W + x]
			= apply_wand_fog(game, get_tex_color(game, ray, tex_x, tex_y),
				ray->perp_wall_dist, y);
		y++;
	}
}

/*
** render_frame - cast one ray per column, draw ceiling + wall + floor.
*/
void	render_frame(t_game *game)
{
	t_ray	ray;
	int		x;

	prepare_wand_light(game);
	x = 0;
	while (x < WIN_W)
	{
		cast_single_ray(game, &ray, x);
		draw_ceiling(game, &ray, x, ray.draw_start);
		draw_wall_column(game, &ray, x);
		draw_floor(game, &ray, x, ray.draw_end);
		x++;
	}
	draw_minimap(game);
	draw_wand_tip_glow(game);
	draw_wand(game);
	draw_wand_sparkles(game);
	mlx_put_image_to_window(game->mlx, game->win, game->screen.img, 0, 0);
}
