/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-ouf <aitouflih.iman@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:14:00 by iait-ouf          #+#    #+#             */
/*   Updated: 2025/02/07 17:14:04 by iait-ouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

static int	free_tab(char **tab, int i)
{
	while (i >= 0)
	{
		free(tab[i]);
		i--;
	}
	free(tab);
	return (0);
}

static unsigned long	count_words(char *s, char c)
{
	int	i;
	int	count;

	count = 0;
	if (s[0] != c)
		count++;
	if (s[ft_strlen(s) - 1] == c)
		count--;
	i = 0;
	while (s[i])
	{
		if (s[i] == c && (s[i + 1] != c))
			count++;
		i++;
	}
	return (count);
}

static int	add_str(char **str, char *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	*ptr;

	i = -1;
	j = -1;
	ptr = (char *)s;
	while (s[++i])
	{
		if (s[i] != c)
		{
			k = 0;
			while (s[i + k] && s[i + k] != c)
				k++;
			str[++j] = malloc(sizeof(char) * (k + 1));
			if (!str[j])
				return (free_tab(str, j - 1));
			ft_strlcpy(str[j], ptr + i, k + 1);
			i += k - 1;
		}
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	int		words;
	char	**tab;

	if (!s)
		return (0);
	if (s[0] == '\0')
		words = 0;
	else
		words = count_words((char *)s, c);
	tab = malloc(sizeof(char *) * (words + 1));
	if (!tab)
		return (NULL);
	if (words > 0)
	{
		if (!add_str(tab, (char *)s, c))
			return (NULL);
	}
	tab[words] = NULL;
	return (tab);
}
