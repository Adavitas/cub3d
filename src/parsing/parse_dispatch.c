/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dispatch.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzhyrgal <zzhyrgal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 16:00:00 by zzhyrgal          #+#    #+#             */
/*   Updated: 2026/03/10 16:10:22 by zzhyrgal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	helper_dispatch_two(char *line, t_game *game, t_node **raw_map)
{
	if (valid_map(line) == 1)
		return (1);
	if (reading_raw_map(line, game, raw_map))
		return (1);
	return (0);
}

int	helper_dispatch(char *line, t_game *game, t_node **raw_map)
{
	if (valid_map(line) == 0)
	{
		game->map_started = true;
		if (reading_raw_map(line, game, raw_map))
			return (1);
		return (0);
	}
	else
	{
		printf("Map validation failed.\n");
		return (1);
	}
	return (0);
}

int	dispatch_line(char *line, t_game *game, t_node **raw_map)
{
	int	i;

	i = 0;
	while (isspace(line[i]))
		i++;
	if (order(game) != 0)
	{
		if (select_parse(&line[i], game) == 0)
			return (0);
		else
			return (1);
	}
	if (!game->map_started)
	{
		if (helper_dispatch(line, game, raw_map))
			return (1);
		return (0);
	}
	if (game->map_started)
	{
		if (helper_dispatch_two(line, game, raw_map))
			return (1);
		return (0);
	}
	return (0);
}
