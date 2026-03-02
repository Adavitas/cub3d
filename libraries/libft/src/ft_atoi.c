/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 20:10:21 by adavitas          #+#    #+#             */
/*   Updated: 2025/06/10 21:07:58 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// #include <stdio.h>
// #include <stdlib.h>

int	ft_atoi(const char *nptr)
{
	int	i;
	int	result;

	i = 1;
	result = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == 43 || *nptr == 45)
	{
		if (*nptr == 45)
			i = -1;
		nptr++;
	}
	while (*nptr >= 48 && *nptr <= 57)
	{
		result = result * 10 + (*nptr - 48);
		nptr++;
	}
	result = result * i;
	return (result);
}

// int	main(void)
// {
// 	int n = 0;
// 	const char *str = "       -234599sdfjkkd";
// 	n = ft_atoi(str);
// 	printf("%d", n);
// }