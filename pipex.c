/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:17:13 by isastre-          #+#    #+#             */
/*   Updated: 2025/05/22 21:52:51 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> // TODO delete
#include "pipex.h"

void	ft_run_cmds(t_cmd cmd1, t_cmd cmd2, char **envp);
void	ft_run_cmd1(t_cmd cmd1, int pipe_fd[], char **envp);
void	ft_run_cmd2(t_cmd cmd2, int pipe_fd[], char **envp, int pid);
void	connect_fds(int pipe_fd[], int used_end, int file);

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
	// ? de hecho, es realmente relevante comprobar que no exista un comando aquí?
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
		ft_run_cmd1(cmd1, pipe_fd, envp);
	else // parent
		ft_run_cmd2(cmd2, pipe_fd, envp, pid);
	// ! TODO en el caso de que algún comando de error ¿que hago?
}

// child (cmd1)
void	ft_run_cmd1(t_cmd cmd1, int pipe_fd[], char **envp)
{
	int	infile;

	infile = open(cmd1.filename, O_RDONLY); // TODO check error
	printf("exec cmd1 %s\n", cmd1.route);
	connect_fds(pipe_fd, WRITE_END, infile);
	
	execve(cmd1.route, cmd1.args, envp);
}

// parent (cmd2)
void	ft_run_cmd2(t_cmd cmd2, int pipe_fd[], char **envp, int pid)
{
	int	outfile;

	outfile = open(cmd2.filename, O_WRONLY | O_CREAT | O_TRUNC, 0644); // TODO check error

	connect_fds(pipe_fd, READ_END, outfile);
	wait(&pid);
	printf("exec cmd2 %s\n", cmd2.route); // ? por que fd deberia salir?

	execve(cmd2.route, cmd2.args, envp);
}

/**
 * @brief dups pipe used end and file fd to std in/out and closes unused fds
 * Pipe used end case:
 * 	if pipe_fd[0]: read end -> STDIN (0)
 * 	if pipe_fd[1]: write end -> STDOUT (1)
 * File case:
 * 	if infile -> STDIN
 * 	if outfile -> STDOUT
 */
void connect_fds(int pipe_fd[], int used_end, int file)
{
	int	unused_end;

	if (used_end == WRITE_END)
		unused_end = READ_END;
	else
		unused_end = WRITE_END;
	
	close(pipe_fd[unused_end]);
	
	dup2(file, unused_end);
	close(file);

	dup2(pipe_fd[used_end], used_end);
	close(pipe_fd[used_end]);
}
