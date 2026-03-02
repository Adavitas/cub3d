/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:18:33 by adavitas          #+#    #+#             */
/*   Updated: 2025/06/17 17:31:33 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <stdlib.h>

#include "libft.h"

static int	ft_len(long n)
{
	int	count;

	count = 0;
	if (n <= 0)
		count++;
	while (n)
	{
		count++;
		n /= 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	long	l_n;

	l_n = n;
	len = ft_len(l_n);
	str = malloc(len + 1);
	if (str == NULL)
		return (NULL);
	if (l_n == 0)
		str[0] = '0';
	else if (l_n < 0)
	{
		str[0] = '-';
		l_n = -l_n;
	}
	str[len] = '\0';
	while (l_n)
	{
		str[--len] = (l_n % 10) + 48;
		l_n = l_n / 10;
	}
	return (str);
}

// int	main(void)
// {
// 	long n;

// 	n = -2147483648;
// 	printf("%s", ft_itoa(n));
// }