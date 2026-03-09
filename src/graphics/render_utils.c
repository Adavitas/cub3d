/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 14:34:16 by adavitas          #+#    #+#             */
/*   Updated: 2026/03/02 16:08:52 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "game.h"

// Pack R, G, B values (0–255 each) into a single 0xRRGGBB int
// for writing into the image buffer.
int	rgb_to_int(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

// Apply distance fog: darken a color based on distance.
// fog_factor 1.0 = full brightness, 0.0 = black.
int	apply_fog(int color, float distance, float max_dist)
{
	float	fog;
	int		r;
	int		g;
	int		b;

	fog = 1.0f - (distance / max_dist);
	if (fog < 0.0f)
		fog = 0.0f;
	if (fog > 1.0f)
		fog = 1.0f;
	fog = fog * fog;
	r = (int)(((color >> 16) & 0xFF) * fog);
	g = (int)(((color >> 8) & 0xFF) * fog);
	b = (int)((color & 0xFF) * fog);
	return ((r << 16) | (g << 8) | b);
}

// Blend two colors by factor t (0.0 = c1, 1.0 = c2).
static int	lerp_color(int c1, int c2, float t)
{
	int	r;
	int	g;
	int	b;

	r = (int)(((c1 >> 16) & 0xFF) * (1 - t) + ((c2 >> 16) & 0xFF) * t);
	g = (int)(((c1 >> 8) & 0xFF) * (1 - t) + ((c2 >> 8) & 0xFF) * t);
	b = (int)((c1 & 0xFF) * (1 - t) + (c2 & 0xFF) * t);
	return ((r << 16) | (g << 8) | b);
}

// Bilinear texture sample: blend 4 nearest texels for smooth result.
// fx, fy are the floating-point texture coordinates (already scaled).
int	sample_tex_bilinear(t_tex *tex, float fx, float fy)
{
	int		x0;
	int		y0;
	int		x1;
	int		y1;
	float	frac_x;
	float	frac_y;
	int		stride;
	int		top;
	int		bot;

	stride = tex->line_len / 4;
	x0 = (int)fx;
	y0 = (int)fy;
	frac_x = fx - x0;
	frac_y = fy - y0;
	x0 = x0 & (tex->width - 1);
	y0 = y0 & (tex->height - 1);
	x1 = (x0 + 1) & (tex->width - 1);
	y1 = (y0 + 1) & (tex->height - 1);
	top = lerp_color(tex->addr[y0 * stride + x0],
			tex->addr[y0 * stride + x1], frac_x);
	bot = lerp_color(tex->addr[y1 * stride + x0],
			tex->addr[y1 * stride + x1], frac_x);
	return (lerp_color(top, bot, frac_y));
}

//Sample one pixel from the texture identified by ray->tex_id.
// Uses line_len to compute the correct stride (accounts for padding).

int	get_tex_color(t_game *game, t_ray *ray, int tex_x, int tex_y)
{
	int	stride;

	stride = game->tex[ray->tex_id].line_len / 4;
	return (game->tex[ray->tex_id].addr[tex_y * stride + tex_x]);
}
