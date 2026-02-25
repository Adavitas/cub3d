/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzhyrgal <zzhyrgal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 12:46:13 by zzhyrgal          #+#    #+#             */
/*   Updated: 2026/02/22 21:54:43 by zzhyrgal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef GAME_H
# define GAME_H
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <ctype.h>
# include "libft.h"
# include <parse.h>
# include <player.h>
# include <stdbool.h>
# include <math.h>

typedef struct s_game
{
    //Jibek's variables
    t_map map; //2d map layout; not a pointer;
    t_tex tex[4]; //wall appearance info; not a pointer;
    t_color  floor; //floor appearance; not a pointer;
    t_color ceiling; //ceiling appearance; not a pointer;
    bool map_started;//for tracking map parsing;
    t_player  player;//not a pointer//runtime player state(position, state);
    t_key key; //runtime input state updates
    
    //Leqso's variables
    void *mlx;
    void *win;
}   t_game;

//only directly game related functions here;
void ft_bzero(void *s, size_t n);
void init_game(t_game *game);
void initialize_player(t_player *player);

#endif