/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 04:11:52 by adavitas          #+#    #+#             */
/*   Updated: 2026/03/02 04:12:09 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

/*
** Compute the ray direction for screen column x.
** camera_x ranges from -1 (left) to +1 (right).
*/
static void	init_ray_dir(t_game *game, t_ray *ray, int x)
{
	float	camera_x;

	camera_x = 2.0f * x / (float)WIN_W - 1.0f;
	ray->ray_dir_x = game->player.dir_x + game->player.plane_x * camera_x;
	ray->ray_dir_y = game->player.dir_y + game->player.plane_y * camera_x;
	ray->map_x = (int)game->player.x;
	ray->map_y = (int)game->player.y;
}

/*
** delta_dist = abs(1 / ray_dir_component).
** step_x/y = -1 or +1 depending on ray direction.
** side_dist = distance from player to the first grid boundary.
*/
static void	init_dda(t_game *game, t_ray *ray)
{
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30f;
	else
		ray->delta_dist_x = fabsf(1.0f / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30f;
	else
		ray->delta_dist_y = fabsf(1.0f / ray->ray_dir_y);
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player.x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0f - game->player.x)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player.y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0f - game->player.y)
			* ray->delta_dist_y;
	}
}

/*
** March through the grid one cell at a time (DDA).
** Stop when we hit a '1' wall tile.
** ray->side records whether last step was in X (0) or Y (1).
*/
static void	run_dda(t_game *game, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_y >= 0 && ray->map_y < game->map.height
			&& ray->map_x >= 0 && ray->map_x < game->map.raw_max_width
			&& game->map.grid[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
}

/*
** cast_single_ray — full pipeline for one screen column:
**  1) compute ray direction  2) init DDA  3) run DDA
**  4) perpendicular distance (fish-eye fix)
**  5) wall slice height + draw bounds
**  6) texture id (N/S/E/W) and wall_x hit coordinate
*/
void	cast_single_ray(t_game *game, t_ray *ray, int x)
{
	init_ray_dir(game, ray, x);
	init_dda(game, ray);
	run_dda(game, ray);
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
	if (ray->perp_wall_dist < 0.0001f)
		ray->perp_wall_dist = 0.0001f;
	ray->line_h = (int)(WIN_H / ray->perp_wall_dist);
	ray->draw_start = -ray->line_h / 2 + WIN_H / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_h / 2 + WIN_H / 2;
	if (ray->draw_end >= WIN_H)
		ray->draw_end = WIN_H - 1;
	if (ray->side == 0)
		ray->wall_x = game->player.y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = game->player.x + ray->perp_wall_dist * ray->ray_dir_x;
	ray->wall_x -= floorf(ray->wall_x);
	if (ray->side == 0 && ray->ray_dir_x < 0)
		ray->tex_id = TEX_WE;
	else if (ray->side == 0 && ray->ray_dir_x >= 0)
		ray->tex_id = TEX_EA;
	else if (ray->side == 1 && ray->ray_dir_y < 0)
		ray->tex_id = TEX_NO;
	else
		ray->tex_id = TEX_SO;
}
