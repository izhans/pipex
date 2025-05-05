/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_joinstrs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:14:56 by isastre-          #+#    #+#             */
/*   Updated: 2025/05/05 14:06:56 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_joinstrs(char const **strs, char **str)
{
	int		len;
	int		i;
	int		j;

	len = 0;
	i = 0;
	while (strs[i])
	{
		len += ft_strlen(strs[i]);
		i++;
	}
	*str = malloc(len + 1);
	i = 0;
	while (*strs)
	{
		j = 0;
		while ((*strs)[j])
		{
			(*str)[i] = (*strs)[j];
			i++;
			j++;
		}
		strs++;
	}
}
