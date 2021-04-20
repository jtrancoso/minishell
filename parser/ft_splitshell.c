/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoria-g <isoria-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 12:49:17 by jtrancos          #+#    #+#             */
/*   Updated: 2021/04/19 10:14:30 by isoria-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	char	*malloc_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

static	int	count_words(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i] && str[i] != c)
		{
			i++;
			while (str[i] && str[i] != c)
				i++;
		}
	printf("Count_words:%d", i);
	}
	return (i);
}

static	char	*malloc_word(const char *str, char c)
{
	char	*word;
	int		i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	word = malloc(sizeof(char) * (i + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != c)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_splitshell(t_split *split, char const *s, char c)
{
	int		i;
	int 	j;
	char	**tab;

	i = 0;
	j = 0;

	if (!s)
		return (NULL);
	tab = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!tab)
		return (NULL);
	while (s[j])
	{
		if (s[0] == c || (s[j] == c && s[j + 1] == c))
		{
			ft_error(2);
			return (NULL);
		}
		if (s[j] == c && j != 0)
			j++;
		if (s[j] && s[j] != c)
		{
			tab[i] = malloc_word(s + j, c);
			if (!(tab[i]))
				return ((char **)malloc_free(tab));
			while (s[j] && s[j] != c)
				j++;
			i++;
		}
	}
	tab[i] = NULL;
	return (tab);
}


int main ()
{
	char **tab;
	int i = 0;
	t_split split;

	tab = ft_splitshell(&split, "hola;hola;adios", ';');
	if (!tab)
		return (0);
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
	return (0);
}