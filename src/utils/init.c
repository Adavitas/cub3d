/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 16:21:40 by zzhyrgal          #+#    #+#             */
/*   Updated: 2026/02/25 18:16:13 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
//bzero only modifies already-existing memory;
//A pointer with all bits set to zero is guaranteed 
                            //to be a NULL pointer.
//Uninitialized memory contains garbage.

// memset zeroes every byte → all pointers become NULL, all ints 0,
// all bools false. No need to set fields individually afterwards.
// Answering your question: setting a freed pointer to NULL before a
// second free() call IS safe — free(NULL) is a no-op by the C standard.
void init_game(t_game *game)
{
    memset(game, 0, sizeof(t_game));
}