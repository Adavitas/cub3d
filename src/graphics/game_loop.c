/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 04:11:44 by adavitas          #+#    #+#             */
/*   Updated: 2026/03/02 04:11:48 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "game.h"

/*
** game_loop — called every frame by mlx_loop_hook.
**  1) Process held-down keys (movement + rotation).
**  2) Cast rays and render the 3D view into the off-screen buffer.
** Returns 0 to satisfy mlx callback signature.
*/
int	game_loop(t_game *game)
{
	update_player(game);
	render_frame(game);
	return (0);
}
