/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 16:32:01 by zzhyrgal          #+#    #+#             */
/*   Updated: 2026/02/25 19:26:31 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PLAYER_H
# define PLAYER_H
# define M_SPEED 0.05
# define ROTATE_SPEED 0.03
# define PLAYER_RADIUS 0.2
# define W  119
# define S  115
# define A  97
# define D  100
# define left   113
# define right  114
// # define up     111//arrows
// # define down   116//arrows

typedef struct s_key
{
    int w;
    int a;
    int s;
    int d;
    int LEFT;
    int RIGHT;
}   t_key;

typedef struct s_player
{
    int player_count;
    char p_orientation;
    float x; // x-coordinate (column position in map, horizontal)
    float y; // y-coordinate (row position in map, vertical)
    float dir_x;//direction vector x(where player is facing);
    float dir_y;//direction vector y;
    float plane_x;//camera plane x;
    float plane_y;//camera plane y;
}   t_player;

// Player setup function
void set_up_dir_plane(t_player *player);

#endif