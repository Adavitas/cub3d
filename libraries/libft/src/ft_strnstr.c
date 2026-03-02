/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:36:24 by adavitas          #+#    #+#             */
/*   Updated: 2025/06/10 20:02:39 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// #include <stdio.h>
// #include <string.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	n;

	i = 0;
	if (!*little)
		return ((char *)big);
	while (*(big + i) && i < len)
	{
		n = 0;
		while (*(big + i + n) == *(little + n) && *(little + n) && (i
				+ n) < len)
			++n;
		if (*(little + n) == 0)
			return ((char *)big + i);
		++i;
	}
	return (NULL);
}

// int	main(void)
// {
// 	printf("%s\n", ft_strnstr("lorem ipsum dolor sit amet", "ipsum", 15));
// 	printf("%s\n", ft_strnstr("lorem ipsum dolor sit amet", "dolor", 17));
// }
