/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-ouf <aitouflih.iman@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:33:14 by iait-ouf          #+#    #+#             */
/*   Updated: 2023/10/16 17:33:46 by iait-ouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strnjoin(char *s1, char *s2, int n)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s1 && s1[i])
		i++;
	while (s2 && s2[j])
		j++;
	if (n != -1)
		j = n;
	if (i == 0 && j == 0)
		return (NULL);
	str = malloc(sizeof(char) * (i + j + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = -1;
	while (++i != -1 && s1 && s1[i])
		str[i] = s1[i];
	while (++j != -1 && s2 && s2[j] && n-- != 0)
		str[i + j] = s2[j];
	str[i + j] = '\0';
	return (str);
}

char	*ft_strchr(char *s, char c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == c)
			return (&s[i]);
		i++;
	}
	return (NULL);
}

void	ft_strmov(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s2 || (s2 && !s2[0]))
		s1[0] = '\0';
	while (s2 && s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
}
