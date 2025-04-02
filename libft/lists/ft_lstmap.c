/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isastre- <isastre-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:19:47 by isastre-          #+#    #+#             */
/*   Updated: 2025/03/21 14:41:39 by isastre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*map;
	t_list	*current;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	map = NULL;
	while (lst)
	{
		current = ft_lstnew(f(lst->content));
		if (current == NULL)
		{
			ft_lstclear(&map, del);
			return (NULL);
		}
		ft_lstadd_back(&map, current);
		lst = lst->next;
	}
	return (map);
}
