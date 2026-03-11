/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_rotate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:46:24 by adavitas          #+#    #+#             */
/*   Updated: 2026/03/11 16:55:16 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

/*
** mouse_toggle — called on mouse button press (X11 event 4).
** Left click (button 1) toggles mouselook mode on/off.
** When active: cursor is hidden and warped to window center.
** When inactive: cursor is shown again.
*/
int	mouse_toggle(int button, int x, int y, t_game *game)
{
	(void)x;
	(void)y;
	if (button != 1)
		return (0);
	game->mouse_active = !game->mouse_active;
	if (game->mouse_active)
	{
		mlx_mouse_hide(game->mlx, game->win);
		mlx_mouse_move(game->mlx, game->win, WIN_W / 2, WIN_H / 2);
	}
	else
		mlx_mouse_show(game->mlx, game->win);
	return (0);
}

/*
** mouse_rotate — called every frame from game_loop.
** Reads current mouse position, computes horizontal delta from
** the window center, applies rotation proportional to the delta,
** then re-centers the cursor so the next frame gets a fresh delta.
** Does nothing when mouselook is inactive.
*/
void	mouse_rotate(t_game *game)
{
	int		mouse_x;
	int		mouse_y;
	int		delta_x;

	if (!game->mouse_active)
		return ;
	mlx_mouse_get_pos(game->mlx, game->win, &mouse_x, &mouse_y);
	delta_x = mouse_x - WIN_W / 2;
	if (delta_x == 0)
		return ;
	rotate_player(game, delta_x * MOUSE_SENS);
	mlx_mouse_move(game->mlx, game->win, WIN_W / 2, WIN_H / 2);
	mlx_do_sync(game->mlx);
}
