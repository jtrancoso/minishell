#include <stdio.h>

static	char	*malloc_free(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

static	int		count_words(const char *str, char c)
{
	int i;

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

char			**ft_split(char const *s, char c)
{
	int		words;
	int		i;
	char	**tab;

	i = 0;
	if (!s)
		return (NULL);
	words = count_words(s, c);
	tab = malloc(sizeof(char*) * (words + 1));
	if (!tab)
		return (NULL);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			if (!(tab[i++] = malloc_word(s, c)))
				return ((char**)malloc_free(tab));
			while (*s && *s != c)
				s++;
		}
	}
	tab[i] = NULL;
	return (tab);
}

int main ()
{
	char **dest;
	char str[110] = "echo hola; echo adios; pwd";
	dest = (ft_split(str, ';'));
	printf("0 %s\n 1 %s\n 2%s \n", dest[0], dest[1], dest[2]);
	return (0);
}