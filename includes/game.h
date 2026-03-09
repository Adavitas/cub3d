/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 12:46:13 by zzhyrgal          #+#    #+#             */
/*   Updated: 2026/03/02 15:03:29 by adavitas         ###   ########.fr       */
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
# include <stdbool.h>
# include <math.h>
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif
# include "mlx.h"
# include "libft.h"
# include "parse.h"
# include "player.h"
# include "raycast.h"

# define WIN_W 1280
# define WIN_H 720
# define TEX_W 64
# define TEX_H 64

// Off-screen pixel buffer written to every frame
typedef struct s_img
{
    void    *img;
    int     *addr;      // addr[y * WIN_W + x] = 0xRRGGBB
    int     bpp;
    int     line_len;
    int     endian;
}   t_img;

typedef struct s_game
{
    //Jibek's variables
    t_map       map;        // 2d map layout
    t_tex       tex[6];     // NO SO WE EA + floor + sky
    t_color     floor;      // floor colour
    t_color     ceiling;    // ceiling colour
    bool        map_started;
    t_player    player;     // runtime player state
    t_key       key;        // runtime input state

    //Leqso's variables
    void        *mlx;
    void        *win;
    t_img       screen;     // single image drawn each frame
}   t_game;

// Init / cleanup
void    init_game(t_game *game);
void    initialize_player(t_player *player);
int     init_mlx(t_game *game);
int     close_game(t_game *game);

#endif