/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzhyrgal <zzhyrgal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 15:31:30 by zzhyrgal          #+#    #+#             */
/*   Updated: 2026/03/10 16:17:30 by zzhyrgal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

char	*creating_new_str(char *line, int start, int end)
{
	int		new_size;
	char	*new_str;
	int		j;

	new_size = end - start + 1;
	new_str = malloc(sizeof(char) * (new_size + 1));
	if (!new_str)
		return (NULL);
	j = 0;
	while (j < new_size)
	{
		new_str[j] = line[start];
		start++;
		j++;
	}
	new_str[j] = '\0';
	return (new_str);
}

char	*delete_white_spaces(char *line)
{
	char	*new_str;
	int		i;
	int		start;

	i = 0;
	if (!line)
		return (NULL);
	while (line[i] && isspace(line[i]))
		i++;
	start = i;
	if (line[start] == '\0')
		return (ft_strdup(""));
	i = ft_strlen(line) - 1;
	while (line[i] && isspace(line[i]))
		i--;
	new_str = creating_new_str(line, start, i);
	if (!new_str)
		return (NULL);
	return (new_str);
}

int	comma_count(const char *str)
{
	int	i;
	int	comma_count;

	i = 0;
	comma_count = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (str[i] == ',')
			comma_count++;
		i++;
	}
	return (comma_count);
}

int	col_len_arr(char **parts)
{
	int	i;

	i = 0;
	while (parts[i])
		i++;
	return (i);
}

int	checking_functions(char **parts)
{
	if (!parts || col_len_arr(parts) != 3)
		return (1);
	if (normalize_parts(parts) == 1)
		return (1);
	return (0);
}
