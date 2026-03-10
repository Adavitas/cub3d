/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzhyrgal <zzhyrgal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 18:47:31 by zzhyrgal          #+#    #+#             */
/*   Updated: 2026/03/10 16:14:21 by zzhyrgal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

char	*trim_white_spaces(char *line)
{
	char	*start;
	char	*end;

	if (!line)
		return (NULL);
	while (*line && isspace(*line))
		line++;
	if (*line == '\0')
		return (line);
	start = line;
	end = line;
	while (*end)
		end++;
	end--;
	while (end > start && isspace(*end))
		end--;
	*(end + 1) = '\0';
	return (start);
}

int	check_spaces_path(char *path)
{
	int	i;

	if (!path)
		return (1);
	i = 0;
	while (path[i])
	{
		if (isspace(path[i]))
			return (1);
		i++;
	}
	if (path[i] == '\0')
		return (0);
	return (1);
}

int	extension_check(char *path)
{
	int	i;

	if (!path)
		return (1);
	i = 0;
	while (path[i])
		i++;
	if (i < 4)
		return (1);
	if (path[i - 4] == '.'
		&& path[i - 3] == 'x'
		&& path[i - 2] == 'p'
		&& path[i - 1] == 'm')
		return (0);
	return (1);
}
