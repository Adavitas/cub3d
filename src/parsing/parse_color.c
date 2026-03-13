/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 17:34:15 by zzhyrgal          #+#    #+#             */
/*   Updated: 2026/03/13 13:20:11 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	free_parts(char **parts)
{
	int	i;

	i = 0;
	while (parts[i])
	{
		free(parts[i]);
		i++;
	}
	free(parts);
}

static int	convert_to_num_check_range(char **parts, t_color *object)
{
	object->r = ft_atoi(parts[0]);
	if (object->r < 0 || object->r > 255)
		return (1);
	object->g = ft_atoi(parts[1]);
	if (object->g < 0 || object->g > 255)
		return (1);
	object->b = ft_atoi(parts[2]);
	if (object->b < 0 || object->b > 255)
		return (1);
	return (0);
}

static char	*extract_rgb_string(char *line)
{
	int	i;

	i = 0;
	while (line[i] && !ft_isspace(line[i]))
		i++;
	while (line[i] && ft_isspace(line[i]))
		i++;
	return (delete_white_spaces(&line[i]));
}

static int	validate_and_split(char *rgb_str, char ***parts)
{
	if (rgb_str == NULL || comma_count(rgb_str) != 2)
	{
		free(rgb_str);
		return (printf("debug msg: color parsing failed.\n"), 1);
	}
	*parts = ft_split(rgb_str, ',');
	free(rgb_str);
	return (0);
}

int	parse_color(char *line, t_color *object)
{
	char	**parts;
	char	*rgb_str;

	if (object->is_set)
		return (1);
	rgb_str = extract_rgb_string(line);
	if (validate_and_split(rgb_str, &parts))
		return (1);
	if (checking_functions(parts))
	{
		free_parts(parts);
		printf("color parsing failed on some checks.\n");
		return (1);
	}
	if (convert_to_num_check_range(parts, object) == 1)
	{
		free_parts(parts);
		return (1);
	}
	free_parts(parts);
	object->is_set = true;
	return (0);
}
