/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 20:04:56 by adavitas          #+#    #+#             */
/*   Updated: 2025/06/17 20:44:57 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// #include <stdio.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	int		i;

	i = 0;
	if (s == NULL)
		return (NULL);
	str = malloc(ft_strlen(s) + 1);
	if (str == NULL)
		return (NULL);
	if (f == NULL)
	{
		ft_strlcpy(str, s, ft_strlen(s) + 1);
		return (str);
	}
	while (s[i])
	{
		str[i] = f(i, s[i]);
		++i;
	}
	str[i] = '\0';
	return (str);
}

// char	f_func(unsigned int x, char c)
// {
// 	x = 32;
// 	return (c - x);
// }

// int	main(void)
// {
// 	char	*s;

// 	s = "hello";
// 	printf("%s\n", ft_strmapi(s, &f_func));
// }
