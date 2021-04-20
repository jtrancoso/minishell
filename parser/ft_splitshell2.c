/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitshell2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoria-g <isoria-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 10:09:14 by isoria-g          #+#    #+#             */
/*   Updated: 2021/04/19 13:07:32 by isoria-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static  void    check_quote(t_split *split, const char *c)
{
    //printf("%s", c);
	if ((int)c[0] == '\"' && split->f_double == 0 && split->f_simple == 0)
        split->f_double = 1;
    else if ((int)c[0] == '\'' && split->f_double == 0 && split->f_simple == 0)
        split->f_simple = 1;
    else if ((int)c[0] == '\"' && split->f_double == 1 && split->f_simple == 0)
        split->f_double = 0;
    else if ((int)c[0] == '\'' && split->f_double == 0 && split->f_simple == 1)
        {
			//printf("estoy aqui");
		split->f_simple = 0;
		}
	printf("%c-%i\n", c[0], (int)c[0]);
	printf("qd%d\n", split->f_double);
	printf("sd%d\n", split->f_simple);   
}

static int		ft_words(t_split *split, char const *s1, char c)
{
	int	a;
	int	b;

	a = 0;
	b = 0;
	if (*s1 == '\0')
		return (0);
	while (*s1 != '\0')
	{
		check_quote(split, s1);
		if (*s1 == c && split->f_simple == 0 && split->f_double == 0)
			a = 0;
		else if (a == 0)
		{
			a = 1;
			b++;
		}
		s1++;
	}
	printf("words:%d", b);
	return (b);
}

static int		ft_letters(t_split *split, char const *s2, char c, int a)
{
	int	len;

	len = 0;
	//check_quote(split, &s2[a]);
	while ((s2[a] != c && s2[a] != '\0') || (s2[a] == c && split->f_double == 0 && split->f_simple == 0))
	{
		len++;
		a++;
		//check_quote(split, &s2[a]);
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
	while (s[a] != '\0' && b < n)
	{
		check_quote(split, &s[a]);
		d = 0;
		while (s[a] == c)
			a++;
		str[b] = (char *)malloc(sizeof(char) * ft_letters(split, s, c, a) + 1);
		if (str[b] == NULL)
			return (ft_clean((char const **)str, b));
		while (s[a] != '\0' && s[a] != c)
		{
			str[b][d] = s[a];
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


int main ()
{
	char **tab;
	int i = 0;
	t_split split;

	tab = ft_splitshell(&split, "hola;adios", ';');
	if (!tab)
		return (0);
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
	return (0);
}