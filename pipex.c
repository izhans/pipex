/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:17:13 by isastre-          #+#    #+#             */
/*   Updated: 2025/05/05 14:55:17 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "libft/libft.h"
#include <errno.h>

char	*ft_find_commmand_route(char const *cmd, char **envp);
char	**ft_get_path(char *envp[]);
char	*ft_find_path(char *envp[]);

int	main(int argc, char const *argv[], char *envp[])
{
	(void) argc, (void) argv;
	// TODO check initial errors
	
	// ! encontrar primero los 2 comandos
	// TODO !!! comprobar primero que se puede acceder a la ruta que viene como comando
		// en ese caso no hay que buscar la ruta porque ya es un comando como tal
	char *cmd_route = ft_find_commmand_route(argv[2], envp);
	if (cmd_route == NULL)
	{
		perror("Error:");
		return (0);
	}

	return (0);
}

char	*ft_find_commmand_route(char const *cmd, char **envp)
{
	char		**path;
	int			i;
	char		*cmd_route;
	char const	*cmd_parts[] = {NULL, "/", cmd, NULL};

	path = ft_get_path(envp);
	if (path == NULL)
		return (NULL); // ? o exit directamente?
	i = 0;
	while (path[i])
	{
		cmd_parts[0] = path[i];
		cmd_route = NULL;
		ft_joinstrs(cmd_parts, &cmd_route);
		printf("route: %s\n", cmd_route);
		if (access(cmd_route, F_OK) == 0)
		{
			printf("command found\n");
			ft_free_str_array(path);
			return (cmd_route);
		}
		free(cmd_route);
		i++;
	}
	ft_free_str_array(path);
	return (NULL);
}

char	**ft_get_path(char *envp[])
{
	char	*path;

	path = ft_find_path(envp);
	if (path == NULL)
		return (NULL);
	return (ft_split(path + 5, ':'));
}

// ? subir comportamiento a get_path ?
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
