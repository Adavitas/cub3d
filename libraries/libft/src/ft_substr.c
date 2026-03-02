/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 20:50:25 by adavitas          #+#    #+#             */
/*   Updated: 2025/06/12 22:26:09 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// #include <stdio.h>
// #include <string.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	src_len;

	if (!s)
		return (NULL);
	src_len = ft_strlen(s);
	if (start >= src_len)
		return (ft_strdup(""));
	if ((src_len - start) < len)
		len = src_len - start;
	str = malloc((len + 1) * sizeof(*str));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s + start, len + 1);
	return (str);
}

// int	main(void)
// {
// 	char *result;

// 	printf("Test 1: Normal substring\n");
// 	result = ft_substr("Hello, World!", 7, 5);
// 	printf("Input: \"Hello, World!\", start=7, len=5\n");
// 	printf("Expected: \"World\", Got: \"%s\"\n", result ? result : "NULL");
// 	printf("Test %s\n\n", strcmp(result, "World") == 0 ? "PASSED" : "FAILED");
// 	free(result);
// }