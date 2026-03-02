/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 12:45:29 by adavitas          #+#    #+#             */
/*   Updated: 2025/06/11 10:18:56 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <string.h>

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	while (n--)
		*((unsigned char *)s + n) = 0;
}

// int	main(void)
// {
// 	int	t[5];

// 	for (int i = 0; i < 5; i++)
// 		t[i] = 1;
// 	for (int i = 0; i < 5; i++)
// 		printf("%d\n", t[i]);
// 	printf("\n");
// 	ft_bzero(t, 20);
// 	for (int i = 0; i < 5; i++)
// 		printf("%d\n", t[i]);
// 	printf("\n\n");
// 	for (int i = 0; i < 5; i++)
// 		t[i] = 1;
// 	for (int i = 0; i < 5; i++)
// 		printf("%d\n", t[i]);
// 	printf("\n");
// 	bzero(t, 20);
// 	for (int i = 0; i < 5; i++)
// 		printf("%d\n", t[i]);
// }
