/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cmd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 20:24:13 by isastre-          #+#    #+#             */
/*   Updated: 2025/05/24 18:31:03 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_cmd	*ft_create_cmd(const char *args, char *filename, char **envp)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->args = ft_split(args, ' ');
	if (cmd->args == NULL)
		cmd->route = NULL;
	else
		cmd->route = ft_find_commmand_route(cmd->args[0], envp);
	cmd->filename = filename;
	cmd->envp = envp;
	return (cmd);
}

void	ft_free_cmd(t_cmd *cmd)
{
	if (cmd == NULL)
		return ;
	free(cmd->route);
	ft_free_str_array(cmd->args);
	free(cmd);
}
