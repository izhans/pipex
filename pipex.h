/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 21:32:32 by isastre-          #+#    #+#             */
/*   Updated: 2025/05/20 08:45:59 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include <unistd.h>
# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>

typedef struct cmd
{
	char		*route;
	char		**args;
	const char	*filename;
}	t_cmd;

char	*ft_find_commmand_route(char const *cmd, char **envp);

#endif
