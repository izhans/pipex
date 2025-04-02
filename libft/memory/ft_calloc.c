/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:36:16 by isastre-          #+#    #+#             */
/*   Updated: 2025/03/21 15:00:59 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*mem;
	size_t	alloc_size;

	alloc_size = nmemb * size;
	mem = malloc(alloc_size);
	if (mem == NULL)
		return (NULL);
	ft_bzero(mem, alloc_size);
	return (mem);
}
