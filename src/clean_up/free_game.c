/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 17:33:13 by zzhyrgal          #+#    #+#             */
/*   Updated: 2026/03/12 20:25:03 by adavitas         ###   ########.fr       */
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

	if (!map)
		return ;
	if (map->door_open)
	{
		i = 0;
		while (i < map->height)
		{
			free(map->door_open[i]);
			i++;
		}
		free(map->door_open);
		map->door_open = NULL;
	}
	if (!map->grid)
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
