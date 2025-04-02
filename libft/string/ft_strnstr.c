/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 00:06:39 by isastre-          #+#    #+#             */
/*   Updated: 2025/03/21 14:55:52 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	little_len;

	little_len = ft_strlen(little);
	if (little_len == 0)
		return ((char *) big);
	i = 0;
	while (*big && i + little_len <= len)
	{
		if (ft_strncmp(big, little, little_len) == 0)
			return ((char *) big);
		i++;
		big++;
	}
	return (NULL);
}
