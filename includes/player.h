/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 16:32:01 by zzhyrgal          #+#    #+#             */
/*   Updated: 2026/03/12 20:25:03 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H
# define M_SPEED 0.02
# define ROTATE_SPEED 0.02
# define PLAYER_RADIUS 0.2
# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_R 114
# define KEY_F 102
# define DOOR_RANGE 1.5f

typedef struct s_key
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}	t_key;

typedef struct s_player
{
	int		player_count;
	char	p_orientation;
	float	x;
	float	y;
	float	dir_x;
	float	dir_y;
	float	plane_x;
	float	plane_y;
}	t_player;

typedef struct s_game	t_game;

void	set_up_dir_plane(t_player *player);
int		move_player(t_game *game, float newx, float newy);
void	update_player(t_game *game);
void	rotate_player(t_game *game, float angle);
void	rotate_left(t_game *game);
void	rotate_right(t_game *game);
int		check_collusion(float new_x, float new_y, t_game *game);
int		key_press(int key, t_game *game);
int		key_release(int key, t_game *game);
int		mouse_toggle(int button, int x, int y, t_game *game);
void	mouse_rotate(t_game *game);
void	toggle_door(t_game *game);
void	toggle_wand(t_game *game);
void	update_wand(t_game *game);

#endif
