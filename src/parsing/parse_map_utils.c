/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzhyrgal <zzhyrgal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 15:36:44 by zzhyrgal          #+#    #+#             */
/*   Updated: 2026/02/22 20:00:42 by zzhyrgal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
//valid_map should not care about player's count;
int valid_map(char *line)
{
    int i;
    
    i = 0;
    while(line[i] && line[i] != '\n')
    {
        if(line[i] == '1' || line[i] == '0')
            ;
        else if(line[i] == ' ' || line[i] == '\t')
            ;
        else if(line[i] == 'N' || line[i] == 'S'
                        || line[i] == 'E' || line[i] =='W')
                        ;
        else
        {
            printf("unknown character in map line: '%c' (ASCII %d)\n", line[i], line[i]);
            return(1);
        }
        i++;
    }
    return(0);
}
t_node *new_node(char *line)
{
    t_node *node;
    int len;
    int i;
    
    node = malloc(sizeof(t_node));
    if(!node)
        return(NULL);

    // Find length without newline
    len = 0;
    while(line[len] && line[len] != '\n' && line[len] != '\r')
        len++;
    
    node->line = malloc(len + 1);
    if(!node->line)
    {
        free(node);
        return(NULL);
    }
    
    // Copy without newline
    i = 0;
    while(i < len)
    {
        node->line[i] = line[i];
        i++;
    }
    node->line[i] = '\0';
    
    node->next = NULL;
    return(node);
}

void add_back(t_node **head, t_node *new_node)
{
    t_node *temp;

    if(!head || !new_node)
        return;
    if(*head == NULL)
    {
        *head = new_node;
        return;
    }
    temp = *head;
    while(temp->next)
        temp = temp->next;
    temp->next = new_node;
}

void free_partial_grid(t_game *game, int rows_allocated)
{
   int i;
   
   i = 0;
   while(i < rows_allocated)
   {
      free(game->map.grid[i]);
      i++;
   }
   free(game->map.grid);
   game->map.grid = NULL;
}