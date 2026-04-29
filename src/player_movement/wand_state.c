/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wand_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 12:00:00 by adavitas          #+#    #+#             */
/*   Updated: 2026/04/29 12:00:00 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	toggle_wand(t_game *game)
{
	if (game->wand.state == WAND_OFF)
	{
		game->wand.state = WAND_TURNING_ON;
		game->wand.frame_id = WAND_FRAME_TURN_1;
		game->wand.anim_tick = 0;
	}
	else if (game->wand.state == WAND_ON)
	{
		game->wand.state = WAND_TURNING_OFF;
		game->wand.frame_id = WAND_FRAME_TURN_3;
		game->wand.anim_tick = 0;
	}
}

static void	update_wand_bob(t_game *game)
{
	float	dx;
	float	dy;
	float	dist;

	dx = game->player.x - game->wand.last_x;
	dy = game->player.y - game->wand.last_y;
	dist = sqrtf(dx * dx + dy * dy);
	game->wand.last_x = game->player.x;
	game->wand.last_y = game->player.y;
	if (dist > WAND_MOVE_EPSILON)
	{
		game->wand.phase += dist * WAND_BOB_SPEED;
		game->wand.bob_x = sinf(game->wand.phase) * WAND_BOB_X;
		game->wand.bob_y = fabsf(cosf(game->wand.phase)) * WAND_BOB_Y;
	}
	else
	{
		game->wand.bob_x *= WAND_BOB_RETURN;
		game->wand.bob_y *= WAND_BOB_RETURN;
	}
}

static void	update_wand_on(t_wand *wand)
{
	wand->anim_tick++;
	if (wand->anim_tick < WAND_FLICKER_TICKS)
		return ;
	wand->anim_tick = 0;
	if (wand->frame_id == WAND_FRAME_ON_A)
		wand->frame_id = WAND_FRAME_ON_B;
	else
		wand->frame_id = WAND_FRAME_ON_A;
}

static void	update_wand_turn(t_wand *wand)
{
	wand->anim_tick++;
	if (wand->anim_tick < WAND_TURN_TICKS)
		return ;
	wand->anim_tick = 0;
	if (wand->state == WAND_TURNING_ON
		&& wand->frame_id < WAND_FRAME_TURN_3)
		wand->frame_id++;
	else if (wand->state == WAND_TURNING_ON)
	{
		wand->state = WAND_ON;
		wand->frame_id = WAND_FRAME_ON_A;
	}
	else if (wand->state == WAND_TURNING_OFF
		&& wand->frame_id > WAND_FRAME_TURN_1)
		wand->frame_id--;
	else if (wand->state == WAND_TURNING_OFF)
	{
		wand->state = WAND_OFF;
		wand->frame_id = WAND_FRAME_OFF;
	}
}

void	update_wand(t_game *game)
{
	update_wand_bob(game);
	if (game->wand.state == WAND_ON)
		update_wand_on(&game->wand);
	else if (game->wand.state == WAND_TURNING_ON
		|| game->wand.state == WAND_TURNING_OFF)
		update_wand_turn(&game->wand);
}
