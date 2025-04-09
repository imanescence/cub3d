/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkhattab <wkhattab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:26:54 by iait-ouf          #+#    #+#             */
/*   Updated: 2025/02/07 19:41:51 by iait-ouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && s2[i] && s1[i] && n - 1 > i)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	l;

	l = ft_strlen((char *)src);
	i = 0;
	if (size != 0)
	{
		while (src[i] && i < size - 1)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (l);
}

int	ft_isdigit(int c)
{
	return (c <= '9' && c >= '0');
}

int	ft_atol(const char *str)
{
	int		i;
	long	nb;
	long	ng;

	i = 0;
	nb = 0;
	ng = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			ng *= -1;
		i++;
	}
	if (!ft_isdigit(str[i]))
		return (-1);
	while (ft_isdigit(str[i]))
	{
		nb = nb * 10;
		nb = nb + (str[i++] - '0');
	}
	if ((nb * ng) > INT_MAX || (nb * ng) < INT_MIN)
		return (-1);
	return ((int)(nb * ng));
}
