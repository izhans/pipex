/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 04:35:47 by isastre-          #+#    #+#             */
/*   Updated: 2025/03/21 14:56:32 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static size_t	ft_get_number_of_parts(char const *s, char c);
static size_t	ft_count_parts(char const *str, char c, size_t i, size_t len);
static char		**ft_alloc(char **strs, char const *str, size_t parts, char c);
static char		**ft_free(char **strs, size_t i);

char	**ft_split(char const *s, char c)
{
	char	**strs;
	size_t	parts;

	parts = ft_get_number_of_parts(s, c);
	strs = malloc((parts + 1) * sizeof(char *));
	if (strs == NULL)
		return (NULL);
	return (ft_alloc(strs, s, parts, c));
}

static size_t	ft_get_number_of_parts(char const *str, char c)
{
	size_t	i;
	size_t	strlen;

	i = 0;
	strlen = ft_strlen(str);
	while (str[i] == c && i < strlen)
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[strlen -1] == c)
		strlen--;
	return (ft_count_parts(str, c, i, strlen));
}

static size_t	ft_count_parts(char const *str, char c, size_t i, size_t len)
{
	int		sep;
	size_t	parts;

	sep = 0;
	parts = 0;
	while (i < len)
	{
		if (!sep && str[i] == c)
			sep = 1;
		else if (sep && str[i] != c)
		{
			parts++;
			sep = 0;
		}
		i++;
	}
	if (sep == 0)
		parts++;
	return (parts);
}

static char	**ft_alloc(char **strs, char const *str, size_t parts, char c)
{
	size_t			i;
	unsigned int	start;
	size_t			len;

	i = 0;
	start = 0;
	while (i < parts)
	{
		len = 0;
		while (str[start + len] == c)
			start++;
		while (str[start + len] != c && str[start + len] != '\0')
			len++;
		strs[i] = ft_substr(str, start, len);
		if (strs[i] == NULL)
			return (ft_free(strs, i));
		i++;
		start += len;
	}
	strs[i] = NULL;
	return (strs);
}

static char	**ft_free(char **strs, size_t i)
{
	while (i)
	{
		i--;
		free(strs[i]);
	}
	free(strs);
	return (NULL);
}
