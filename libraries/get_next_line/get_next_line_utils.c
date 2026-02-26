/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zzhyrgal <zzhyrgal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 17:29:04 by zzhyrgal          #+#    #+#             */
/*   Updated: 2025/08/15 19:43:24 by zzhyrgal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char const *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i] != '\0')
	{
		i++;
		len++;
	}
	return (len);
}

char	*ft_strsearch(char const *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
			return ((char *)&str[i]);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&str[i]);
	return (NULL);
}

char	*ft_strdup(char *s)
{
	int		len;
	char	*new;
	int		i;

	len = ft_strlen(s);
	new = malloc(len + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (s[i])
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*ft_append(char *s1, char *s2)
{
	char	*s3;
	char	*temp;
	char	*to_free;

	if (!s1)
		s1 = ft_strdup("");
	if (!s1 || !s2)
		return (NULL);
	to_free = s1;
	s3 = malloc((ft_strlen(s1)) + (ft_strlen(s2)) + 1);
	if (!s3)
	{
		free(s1);
		return (NULL);
	}
	temp = s3;
	while (*s1)
		*temp++ = *s1++;
	while (*s2)
		*temp++ = *s2++;
	*temp = '\0';
	free(to_free);
	return (s3);
}

int	len_count(char *str)
{
	int	len;

	len = 0;
	if (ft_strsearch(str, '\n'))
	{
		while (str[len] && str[len] != '\n')
			len++;
		if (str[len] == '\n')
			len++;
		return (len);
	}
	return (ft_strlen(str));
}
