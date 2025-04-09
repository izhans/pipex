/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:17:13 by isastre-          #+#    #+#             */
/*   Updated: 2025/04/09 14:18:09 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "libft/libft.h"

char	**ft_get_path(char *envp[]);
char	*ft_find_path(char *envp[]);

int	main(int argc, char const *argv[], char *envp[])
{
	char	**paths;

	paths = ft_get_path(envp);
	while (*paths)
	{
		printf("%s\n", *paths);
		paths++;
	}

	return (0);
}

char	**ft_get_path(char *envp[])
{
	char	*path;

	path = ft_find_path(envp);
	printf("%s\n", path);
	return (ft_split(path + 5, ':'));
}

char	*ft_find_path(char *envp[])
{
	while (*envp)
	{
		if (ft_strncmp("PATH=", *envp, 5) == 0)
			return (*envp);
		envp++;
	}
	return (NULL);
}
