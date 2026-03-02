/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 14:34:16 by adavitas          #+#    #+#             */
/*   Updated: 2026/03/02 04:57:47 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "game.h"

// Pack R, G, B values (0–255 each) into a single 0xRRGGBB int
// for writing into the image buffer.
int	rgb_to_int(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}


//Sample one pixel from the texture identified by ray->tex_id.
// Uses line_len to compute the correct stride (accounts for padding).

int	get_tex_color(t_game *game, t_ray *ray, int tex_x, int tex_y)
{
	int	stride;

	stride = game->tex[ray->tex_id].line_len / 4;
	return (game->tex[ray->tex_id].addr[tex_y * stride + tex_x]);
}
