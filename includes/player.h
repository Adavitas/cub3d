/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 16:32:01 by zzhyrgal          #+#    #+#             */
/*   Updated: 2026/02/25 18:23:28 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PLAYER_H
# define PLAYER_H
# include <stdbool.h>

typedef struct s_player
{
    // -- parser fills these --
    int     x;       // tile col
    int     y;       // tile row
    char    dir;     // 'N' 'S' 'E' 'W'
    bool    is_set;

    // -- init_player() derives these from dir --
    double  pos_x;   // exact world position (e.g. 22.5)
    double  pos_y;
    double  dir_x;   // unit direction vector (lodev: dirX/dirY)
    double  dir_y;
    double  plane_x; // camera plane perpendicular to dir (lodev: planeX/planeY)
    double  plane_y; // length 0.66 → 66° FOV
}   t_player;

#endif