/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzhyrgal <zzhyrgal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 17:02:23 by zzhyrgal          #+#    #+#             */
/*   Updated: 2026/02/22 20:39:15 by zzhyrgal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
//padding is happening here->
void fill_void_spaces(char *row, int start, int max_width)
{
   while (start < max_width)
    {
        row[start] = ' ';
        start++;
    }
    row[start] = '\0';
}
//player position is stored here!
void check_player_position(t_game *game, char c, int row, int col)
{
   if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
   {
      game->player.player_count++;
      game->player.x = (float)col + 0.5; // x is column, centered in tile
      game->player.y = (float)row + 0.5; // y is row, centered in tile
      game->player.p_orientation = c;
   }
}

int parse_row(t_game *game, t_node *node, int i)
{
   int j;
   int len;

   len = strlen(node->line);
   game->map.grid[i] = malloc(sizeof(char) * (game->map.raw_max_width + 1));
   if(!game->map.grid[i])
      return(1);
   j = 0;
   while(j < len)
   {
      game->map.grid[i][j] = node->line[j];
      check_player_position(game, node->line[j], i, j); // pass row, col
      if (node->line[j] == 'N' || node->line[j] == 'S' ||
                node->line[j] == 'E' || node->line[j] == 'W')
                game->map.grid[i][j] = '0';//player is not a part of map//we only have coordinates
      j++;
   }
   fill_void_spaces(game->map.grid[i], j, game->map.raw_max_width);
   return(0);
}
//take the longest row and pad shorter ones with spaces;
int reading_raw_map(char *line, t_game *game, t_node **raw_map)
{
    int i;
    int line_len;
    t_node *node;
    
    i = 0;
    line_len = 0;
    while(line[i] && line[i] != '\n')
        i++;
    
    line_len = i;
    if(line_len > game->map.raw_max_width)//keeping track of the columns;
        game->map.raw_max_width = line_len;
    game->map.height += 1;//number of rows;
    node = new_node(line);
    if(!node)
        return(1);
    add_back(raw_map, node);
    return(0);
}

int parse_map(t_game *game, t_node *raw_map)
{
   t_node *node;
   int i;
   
   node = raw_map;
   game->map.grid = malloc(sizeof(char *) * (game->map.height + 1)); // +1 for NULL
   if(!game->map.grid)
      return(1);
   i = 0;
   while(node)
   {
      if(parse_row(game, node, i))
      {
         free_partial_grid(game, i);
         return(1);
      }
      node = node->next;
      i++;
   }
   game->map.grid[i] = NULL; // NULL terminate
   if(game->player.player_count != 1)
   {
      printf("more than one player\n");
      return(1);  // Caller will handle cleanup via free_game()
   }
   return(0);
}

/*
read line
   ↓
validate line
   ↓
store line in temp array
   ↓
after reading all map lines:
    calculate height
    calculate max width
    allocate grid[height][width]
    copy lines
*/