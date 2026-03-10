/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 14:34:16 by adavitas          #+#    #+#             */
/*   Updated: 2026/03/10 00:37:46 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

/*
** Pack R, G, B values (0-255 each) into a single 0xRRGGBB int
** for writing into the image buffer.
*/
int	rgb_to_int(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

/*
** Apply distance fog: darken a color based on distance.
** fog_factor 1.0 = full brightness, 0.0 = black.
*/
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
	r = (int)(((color >> 16) & 255) * fog);
	g = (int)(((color >> 8) & 255) * fog);
	b = (int)((color & 255) * fog);
	return ((r << 16) | (g << 8) | b);
}

/* Blend two colors by factor t (0.0 = c1, 1.0 = c2). */
static int	lerp_color(int c1, int c2, float t)
{
	int	r;
	int	g;
	int	b;

	r = (int)(((c1 >> 16) & 255) * (1 - t) + ((c2 >> 16) & 255) * t);
	g = (int)(((c1 >> 8) & 255) * (1 - t) + ((c2 >> 8) & 255) * t);
	b = (int)((c1 & 255) * (1 - t) + (c2 & 255) * t);
	return ((r << 16) | (g << 8) | b);
}

/*
** Bilinear texture sample: blend 4 nearest texels for smooth result.
** fx, fy are the floating-point texture coordinates (already scaled).
*/
int	sample_tex_bilinear(t_tex *tex, float fx, float fy)
{
	int		c[4];
	float	frac[2];
	int		stride;
	int		top;
	int		bot;

	stride = tex->line_len / 4;
	c[0] = (int)fx & (tex->width - 1);
	c[1] = (int)fy & (tex->height - 1);
	frac[0] = fx - (int)fx;
	frac[1] = fy - (int)fy;
	c[2] = (c[0] + 1) & (tex->width - 1);
	c[3] = (c[1] + 1) & (tex->height - 1);
	top = lerp_color(tex->addr[c[1] * stride + c[0]],
			tex->addr[c[1] * stride + c[2]], frac[0]);
	bot = lerp_color(tex->addr[c[3] * stride + c[0]],
			tex->addr[c[3] * stride + c[2]], frac[0]);
	return (lerp_color(top, bot, frac[1]));
}

/*
** Sample one pixel from the texture identified by ray->tex_id.
** Uses line_len to compute the correct stride (accounts for padding).
*/
int	get_tex_color(t_game *game, t_ray *ray, int tex_x, int tex_y)
{
	int	stride;

	stride = game->tex[ray->tex_id].line_len / 4;
	return (game->tex[ray->tex_id].addr[tex_y * stride + tex_x]);
}
