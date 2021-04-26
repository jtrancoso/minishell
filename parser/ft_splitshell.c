/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrancos <jtrancos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 10:09:14 by isoria-g          #+#    #+#             */
/*   Updated: 2021/04/26 14:26:04 by jtrancos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//TODO: gestion de errores
//TODO: check '\' en el checkquotes y mirar si podemosa cambiar lo que le pasamos a un array y una i
//TODO: mirar si se puede hacer un barraflag y pasarlo por ahi


static  void    check_quote(t_split *split, const char *c)
{
    printf("%s", c);
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
	//printf("%c-%i", c[0], (int)c[0]);
	//printf("flag: d%d\n", split->f_double);
	printf("letra: %c flag_s: %d flag_d: %d\n", c[0],  split->f_simple, split->f_double);   
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
	//printf("check_words\n");
	while (s1[i])
	{
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
	printf("words:%d\n", b);
	return (b);
}

static int		ft_letters(t_split *split, char const *s2, char c, int a)
{
	int	len;

	len = 0;
	split->f_double = 0;
	split->f_simple = 0;
	//printf("1\n");
	//printf("letra1: %c\n", s2[a]);
	check_quote(split, &s2[a]);
	while ((s2[a] != c && s2[a] != '\0') || (s2[a] == c && (split->f_double != 0 || split->f_simple != 0)))
	{
		len++;
		a++;
		//check_quote(split, &s2[a]); //TODO: mirar si es necesario
	}
	if (s2[a] == '\0')
	{
		split->f_double = 0;
		split->f_simple = 0;
	}
	//printf("len%d", len);
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


/*int main ()
{
	char **tab;
	int i = 0;
	t_split split;

	tab = ft_splitshell(&split, "hola';'adios;a", ';');
	if (!tab)
		return (0);
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
	return (0);
}*/