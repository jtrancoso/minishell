/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoria-g <isoria-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 20:46:32 by isoria-g          #+#    #+#             */
/*   Updated: 2021/11/20 20:59:12 by isoria-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_condition(t_split *split, char const *s, char c)
{
	if ((s[split->i] != '\0' && s[split->i] != c) || (s[split->i] == c
			&& s[split->i + 1] != c) || (s[split->i] == c
			&& (split->f_double != 0 || split->f_simple != 0))
		|| (s[split->i] == c && s[split->i - 1] == '\\'))
		return (1);
	return (0);
}
