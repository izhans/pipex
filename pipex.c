/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:17:13 by isastre-          #+#    #+#             */
/*   Updated: 2025/05/06 18:49:39 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "libft/libft.h"
#include <errno.h>
#include <fcntl.h>

char	*ft_find_commmand_route(char const *cmd, char **envp);
char	**ft_get_path(char *envp[]);
char	*ft_find_path(char *envp[]);

int	main(int argc, char const *argv[], char *envp[])
{
	(void) argc, (void) argv;
	// TODO check initial errors
	if (argc != 5)
	{
		ft_putendl("./pipex infile cmd1 cmd2 outfile");
		return (0);
	}
	char **splited_cmd1 = ft_split(argv[2], ' ');
	char **splited_cmd2 = ft_split(argv[3], ' ');

	char *cmd1 = ft_find_commmand_route(splited_cmd1[0], envp);
	char *cmd2 = ft_find_commmand_route(splited_cmd2[0], envp);
	if (cmd1 == NULL || cmd2 == NULL)
	{
		ft_putendl("Command not found");
		free(splited_cmd1);
		free(splited_cmd2);
		return (0);
	}
	if (access(cmd1, X_OK) == -1 || access(cmd1, X_OK) == -1)
	{
		free(cmd1);
		free(cmd2);
		free(splited_cmd1);
		free(splited_cmd2);
		ft_putendl("Not enough permissions");
		return (0);
	}

	int pipe_fd[2];
	pipe(pipe_fd); // TODO check error
	
	int f = fork();
	if(f == -1)
		return (1);
	if (f == 0) // child
	{
		close(pipe_fd[0]);
		int infile = open(argv[1], O_RDONLY);
		dup2(infile, 0);
		close(infile);
		
		printf("cmd1 %s\n", cmd1);
		dup2(pipe_fd[1], 1);
		
		execve(cmd1, splited_cmd1, envp);
		ft_putstr("end cmd1\n"); // this is never executed
	}
	else // parent
	{
		close(pipe_fd[1]);
		int outfile = open(argv[4], O_WRONLY);
		dup2(outfile, 1);
		close(outfile);

		dup2(pipe_fd[0], 0);

		printf("waiting\n");
		wait(NULL);
		printf("end waiting\n");
		printf("cmd2 %s\n", cmd2);
		execve(cmd2, splited_cmd2, envp);
		printf("end cmd2\n");
	}
	
	return (0);
}

/**
 * first checks if the cmd exists as a complete route, if so, a copy is returned
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
		ft_joinstrs(cmd_parts, &cmd_route);
		if (access(cmd_route, F_OK) == 0)
			return (ft_free_str_array(path), cmd_route);
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
