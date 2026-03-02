/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:44:53 by adavitas          #+#    #+#             */
/*   Updated: 2025/06/05 20:26:05 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <string.h>
#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	while (n--)
		*((unsigned char *)s + n) = c;
	return (s);
}

// int	main(void)
// {
// 	char t[10];

// 	for (int i = 0; i < 10; i++)
// 		t[i] = 1;

// 	ft_memset(t, 0, 5);

// 	for (int i = 0; i < 10; ++i)
// 		printf("%d\n", t[i]);

// 	printf("\n");

// 	memset(t, 0, 5);

// 	for (int i = 0; i < 10; ++i)
// 		printf("%d\n", t[i]);
// }