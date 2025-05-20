/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 08:43:28 by isastre-          #+#    #+#             */
/*   Updated: 2025/05/20 08:44:54 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**ft_get_path(char *envp[]);
static char	*ft_find_path(char *envp[]);

/**
 * @brief checks if the cmd exists as a complete route, if so, a copy is returned
 */
char	*ft_find_commmand_route(char const *cmd, char **envp)
{
	char		**path;
	int			i;
	char		*cmd_route;
	char const	*cmd_parts[] = {NULL, "/", cmd, NULL};

	if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	path = ft_get_path(envp);
	if (path == NULL)
		return (NULL); // ? o exit directamente?
	i = 0;
	while (path[i])
	{
		cmd_parts[0] = path[i];
		cmd_route = ft_joinstrs(cmd_parts);
		if (cmd_route == NULL) // malloc error inside ft_joinstrs
			break;
		if (access(cmd_route, F_OK) == 0)
			return (ft_free_str_array(path), cmd_route);
		free(cmd_route);
		i++;
	}
	ft_free_str_array(path);
	return (NULL);
}

static char	**ft_get_path(char *envp[])
{
	char	*path;

	path = ft_find_path(envp);
	if (path == NULL)
		return (NULL);
	return (ft_split(path + 5, ':'));
}

// ? subir comportamiento a get_path ?
static char	*ft_find_path(char *envp[])
{
	while (*envp)
	{
		if (ft_strncmp("PATH=", *envp, 5) == 0)
			return (*envp);
		envp++;
	}
	return (NULL);
}
