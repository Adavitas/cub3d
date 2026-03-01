/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 14:34:16 by adavitas          #+#    #+#             */
/*   Updated: 2026/03/01 22:38:05 by adavitas         ###   ########.fr       */
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
// pixel_index = tex_y * TEX_W + tex_x (precomputed by caller).

int	get_tex_color(t_game *game, t_ray *ray, int pixel_index)
{
	return (game->tex[ray->tex_id].addr[pixel_index]);
}
