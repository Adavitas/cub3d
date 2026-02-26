/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzhyrgal <zzhyrgal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 17:29:07 by zzhyrgal          #+#    #+#             */
/*   Updated: 2025/08/15 23:54:34 by zzhyrgal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*save_leftover(char *str)
{
	int		i;
	char	*keep;
	char	*found_newline;

	found_newline = ft_strsearch(str, '\n');
	if (!found_newline)
	{
		free(str);
		return (NULL);
	}
	i = (found_newline - str) + 1;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	keep = ft_strdup(&str[i]);
	free(str);
	return (keep);
}

char	*extract_line(char *str)
{
	int		i;
	int		len;
	char	*return_line;

	if (!str || !*str)
		return (NULL);
	len = len_count(str);
	return_line = malloc(len + 1);
	if (!return_line)
		return (NULL);
	i = 0;
	while (i < len)
	{
		return_line[i] = str[i];
		i++;
	}
	return_line[i] = '\0';
	return (return_line);
}

char	*read_until_newline(int fd, char **leftover, int *bytes_read)
{
	char	*line;
	char	*buffer;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	*bytes_read = 1;
	while (*bytes_read > 0)
	{
		*bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (*bytes_read > 0)
		{
			buffer[*bytes_read] = '\0';
			*leftover = ft_append(*leftover, buffer);
			if (ft_strsearch(*leftover, '\n'))
			{
				line = extract_line(*leftover);
				*leftover = save_leftover(*leftover);
				free(buffer);
				return (line);
			}
		}
	}
	free(buffer);
	return (NULL);
}

char	*handle_eof_error(int bytes_read, char **leftover)
{
	char	*line;

	if (bytes_read == -1)
	{
		if (*leftover)
		{
			free(*leftover);
			*leftover = NULL;
			return (NULL);
		}
		return (NULL);
	}
	if (bytes_read == 0 && *leftover && **leftover)
	{
		line = extract_line(*leftover);
		free(*leftover);
		*leftover = (NULL);
		return (line);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*leftover;
	char		*line;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (leftover && ft_strsearch(leftover, '\n'))
	{
		line = extract_line(leftover);
		leftover = save_leftover(leftover);
		return (line);
	}
	bytes_read = 1;
	while (bytes_read > 0)
	{
		line = read_until_newline(fd, &leftover, &bytes_read);
		if (line)
			return (line);
	}
	return (handle_eof_error(bytes_read, &leftover));
}
