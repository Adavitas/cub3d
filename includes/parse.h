/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 13:06:42 by zzhyrgal          #+#    #+#             */
/*   Updated: 2026/03/12 20:25:03 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# include <stdbool.h>

typedef struct s_map
{
	char	**grid;
	bool	**door_open;
	int		width;
	int		height;
	int		raw_max_width;
}	t_map;

typedef struct s_node
{
	char			*line;
	struct s_node	*next;
}	t_node;

typedef enum e_color_id
{
	COLOR_FLOOR,
	COLOR_CEILING,
	COLOR_UNKNOWN
}	t_color_id;

typedef enum e_text_id
{
	TEX_NO = 0,
	TEX_SO = 1,
	TEX_WE = 2,
	TEX_EA = 3,
	TEX_FLOOR = 4,
	TEX_SKY = 5,
	TEX_DOOR = 6,
	TEX_UNKNOWN = 7
}	t_text_id;

typedef struct s_tex
{
	char	*path;
	bool	is_set;
	void	*img;
	int		*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}	t_tex;

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
	bool	is_set;
}	t_color;

typedef struct s_game	t_game;

int				parse(const char *file, t_game *game);
int				parse_texture(char *line, t_tex *tex, t_text_id tex_id);
int				check_spaces_path(char *path);
int				extension_check(char *path);
char			*trim_white_spaces(char *line);
int				parse_color(char *line, t_color *object);
char			*delete_white_spaces(char *line);
int				comma_count(const char *str);
int				checking_functions(char **parts);
int				col_len_arr(char **parts);
int				find_start(char *parts);
int				find_end(char *parts);
int				shift_memory(char *parts, int start, int end);
int				normalize_parts(char **parts);
int				parse_map(t_game *game, t_node *raw_map);
int				parse_row(t_game *game, t_node *node, int i);
void			check_player_position(t_game *game, char c, int row, int col);
void			fill_void_spaces(char *row, int start, int max_width);
int				valid_map(char *line);
int				reading_raw_map(char *line, t_game *game, t_node **raw_map);
t_node			*new_node(char *line);
void			add_back(t_node **head, t_node *new_node);
void			free_partial_grid(t_game *game, int rows_allocated);
int				order(t_game *game);
int				select_parse(char *line, t_game *game);
char			*creating_new_str(char *line, int start, int end);
int				dispatch_line(char *line, t_game *game, t_node **raw_map);
t_color_id		get_color_id(char *line);
t_text_id		get_tex_id(char *line);
int				is_wall_tile(char c);
t_text_id		get_wall_tex_id(char c);
int				post_validation(t_game *game);
int				validate_chars(t_map *map);
int				validate_player(t_game *game);
int				validate_map(t_game *game);
int				flood_fill(char **map_copy, int x, int y, int height);
char			**copy_map(t_map *map);
void			free_map_copy(char **map, int height);
int				cub_file_check(char *filename);
int				is_empty(char *line);
void			init_game(t_game *game);
void			free_game(t_game *game);
void			free_map(t_map *map);
void			free_tex(t_tex *tex);
void			free_list_maplines(t_node **head);
char			*get_next_line(int fd);
#endif
