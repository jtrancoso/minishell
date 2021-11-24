/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_middle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 12:35:40 by jtrancos          #+#    #+#             */
/*   Updated: 2021/11/24 12:34:08 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_middle(t_list **lst, t_list **new)
{
	t_list	*aux;

	aux = (*lst)->next;
	(*lst)->next = *new;
	(*new)->next = aux;
}
