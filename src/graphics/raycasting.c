/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 04:11:52 by adavitas          #+#    #+#             */
/*   Updated: 2026/03/12 20:25:03 by adavitas         ###   ########.fr       */
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
** Check if the current cell is a wall or closed door.
** Returns 1 for wall, 2 for closed door, 0 otherwise.
*/
static int	check_hit(t_game *game, t_ray *ray)
{
	if (ray->map_y < 0 || ray->map_y >= game->map.height
		|| ray->map_x < 0 || ray->map_x >= game->map.raw_max_width)
		return (0);
	if (is_wall_tile(game->map.grid[ray->map_y][ray->map_x]))
		return (1);
	if (game->map.grid[ray->map_y][ray->map_x] == 'D'
		&& !game->map.door_open[ray->map_y][ray->map_x])
		return (2);
	return (0);
}

/*
** March through the grid one cell at a time (DDA).
** Stop when we hit a wall or closed door.
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
		hit = check_hit(game, ray);
	}
}

/*
** Determine texture ID and wall_x hit coordinate.
*/
static void	set_wall_info(t_game *game, t_ray *ray)
{
	char	tile;

	if (ray->side == 0)
		ray->wall_x = game->player.y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = game->player.x + ray->perp_wall_dist * ray->ray_dir_x;
	ray->wall_x -= floorf(ray->wall_x);
	tile = game->map.grid[ray->map_y][ray->map_x];
	ray->tex_id = get_wall_tex_id(tile);
	if (ray->tex_id == TEX_UNKNOWN)
		ray->tex_id = TEX_NO;
}

/*
** cast_single_ray - full pipeline for one screen column.
*/
void	cast_single_ray(t_game *game, t_ray *ray, int x)
{
	init_ray_dir(game, ray, x);
	init_dda_x(game, ray);
	init_dda_y(game, ray);
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
	set_wall_info(game, ray);
}
