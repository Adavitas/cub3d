/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 17:38:55 by adavitas          #+#    #+#             */
/*   Updated: 2026/02/25 17:38:57 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# ifndef DISPLAY_H
# define DISPLAY_H

/* ── Convenience unsigned int alias (ported from so_long) ──── */
typedef unsigned int	t_u32;

/* ── 2D integer point (replaces loose x/y pairs) ───────────── */
typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

/*
 * t_display — bundles mlx connection + window into one struct.
 * In t_game (game.h) you currently have loose:
 *   void *mlx;
 *   void *win;
 * You can replace those two fields with:
 *   t_display display;
 * and access them as game.display.mlx_ptr / game.display.window
 */
typedef struct s_display
{
	void	*mlx_ptr;
	void	*window;
}	t_display;

#endif
