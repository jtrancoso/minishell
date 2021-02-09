/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 21:07:01 by jtrancos          #+#    #+#             */
/*   Updated: 2020/01/23 21:52:29 by jtrancos         ###   ########.fr       */
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
		if (!(map->next = ft_lstnew(f(lst->content))))
		{
			ft_lstclear(&map, del);
			return (NULL);
		}
		map = map->next;
	}
	return (first);
}
