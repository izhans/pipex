/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:17:13 by isastre-          #+#    #+#             */
/*   Updated: 2025/05/24 20:51:05 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_exec_commands(char **argv, char **envp, int pipe_fd[]);
static void	ft_run_command(t_cmd *cmd, int parent, int pipe_fd[]);
static int	ft_open_file(t_cmd *cmd, int create);
static int	ft_connect_pipes(int pipe_fd[], int file_fd, int parent);

int	main(int argc, char *argv[], char *envp[])
{
	int		pipe_fd[2];

	if (argc != 5)
		return (ft_putendl(MSG_EXECUTION_INSTRUCTIONS), 0);
	if (pipe(pipe_fd) == -1)
		ft_error(NULL, EXIT_FAILURE);
	ft_exec_commands(argv, envp, pipe_fd);
	return (0);
}

/**
 * @brief creates the childs and each of them execs a command
 * @note at the end is necessary to close both pipe_fd ends to avoid a deadlock 
 */
static void	ft_exec_commands(char **argv, char **envp, int pipe_fd[])
{
	pid_t	pid;
	pid_t	pid2;
	t_cmd	*cmd;

	pid = fork();
	if (pid == -1)
		ft_error(NULL, EXIT_FAILURE);
	if (pid == 0)
	{
		cmd = ft_create_cmd(argv[2], argv[1], envp);
		ft_run_command(cmd, CHILD, pipe_fd);
	}
	pid2 = fork();
	if (pid2 == -1)
		ft_error(NULL, EXIT_FAILURE);
	if (pid2 == 0)
	{
		cmd = ft_create_cmd(argv[3], argv[4], envp);
		ft_run_command(cmd, PARENT, pipe_fd);
	}
	close(pipe_fd[READ_END]);
	close(pipe_fd[WRITE_END]);
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
}

/**
 * @brief prepares and runs the command
 */
static void	ft_run_command(t_cmd *cmd, int parent, int pipe_fd[])
{
	int		file_fd;

	if (cmd == NULL)
		ft_error(cmd, 1);
	file_fd = ft_open_file(cmd, parent);
	if (cmd->route == NULL)
	{
		ft_putendl_fd(MSG_COMMAND_NOT_FOUND, 2);
		ft_free_cmd(cmd);
		exit(127);
	}
	if (ft_connect_pipes(pipe_fd, file_fd, parent))
		ft_error(cmd, 1);
	execve(cmd->route, cmd->args, cmd->envp);
	ft_error(cmd, 126);
}

/**
 * @brief opens or creates the file with the filename given
 */
static int	ft_open_file(t_cmd *cmd, int create)
{
	int	fd;

	if (create)
		fd = open(cmd->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(cmd->filename, O_RDONLY);
	if (fd == -1)
		ft_error(cmd, EXIT_FAILURE);
	return (fd);
}

/**
 * @brief makes the pipe ends connection between commands
 */
static int	ft_connect_pipes(int pipe_fd[], int file_fd, int parent)
{
	int	error;

	if (parent)
	{
		error = (dup2(file_fd, STDOUT_FILENO) == -1
				|| dup2(pipe_fd[READ_END], STDIN_FILENO) == -1);
	}
	else
	{
		error = (dup2(file_fd, STDIN_FILENO) == -1
				|| dup2(pipe_fd[WRITE_END], STDOUT_FILENO) == -1);
	}
	close(file_fd);
	close(pipe_fd[READ_END]);
	close(pipe_fd[WRITE_END]);
	return (error);
}
