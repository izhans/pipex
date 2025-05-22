/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 21:32:32 by isastre-          #+#    #+#             */
/*   Updated: 2025/05/22 12:29:58 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include <unistd.h>
# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>

# define WRITE_END STDOUT_FILENO
# define READ_END STDIN_FILENO

typedef struct cmd
{
	char		*route;
	char		**args;
	const char	*filename;
}	t_cmd;

// t_cmd utils
t_cmd	*ft_create_cmd(const char *args, const char *filename, char **envp);
void	ft_free_cmd(t_cmd *cmd);
// route utils
char	*ft_find_commmand_route(char *cmd, char **envp);

#endif
