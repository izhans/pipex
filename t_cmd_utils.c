/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cmd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 20:24:13 by isastre-          #+#    #+#             */
/*   Updated: 2025/05/23 03:03:57 by isastre-         ###   ########.fr       */
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
		return (NULL);
	cmd->route = ft_find_commmand_route(cmd->args[0], envp);
	if (cmd->route == NULL)
	{
		ft_free_str_array(cmd->args);
		free(cmd); // ?! si dejo de tener clausula guarda de existencia de comando esto puede ser un posible segfault
		return (NULL);
	}
	if (!*filename)
		cmd->filename = NULL;
	else
		cmd->filename = filename;
	cmd->envp = envp;
	return (cmd);
}

void	ft_free_cmd(t_cmd *cmd)
{
	// ? añadir comprobaciones de != NULL antes de hacer free ?
	if (cmd == NULL)
		return ;
	free(cmd->route);
	ft_free_str_array(cmd->args);
	free(cmd);
	// ? hacer que retorne NULL y así se puede usar como "generico" en errores
}
