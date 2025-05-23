/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 00:56:09 by isastre-          #+#    #+#             */
/*   Updated: 2025/05/23 02:30:33 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

void	ft_run_cmd1(t_cmd *cmd, int pipe_fd[]);
void	ft_run_cmd2(t_cmd *cmd, int pipe_fd[], pid_t pid);
int		ft_open_file(char *filename, int create);
void	ft_connect_pipes(int pipe_fd[], int file_fd, int parent);

int main(int argc, char *argv[], char *envp[])
{
	pid_t	pid;
	t_cmd	*cmd;
	int		pipe_fd[2];

	if (argc != 5)
		return (ft_print_error(MSG_EXECUTION_INSTRUCTIONS), 0);
	
	if (pipe(pipe_fd) == -1)
		exit(1); // error de pipe

	pid = fork();
	if (pid == 0) // child
	{
		cmd = ft_create_cmd(argv[2], argv[1], envp);
		ft_run_cmd1(cmd, pipe_fd);
	}
	else if (pid > 0) // parent
	{
		cmd = ft_create_cmd(argv[3], argv[4], envp);
		// waitpid(pid, NULL, 0);
		ft_run_cmd2(cmd, pipe_fd, pid);
	}
	return 0;
}
// child (cmd1)
void	ft_run_cmd1(t_cmd *cmd, int pipe_fd[])
{
	int	infile;

	if (cmd == NULL)
		return (ft_print_error(MSG_COMMAND_NOT_FOUND));
	
	infile = ft_open_file(cmd->filename, 0);
	if (cmd->filename != NULL && infile == -1)
		return ft_print_error(MSG_ERROR_OPENING_INFILE);
	
	printf("exec cmd1 %s\n", cmd->route);
	ft_connect_pipes(pipe_fd, infile, CHILD);
	
	execve(cmd->route, cmd->args, cmd->envp);
	free(cmd);
	exit(127);
}

// parent (cmd2)
void	ft_run_cmd2(t_cmd *cmd, int pipe_fd[], pid_t pid)
{
	int	outfile;
	
	wait(&pid);
	
	if (cmd == NULL)
		return ft_print_error(MSG_COMMAND_NOT_FOUND);
	
	outfile = ft_open_file(cmd->filename, 1);
	if (cmd->filename != NULL && outfile == -1)
		return ft_print_error(MSG_ERROR_CREATING_OUTFILE);
	
	ft_connect_pipes(pipe_fd, outfile, PARENT);
	printf("exec cmd2 %s\n", cmd->route);

	execve(cmd->route, cmd->args, cmd->envp);
	free(cmd);
	exit(127);
}

/**
 * @brief opens or creates the file with the filename given
 */
int	ft_open_file(char *filename, int create)
{
	int	fd;

	if (create)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(filename, O_RDONLY);
	return (fd);
}

/**
 * @brief makes the pipe ends connection between commands
 */
void	ft_connect_pipes(int pipe_fd[], int file_fd, int parent)
{
	if (parent)
	{
		dup2(file_fd, STDOUT_FILENO);
		dup2(pipe_fd[READ_END], STDIN_FILENO);
	}
	else
	{
		dup2(file_fd, STDIN_FILENO);
		dup2(pipe_fd[WRITE_END], STDOUT_FILENO);
	}
	close(file_fd);
	close(pipe_fd[READ_END]);
	close(pipe_fd[WRITE_END]);
}
