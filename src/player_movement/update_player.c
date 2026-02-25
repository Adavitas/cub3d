/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzhyrgal <zzhyrgal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 00:24:30 by zzhyrgal          #+#    #+#             */
/*   Updated: 2026/02/22 21:55:58 by zzhyrgal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void update_player(t_game *game)
{
    if(game->key.w)//if there is collusion, nothing happens;
        move_player(game, game->player.dir_x * M_SPEED, 
                            game->player.dir_y * M_SPEED);
    if(game->key.s)
        move_player(game, -game->player.dir_x * M_SPEED,
                            -game->player.dir_y * M_SPEED);
    if(game->key.a)
        move_player(game, -game->player.dir_y * M_SPEED,
                            game->player.dir_x * M_SPEED);
    if(game->key.d)
        move_player(game, game->player.dir_y * M_SPEED,
                            -game->player.dir_x * M_SPEED);
    if(game->key.LEFT)
        rotate_left(game);
    if(game->key.RIGHT)
        rotate_right(game);
}

int key_press(int key, t_key *key_)
{
    switch(key)
    {
        case W:
            key_->w = 1;
            break;
        case S:
            key_->s = 1;
            break;
        case A:
            key_->a = 1;
            break;
        case D:
            key_->d = 1;
            break;
        case left:
            key_->LEFT = 1;
            break;
        case right:
            key_->RIGHT = 1;
            break;
    }
    return(0);
}
int key_release(int key, t_key *key_)
{
    switch(key)
    {
        case W:
            key_->w = 0;
            break;
        case S:
            key_->s = 0;
            break;
        case A:
            key_->a = 0;
            break;
        case D:
            key_->d = 0;
            break;
        case left:
            key_->LEFT = 0;
            break;
        case right:
            key_->RIGHT = 0;
            break;
    }
    return(0);
}
