/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_middle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/18 12:35:40 by jtrancos          #+#    #+#             */
/*   Updated: 2021/05/19 16:02:58 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// añadimos un elemento detras del que habia y le ponemos el next del que habia

void	ft_lstadd_middle(t_list **lst, t_list **new)
{
	t_list	*aux;

	aux = (*lst)->next;
	(*lst)->next = *new;
	(*new)->next = aux;
}
