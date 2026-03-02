/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 09:16:22 by adavitas          #+#    #+#             */
/*   Updated: 2025/06/11 10:31:45 by adavitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	byte_count;
	void	*ptr;

	byte_count = nmemb * size;
	if (size && ((byte_count / size) != nmemb))
		return (NULL);
	ptr = malloc(byte_count);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, byte_count);
	return (ptr);
}
