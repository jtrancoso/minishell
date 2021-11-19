/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoria-g <isoria-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 10:09:14 by isoria-g          #+#    #+#             */
/*   Updated: 2021/11/19 10:17:12 by isoria-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_words(t_split *split, char const *s1, char c)
{
	init_splitshell(split, 0);
	if (s1[split->i] == '\0')
		return (0);
	while (s1[split->i])
	{
		if (check_inverted_var(&s1[split->i]) == 1)
			split->i += 2;
		check_quote(split, &s1[split->i]);
		if (split->i != 0 && (s1[split->i] == c && s1[split->i - 1] != '\\'
				&& split->f_simple == 0 && split->f_double == 0))
			split->j = 0;
		else if (split->i == 0 && s1[split->i] == c && split->f_simple == 0
			&& split->f_double == 0)
			split->j = 0;
		else if (split->j == 0)
		{
			split->j = 1;
			split->k++;
		}
		split->i++;
	}
	return (split->k);
}

static int	ft_letters(t_split *split, char const *s2, char c, int a)
{
	int	len;

	len = 0;
	split->f_double = 0;
	split->f_simple = 0;
	check_quote(split, &s2[a]);
	while ((s2[a] != c && s2[a] != '\0')
		|| (s2[a] == c && (split->f_double != 0 || split->f_simple != 0)))
	{
		len++;
		a++;
		check_quote(split, &s2[a]);
	}
	if (s2[a] == '\0')
	{
		split->f_double = 0;
		split->f_simple = 0;
	}
	return (len);
}

static char	**ft_clean(char const **str, int b)
{
	while (b > 0)
	{
		b--;
		free((void *)str[b]);
	}
	free(str);
	return (NULL);
}

static char	**ft_divide(t_split *split, char const *s, char **str, char c)
{
	init_splitshell(split, 1);
	while (s[split->i] != '\0' && split->j < split->n)
	{
		split->k = 0;
		while (s[split->i] == c || (s[split->i] == c && (split->f_double != 0 \
		|| split->f_simple != 0)) || (s[split->i] == c && s[split->i - 1] \
		== '\\'))
			check_quote(split, &s[split->i++]);
		str[split->j] = (char *)malloc(sizeof(char)
				* ft_letters(split, s, c, split->i) + 1);
		if (str[split->j] == NULL)
			return (ft_clean((char const **)str, split->j));
		while ((s[split->i] != '\0' && s[split->i] != c) || (s[split->i] == c \
		&& (split->f_double != 0 || split->f_simple != 0)) \
		|| (s[split->i] == c && s[split->i - 1] == '\\'))
		{
			str[split->j][split->k] = s[split->i];
			check_quote(split, &s[split->i++]);
			split->k++;
		}
		str[split->j++][split->k] = '\0';
	}
	str[split->j] = 0;
	return (str);
}

char	**ft_splitshell(t_split *split, char const *s, char c)
{
	char	**str;

	split->f_double = 0;
	split->f_simple = 0;
	if (s == NULL)
		return (NULL);
	split->n = ft_words(split, s, c);
	str = (char **)malloc(sizeof(char *) * (split->n + 1));
	if (!str)
		return (NULL);
	return (ft_divide(split, s, str, c));
}
