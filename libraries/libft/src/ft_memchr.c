/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 13:26:15 by adavitas          #+#    #+#             */
/*   Updated: 2025/06/10 13:48:55 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// #include <stdio.h>
// #include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	while (n--)
	{
		if (*(unsigned char *)s == (unsigned char)c)
			return ((unsigned char *)s);
		s++;
	}
	return (NULL);
}

// int	main(void)
// {
// 	char str[] = "Hello World!";
// 	void *result;
// 	void *result1;

// 	result = ft_memchr(str, 'W', strlen(str));
// 	result1 = memchr(str, 'W', strlen(str));

// 	if (result)
// 		printf("ft_memchr 'W': %c\n", *(char *)result);
// 	else
// 		printf("ft_memchr 'W': not found\n");

// 	if (result1)
// 		printf("memchr 'W': %c\n", *(char *)result1);
// 	else
// 		printf("memchr 'W': not found\n");
// }