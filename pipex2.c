/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 00:56:09 by isastre-          #+#    #+#             */
/*   Updated: 2025/05/23 04:01:39 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_exec_commands(char **argv, char **envp, int pipe_fd[]);
void	ft_run_command(t_cmd *cmd, int parent, int pipe_fd[]);
int		ft_open_file(char *filename, int create);
void	ft_connect_pipes(int pipe_fd[], int file_fd, int parent);

int main(int argc, char *argv[], char *envp[])
{
	pid_t	pid;
	int		pipe_fd[2];

	if (argc != 5)
		return (ft_print_error(MSG_EXECUTION_INSTRUCTIONS), 0);
	if (pipe(pipe_fd) == -1)
		exit(1); // error de pipe
	pid = fork();
	if (pid == -1)
		exit(1); // error de fork
	ft_exec_commands(argv, envp, pipe_fd);
	waitpid(pid, NULL, 0);
	return 0;
}

void	ft_exec_commands(char **argv, char **envp, int pipe_fd[])
{
	pid_t	pid;
	t_cmd	*cmd;

	pid = fork();
	if (pid == 0) // child
	{
		cmd = ft_create_cmd(argv[2], argv[1], envp);
		ft_run_command(cmd, CHILD, pipe_fd);
	}
	else if (pid > 0) // parent
	{
		cmd = ft_create_cmd(argv[3], argv[4], envp);
		ft_run_command(cmd, PARENT, pipe_fd);
	}
	waitpid(pid, NULL, 0); // aqui?
}


/**
 * @brief prepares and runs the command
 */
void	ft_run_command(t_cmd *cmd, int parent, int pipe_fd[])
{
	int		file_fd;
	
	if (cmd == NULL)
		return (ft_print_error(MSG_COMMAND_NOT_FOUND));

	file_fd = ft_open_file(cmd->filename, parent);
	if (cmd->filename != NULL && file_fd == -1)
		return (ft_print_error("Error opening the file"));
	
	ft_connect_pipes(pipe_fd, file_fd, parent);
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
