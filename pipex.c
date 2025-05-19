/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:17:13 by isastre-          #+#    #+#             */
/*   Updated: 2025/05/19 21:44:55 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "libft/libft.h"
#include <errno.h>
#include <fcntl.h>
#include "pipex.h"

void	ft_run_cmds(t_cmd cmd1, t_cmd cmd2, char **envp);

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

	char *cmd1_route = ft_find_commmand_route(splited_cmd1[0], envp);
	char *cmd2_route = ft_find_commmand_route(splited_cmd2[0], envp);
	if (cmd1_route == NULL || cmd2_route == NULL)
	{
		ft_putendl("Command not found");
		ft_free_str_array(splited_cmd1);
		ft_free_str_array(splited_cmd2);
		return (0);
	}
	if (access(cmd1_route, X_OK) == -1 || access(cmd2_route, X_OK) == -1)
	{
		free(cmd1_route);
		free(cmd2_route);
		ft_free_str_array(splited_cmd1);
		ft_free_str_array(splited_cmd2);
		ft_putendl("Not enough permissions");
		return (0);
	}

	int pid = fork();
	if (pid == 0)
	{
		t_cmd cmd1 = {cmd1_route, splited_cmd1, argv[1]};
		t_cmd cmd2 = {cmd2_route, splited_cmd2, argv[4]};
		ft_run_cmds(cmd1, cmd2, envp);
	}
	else
		wait(&pid);
	
	printf("end main\n");
	return (0);
}

void	ft_run_cmds(t_cmd cmd1, t_cmd cmd2, char **envp)
{
	int pipe_fd[2];
	pipe(pipe_fd); // TODO check error
	
	int pid = fork();
	if(pid == -1)
		return ;
	if (pid == 0) // child
	{
		close(pipe_fd[0]);
		int infile = open(cmd1.filename, O_RDONLY);
		dup2(infile, STDIN_FILENO);
		close(infile);
		
		printf("cmd1 %s\n", cmd1.route);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		
		execve(cmd1.route, cmd1.args, envp);
	}
	else // parent
	{
		close(pipe_fd[1]);
		int outfile = open(cmd2.filename, O_WRONLY | O_CREAT, 0644); // ! outifle en bash borra el fichero entero?
		dup2(outfile, STDOUT_FILENO);
		close(outfile);

		dup2(pipe_fd[0], STDIN_FILENO);
		wait(&pid);

		printf("cmd2 %s\n", cmd2.route);
		close(pipe_fd[0]);
		execve(cmd2.route, cmd2.args, envp);
	}
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
