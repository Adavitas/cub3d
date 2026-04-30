/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 22:40:19 by adavitas          #+#    #+#             */
/*   Updated: 2026/03/12 20:25:03 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

/*
** t_ray — holds all per-column DDA raycasting state.
**
** ray_dir_x/y : direction of the ray in world space
** side_dist_x/y : distance from player to next grid line
** delta_dist_x/y : distance between two consecutive grid lines
** perp_wall_dist : corrected distance to wall (no fish-eye)
** step_x/y : direction to step in grid (-1 or +1)
** map_x/y : current grid cell the ray is in
** side : 0 = vertical wall hit (NS), 1 = horizontal wall hit (EW)
** tex_id : index into game->tex[4] (NO=0 SO=1 WE=2 EA=3)
** wall_x : exact fractional hit point on the wall (0.0–1.0)
** line_h : height of the wall slice to draw on screen
** draw_start : top pixel of the wall slice
** draw_end : bottom pixel of the wall slice
*/
typedef struct s_ray
{
	float	ray_dir_x;
	float	ray_dir_y;
	float	side_dist_x;
	float	side_dist_y;
	float	delta_dist_x;
	float	delta_dist_y;
	float	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		map_x;
	int		map_y;
	int		side;
	int		tex_id;
	float	wall_x;
	int		line_h;
	int		draw_start;
	int		draw_end;
}	t_ray;

/* Forward declaration */
typedef struct s_game	t_game;

/* raycasting.c — DDA algorithm */
void	cast_single_ray(t_game *game, t_ray *ray, int x);

/* raycasting_utils.c — DDA helpers */
void	init_dda_x(t_game *game, t_ray *ray);
void	init_dda_y(t_game *game, t_ray *ray);

/* render.c — drawing wall slices, ceiling, floor */
void	render_frame(t_game *game);
void	draw_wand(t_game *game);

/* render_utils.c — texture sampling and color helpers */
int		get_tex_color(t_game *game, t_ray *ray, int tex_x, int tex_y);
int		rgb_to_int(int r, int g, int b);
int		apply_fog(int color, float distance, float max_dist);
int		apply_wand_fog(t_game *game, int color, float distance, int y);
int		apply_wand_sky(t_game *game, int color, int y);
void	prepare_wand_light(t_game *game);
int		light_clamp_channel(int value);
float	light_clamp_float(float value, float min, float max);
float	wand_state_light(t_game *game);
int		add_warm_light(int color, float power);
int		sample_tex_bilinear(t_tex *tex, float fx, float fy);
int		is_wand_transparent(int color);
void	draw_wand_unscaled(t_game *game, t_tex *frame, int *pos,
			int *clip);
void	draw_wand_scaled(t_game *game, t_tex *frame, int *pos, int *clip);

/* minimap.c + minimap_utils.c — top-left minimap overlay */
void	draw_minimap(t_game *game);
void	draw_border(t_game *game, int tsz);
void	draw_tile(t_game *game, int *pos, int tsz, int color);

/* game_loop.c — main frame loop */
int		game_loop(t_game *game);

#endif
