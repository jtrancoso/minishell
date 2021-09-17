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
			//while (str[i] && str[i] != c) // TODO: Validar con Jesús esta línea no necesaria
			//	i++; // TODO: Validar con Jesús esta línea no necesaria
		}
	}
	return (i);
}

static	char	*malloc_word(const char *str, char c)
{
	char	*word;
	int		i;

	i = 0;
	printf("he llegado aqui: %s\n", str);
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
		printf("Count\n");
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
	char str[110] = ";;;;HOLA2;2ADIOS";
	dest = (ft_split(str, ';'));
	int i = 0;
	while (dest[i])
	{
		printf("%d %s\n", i, dest[i]);
		i++;
	}
	return (0);
}