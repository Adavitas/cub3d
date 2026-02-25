/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 17:38:19 by adavitas          #+#    #+#             */
/*   Updated: 2026/02/25 17:38:27 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Ported and adapted from Adavitas/so_long error_exit.
 *
 * so_long's version returned int (the result of mlx_destroy_display).
 * cub3d version calls free_game then exit(1) directly — the subject
 * requires the word "Error\n" on stderr followed by an explicit message.
 *
 * Usage pattern (mirrors main_testing.c style):
 *   if (some_check_fails)
 *       error_exit(&game, "Descriptive message");
 *
 *   Or inline in a return:
 *   return (error_exit(&game, "Map is not enclosed"), 1);
 *   (void cast is fine because error_exit never returns — it calls exit)
 */

#include "game.h"
#include <string.h>

/*
 * error_exit
 * 1. Writes "Error\n" to stderr (required by the cub3d subject).
 * 2. Writes the caller-supplied message + newline to stderr.
 * 3. Calls free_game to release all heap memory.
 * 4. Calls exit(1).
 *
 * Note: this function does NOT return.  Mark it __attribute__((noreturn))
 * if your compiler warns about control flow after the call.
 */
void	error_exit(t_game *game, char *message)
{
	write(2, "Error\n", 6);
	if (message)
	{
		write(2, message, strlen(message));
		write(2, "\n", 1);
	}
	free_game(game);
	exit(1);
}
