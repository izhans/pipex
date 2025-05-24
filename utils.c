/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 08:43:28 by isastre-          #+#    #+#             */
/*   Updated: 2025/05/24 03:51:22 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_command_route_exists(char *cmd_route);
static char	**ft_get_path(char *envp[]);

/**
 * @brief checks if the cmd exists as a complete route, if so, a copy is returned
 */
char	*ft_find_commmand_route(char *cmd, char **envp)
{
	char		**path;
	int			i;
	char		*cmd_route;
	char const	*cmd_parts[] = {NULL, "/", cmd, NULL};

	if (ft_command_route_exists(cmd))
		return (ft_strdup(cmd));
	path = ft_get_path(envp);
	if (path == NULL)
		return (NULL);
	i = 0;
	while (path[i])
	{
		cmd_parts[0] = path[i];
		cmd_route = ft_joinstrs(cmd_parts);
		if (ft_command_route_exists(cmd_route))
		{
			ft_free_str_array(path);
			return (cmd_route);
		}
		free(cmd_route);
		i++;
	}
	ft_free_str_array(path);
	return (NULL);
}

static int	ft_command_route_exists(char *cmd_route)
{
	if (cmd_route == NULL)
		return (0);
	return (access(cmd_route, F_OK) == 0);
}

static char	**ft_get_path(char *envp[])
{
	while (*envp)
	{
		if (ft_strncmp("PATH=", *envp, 5) == 0)
			return (ft_split(*envp + 5, ':'));
		envp++;
	}
	return (NULL);
}

void	ft_error(t_cmd *cmd, int exit_code)
{
	perror("");
	ft_free_cmd(cmd);
	exit(exit_code);
}
