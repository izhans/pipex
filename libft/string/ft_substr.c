/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:32:52 by isastre-          #+#    #+#             */
/*   Updated: 2025/03/21 14:56:13 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	str_len;
	char	*substr;

	str_len = ft_strlen(s);
	if (start >= str_len)
	{
		len = 0;
		start = 0;
	}
	else if (len > str_len - start)
		len = str_len - start;
	substr = malloc((len + 1) * sizeof(char));
	if (substr == NULL)
		return (NULL);
	ft_strlcpy(substr, s + start, len + 1);
	return (substr);
}
