/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-ouf <aitouflih.iman@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:36:04 by iait-ouf          #+#    #+#             */
/*   Updated: 2025/02/07 19:39:48 by iait-ouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int	ft_tab_size(char **tab)
{
	int	i;

	if (!tab || !(*tab))
		return (0);
	i = 0;
	while (tab[i] != NULL)
	{
		i++;
	}
	return (i);
}

int	choose_texture(char *texture_name)
{
	int		i;
	char	*texture[6];

	texture[0] = "NO";
	texture[1] = "SO";
	texture[2] = "WE";
	texture[3] = "EA";
	texture[4] = "F";
	texture[5] = "C";
	i = 0;
	while (i < 6)
	{
		if (!ft_strncmp(texture[i], texture_name, -1))
			return (i);
		i++;
	}
	return (-1);
}

int	ft_is_dir(char c)
{
	if (c && (c == 'N' || c == 'S'
			|| c == 'W' || c == 'E'))
		return (1);
	return (0);
}

int	if_dir(char *str)
{
	if (str && (!ft_strncmp(str, "NO", 2) || !ft_strncmp(str, "SO", 2)
			|| !ft_strncmp(str, "WE", 2) || !ft_strncmp(str, "EA", 2)))
		return (1);
	return (0);
}

int	if_fc(char *str)
{
	if (str && (str[0] == 'C' || str[0] == 'F'))
		return (1);
	return (0);
}
