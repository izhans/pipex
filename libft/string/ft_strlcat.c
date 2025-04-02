/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 04:19:50 by isastre-          #+#    #+#             */
/*   Updated: 2025/03/21 14:55:24 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// size is the max size of the final dst
// returns the len of the string it tried to create
//	-> if the size is smaller than the dest (it cannot concatenate)
//	--> src len + size
//	-> else
// 	--> initial len of dst + len of src
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dst_len;
	size_t	src_len;

	i = 0;
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (size == 0 || size <= dst_len)
		return (src_len + size);
	while (src[i] && dst_len + i < size - 1)
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}
