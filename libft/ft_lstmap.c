/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 21:07:01 by jtrancos          #+#    #+#             */
/*   Updated: 2021/03/04 12:30:19 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*first;
	t_list	*map;

	if (!lst || !f)
		return (NULL);
	map = ft_lstnew(f(lst->content));
	first = map;
	while (lst->next)
	{
		lst = lst->next;
		map->next = ft_lstnew(f(lst->content));
		if (!(map->next))
		{
			ft_lstclear(&map, del);
			return (NULL);
		}
		map = map->next;
	}
	return (first);
}
