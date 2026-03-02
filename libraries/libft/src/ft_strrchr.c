/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 21:42:27 by adavitas          #+#    #+#             */
/*   Updated: 2025/06/09 23:21:51 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// #include <stdio.h>
// #include <string.h>

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;

	len = ft_strlen(s);
	if ((char)c == '\0')
		return ((char *)s + len);
	while (len--)
	{
		if (*(s + len) == (char)c)
			return ((char *)s + len);
	}
	return (NULL);
}

// int	main(void)
// {
// 	char	str[] = "Hello World!";
// 	char	*ptr;

// 	ptr = ft_strrchr(str, 'l');
// 	if (ptr != NULL)
// 		printf("Found last 'l' at position: %ld\n", ptr - str);
// }
