/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 01:33:05 by adavitas          #+#    #+#             */
/*   Updated: 2026/03/12 20:25:03 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

/*
** close_game — hooked to the window's red-X button (event 17)
** and optionally to the ESC key.
** Destroys all MLX resources in reverse order of creation,
** frees parsed game data, then exits cleanly.
*/
int	close_game(t_game *game)
{
	destroy_mlx_resources(game);
	free_game(game);
	exit(0);
}
