/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-ouf <aitouflih.iman@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:27:59 by iait-ouf          #+#    #+#             */
/*   Updated: 2025/02/07 17:28:02 by iait-ouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

char	*ft_strdup(const char *src)
{
	char	*dest;
	int		size;
	int		i;

	i = 0;
	if (!src)
		return (NULL);
	size = ft_strlen((char *)src);
	dest = malloc(sizeof(char) * size + 1);
	if (!dest)
		return (0);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	*ft_memset(void *b, int c, size_t len)
{
	char			*ptr;
	unsigned long	i;

	if (!b)
		return (NULL);
	i = 0;
	ptr = b;
	while (i < len)
	{
		ptr[i] = c;
		i++;
	}
	return (b);
}
