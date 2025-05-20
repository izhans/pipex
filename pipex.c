/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:17:13 by isastre-          #+#    #+#             */
/*   Updated: 2025/05/20 21:41:57 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> // TODO delete
#include "pipex.h"

void	ft_run_cmds(t_cmd cmd1, t_cmd cmd2, char **envp);
void	ft_run_cmd1(t_cmd cmd1, int pipe_fd[], char **envp);
void	ft_run_cmd2(t_cmd cmd2, int pipe_fd[], char **envp, int pid);

// ? meter envp en t_cmd ?
int	main(int argc, char const *argv[], char *envp[])
{
	t_cmd	*cmd1;
	t_cmd	*cmd2;
	int		pid;
	
	if (argc != 5)
	{
		ft_putendl("./pipex infile cmd1 cmd2 outfile");
		return (0);
	}
	cmd1 = ft_create_cmd(argv[2], argv[1], envp);
	cmd2 = ft_create_cmd(argv[3], argv[4], envp);
	if (cmd1 == NULL || cmd2 == NULL) // ! no tienen porque existir los 2 para que se ejecute alguno
	{
		ft_putendl("Command not found");
		ft_free_cmd(cmd1);
		ft_free_cmd(cmd2);
		return (0);
	}

	pid = fork();
	if (pid == 0)
		ft_run_cmds(*cmd1, *cmd2, envp);
	else
		wait(&pid);
	
	// free
	ft_free_cmd(cmd1);
	ft_free_cmd(cmd2);
	
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
		ft_run_cmd1(cmd1, pipe_fd, envp);
	}
	else // parent
	{
		ft_run_cmd2(cmd2, pipe_fd, envp, pid);
	}
}

// child (cmd1)
void	ft_run_cmd1(t_cmd cmd1, int pipe_fd[], char **envp)
{
	int	infile;

	close(pipe_fd[0]);

	infile = open(cmd1.filename, O_RDONLY);
	dup2(infile, STDIN_FILENO);
	close(infile);
	
	printf("exec cmd1 %s\n", cmd1.route);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	
	execve(cmd1.route, cmd1.args, envp);
}

// parent (cmd2)
void	ft_run_cmd2(t_cmd cmd2, int pipe_fd[], char **envp, int pid)
{
	int	outfile;

	close(pipe_fd[1]);

	outfile = open(cmd2.filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(outfile, STDOUT_FILENO);
	close(outfile);

	dup2(pipe_fd[0], STDIN_FILENO);
	wait(&pid);
	printf("exec cmd2 %s\n", cmd2.route);
	close(pipe_fd[0]);

	execve(cmd2.route, cmd2.args, envp);
}
