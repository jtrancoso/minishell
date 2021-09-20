/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 10:09:14 by isoria-g          #+#    #+#             */
/*   Updated: 2021/09/20 13:49:53 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int check_inverted_var(const char *c)
{
	if ((int)c[0] == '\\' && (int)c[0] != '\0' && ((int)c[1] == '\"' || (int)c[1] == '\''))
		return (1);
	return (0);
}

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
		if (i != 0 && (s1[i] == c && s1[i - 1] != '\\' && split->f_simple == 0 && split->f_double == 0))
			a = 0;
		else if (i == 0 && s1[i] == c && split->f_simple == 0 && split->f_double == 0)
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
	while ((s2[a] != c && s2[a] != '\0') || (s2[a] == c && (split->f_double != 0 || split->f_simple != 0)))
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
	while (s[a] != '\0' && b < n)
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
		while ((s[a] != '\0' && s[a] != c) || (s[a] == c && (split->f_double != 0 || split->f_simple != 0)) || (s[a] == c && s[a - 1] == '\\'))
		{
			str[b][d] = s[a];
			check_quote(split, &s[a]);
			a++;
			d++;
		}
		str[b][d] = '\0';
		b++;
	}
	str[b] = 0;
	return (str);
}

char			**ft_splitshell(t_split *split, char const *s, char c)
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