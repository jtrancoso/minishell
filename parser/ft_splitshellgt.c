/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitshellgt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 12:51:54 by jtrancos          #+#    #+#             */
/*   Updated: 2021/10/13 12:44:26 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int		ft_words(t_split *split, char const *s1, char c)
{
	int	a;
	int	b;
	int i;

	a = 0;
	b = 0;
	i = 0;
	if (s1[i] == '\0')
		return (0);
	while (s1[i])
	{
		if (check_inverted_var(&s1[i]) == 1)
			i += 2;
		check_quote(split, &s1[i]);
		if (i != 0 && (s1[i] == c && s1[i + 1] == c && s1[i - 1] != '\\' && split->f_simple == 0 && split->f_double == 0))
			a = 0;
		else if (i == 0 && s1[i] == c && s1[i + 1] == c && split->f_simple == 0 && split->f_double == 0)
			a = 0;
		else if (a == 0)
		{
			a = 1;
			b++;
		}
		i++;
	}
	return (b);
}

static int		ft_letters(t_split *split, char const *s2, char c, int a)
{
	int	len;

	len = 0;
	split->f_double = 0;
	split->f_simple = 0;
	check_quote(split, &s2[a]);
	while ((s2[a] != c && s2[a] != '\0') || (s2[a] == c && s2[a + 1] == c && (split->f_double != 0 || split->f_simple != 0)) || (s2[a] == c && s2[a + 1] != c))
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

static char		**ft_clean(char const **str, int b)
{
	while (b > 0)
	{
		b--;
		free((void *)str[b]);
	}
	free(str);
	return (NULL);
}

static char		**ft_divide(t_split *split, char const *s, char **str, char c, int n)
{
	int	a;
	int	b;
	int	d;

	a = 0;
	b = 0;
	split->f_double = 0;
	split->f_simple = 0;
	while (s[a] != '\0' && b < n && n > 1)
	{
		d = 0;
		while (s[a] == c || (s[a] == c && (split->f_double != 0 || split->f_simple != 0)) || (s[a] == c && s[a - 1] == '\\'))
		{
			check_quote(split, &s[a]);
			a++;
		}
		str[b] = (char *)malloc(sizeof(char) * ft_letters(split, s, c, a) + 1);
		if (str[b] == NULL)
			return (ft_clean((char const **)str, b));
		while ((s[a] != '\0' && s[a] != c) || (s[a] == c && s[a + 1] != c) || (s[a] == c && (split->f_double != 0 || split->f_simple != 0)) || (s[a] == c && s[a - 1] == '\\'))
		{
			str[b][d] = s[a];
			check_quote(split, &s[a]);
			a++;
			d++;
		}
		str[b][d] = '\0';
		b++;
	}
	str[b] = NULL;
	return (str);
}

char			**ft_splitshellgt(t_split *split, char const *s, char c)
{
	char	**str;
	int		n;

	split->f_double = 0;
	split->f_simple = 0;
	if (s == NULL)
		return (NULL);
	n = ft_words(split, s, c);
	if (!(str = (char **)malloc(sizeof(char *) * (n + 1))))
		return (NULL);
	return (ft_divide(split, s, str, c, n));
}