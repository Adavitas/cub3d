/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 12:46:13 by zzhyrgal          #+#    #+#             */
/*   Updated: 2026/02/25 18:23:04 by adavitas         ###   ########.fr       */
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
# include "map.h"
# include "player.h"

# define SCREEN_W   1280
# define SCREEN_H   720
# define TEX_W      64
# define TEX_H      64

//Central State Struct
//Game_state owns the map: parse create the map;
//If memory lives longer than the function call, 
        //it must belong to a struct outside that function.
//We have ONE STRUCT that represents the whole program.
typedef enum e_state
{
    INSIDE_NUM,
    EXPECT_DIGIT,
    EXPECT_DIGIT_AFTER_COMMA
}   t_state;

typedef enum e_color_id
{
    COLOR_FLOOR,
    COLOR_CEILING,
    COLOR_UNKNOWN
}   t_color_id;

typedef enum e_text_id
{
    TEX_NO = 0,
    TEX_SO = 1,
    TEX_WE = 2,
    TEX_EA = 3,
    TEX_UNKNOWN = 4
}   t_text_id;

typedef struct s_tex
{
    //parser part:
    char *path;
    bool is_set; //parsing state;
    //graphics part:
    void *img;
    int *addr;
    int bpp;
    int line_len;
    int endian;
}   t_tex;

typedef struct s_color
{
    //RBG
    int r;//no need to be cleaned up;
    int g;
    int b;
    bool is_set;
    // bool r_set;
    // bool g_set;
    // bool b_set;
}   t_color;

typedef struct s_game
{
    //Jibek's variables
    t_map map; //2d map layout; not a pointer;
    t_player  player;//not a pointer//runtime player state(position, state);
    t_tex tex[4]; //wall appearance info; not a pointer;
    t_color  floor; //floor appearance; not a pointer;
    t_color ceiling; //ceiling appearance; not a pointer;
    bool map_started;
    //Leqso's variables
    void *mlx;
    void *win;
    int rbg;
    char *id;//not sure what it is?
}   t_game;

void ft_bzero(void *s, size_t n);

//Ownership Rules: this is Architecture;
    //Do parse functions mutate GAME STATE or RETURN DATA?
    //The struct that owns memory is responsible for freeing it;
//Parsing Architecture(SINGLE vs STAGED):
    //Staged Parsing: only does ONE thing; sets flags when successful;
//Validation layer: totally separate;
//ERROR handling strategy:
    //Do functions return int error codes?
    //Or do they call exit() directly?
    //Do you clean up before exiting?
    //free_game in one place if error;

#endif