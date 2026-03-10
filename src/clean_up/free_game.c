/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzhyrgal <zzhyrgal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 17:33:13 by zzhyrgal          #+#    #+#             */
/*   Updated: 2026/03/10 15:45:22 by zzhyrgal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	free_game(t_game *game)
{
	if (!game)
		return ;
	free_tex(game->tex);
	free_map(&game->map);
}

void	free_map(t_map *map)
{
	int	i;

	if (!map || !map->grid)
		return ;
	i = 0;
	while (i < map->height)
	{
		free(map->grid[i]);
		i++;
	}
	free(map->grid);
	map->grid = NULL;
}

void	free_tex(t_tex *tex)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		if (tex[i].path != NULL)
		{
			free(tex[i].path);
			tex[i].path = NULL;
		}
		i++;
	}
}

void	free_list_maplines(t_node **head)
{
	t_node	*temp;

	if (!head || !(*head))
		return ;
	while (*head)
	{
		temp = *head;
		*head = (*head)->next;
		free(temp->line);
		free(temp);
	}
	*head = NULL;
}
