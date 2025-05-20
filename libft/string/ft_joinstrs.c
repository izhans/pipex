/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_joinstrs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:14:56 by isastre-          #+#    #+#             */
/*   Updated: 2025/05/20 20:47:48 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_get_total_len(char const **strs);

char	*ft_joinstrs(char const **strs)
{
	int		len;
	int		i;
	int		j;
	char	*str;

	len = ft_get_total_len(strs);
	str = malloc(len + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (*strs)
	{
		j = 0;
		while ((*strs)[j])
		{
			str[i] = (*strs)[j];
			i++;
			j++;
		}
		strs++;
	}
	str[i] = '\0';
	return (str);
}

static int	ft_get_total_len(char const **strs)
{
	int		len;

	len = 0;
	while (*strs)
	{
		len += ft_strlen(*strs);
		strs++;
	}
	return (len);
}
