/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 10:22:54 by adavitas          #+#    #+#             */
/*   Updated: 2025/06/11 10:32:12 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*str;
	int		buffer_size;

	buffer_size = ft_strlen(s) + 1;
	str = malloc(buffer_size);
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s, buffer_size);
	return (str);
}
