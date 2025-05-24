/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 21:32:32 by isastre-          #+#    #+#             */
/*   Updated: 2025/05/24 04:04:01 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include <unistd.h>
# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>

# define WRITE_END STDOUT_FILENO
# define READ_END STDIN_FILENO

# define PARENT 1
# define CHILD 0

# define MSG_EXECUTION_INSTRUCTIONS "./pipex infile cmd1 cmd2 outfile"
# define MSG_COMMAND_NOT_FOUND "Command not found"

typedef struct cmd
{
	char	*route;
	char	**args;
	char	*filename;
	char	**envp;
}	t_cmd;

// t_cmd utils
t_cmd	*ft_create_cmd(const char *args, char *filename, char **envp);
void	ft_free_cmd(t_cmd *cmd);

// utils
char	*ft_find_commmand_route(char *cmd, char **envp);
void	ft_error(t_cmd *cmd, int exit_code);

#endif
