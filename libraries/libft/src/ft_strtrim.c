/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:47:07 by adavitas          #+#    #+#             */
/*   Updated: 2025/06/14 19:42:44 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// #include <stdio.h>

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*str;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	start = 0;
	end = ft_strlen(s1);
	while (start < end && ft_strchr(set, s1[start]))
		start++;
	if (start == end)
		return (ft_strdup(""));
	end--;
	while (end > start && ft_strchr(set, s1[end]))
		end--;
	str = malloc((end - start + 2) * sizeof(*str));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1 + start, end - start + 2);
	return (str);
}

// int	main(void)
// {
// 	char const	*s1;
// 	char const	*set;
// 	char		*result;

// 	s1 = "-- Hello, World --";
// 	set = " -";
// 	result = ft_strtrim(s1, set);
// 	printf("%s", result);
// }
