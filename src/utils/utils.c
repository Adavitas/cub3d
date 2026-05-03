/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 16:38:28 by zzhyrgal          #+#    #+#             */
/*   Updated: 2026/03/12 15:32:09 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	cub_file_check(char *filename)
{
	int	len;

	if (!filename)
		return (0);
	len = strlen(filename);
	if (len <= 4)
		return (0);
	if (filename[len - 4] == '.'
		&& filename[len - 3] == 'c'
		&& filename[len - 2] == 'u'
		&& filename[len - 1] == 'b')
		return (1);
	return (0);
}

int	is_empty(char *line)
{
	int	i;

	if (!line)
		return (1);
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t'
			&& line[i] != '\n' && line[i] != '\r')
			return (0);
		i++;
	}
	return (1);
}

int	is_wall_tile(char c)
{
	return (c == '1' || c == '2' || c == '3' || c == '4');
}

t_text_id	get_wall_tex_id(char c)
{
	if (c == '1')
		return (TEX_NO);
	if (c == '2')
		return (TEX_SO);
	if (c == '3')
		return (TEX_WE);
	if (c == '4')
		return (TEX_EA);
	if (c == 'D')
		return (TEX_DOOR);
	return (TEX_UNKNOWN);
}
