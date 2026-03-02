/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:25:16 by adavitas          #+#    #+#             */
/*   Updated: 2025/06/06 19:48:03 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// #include <stdio.h>
// #include <string.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	int	i;

	if (src == NULL && dest == NULL)
		return (NULL);
	i = 0;
	while (n--)
	{
		*((unsigned char *)dest + i) = *((unsigned char *)src + i);
		i++;
	}
	return (dest);
}

// int	main(void)
// {
// 	char	d[] = "hello";
// 	char	s[] = "World";

// 	printf("%s\n", ft_memcpy(d, s, 3));
// 	printf("%s\n", memcpy(d, s, 3));
// }
