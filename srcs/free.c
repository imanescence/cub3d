/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-ouf <aitouflih.iman@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:12:57 by iait-ouf          #+#    #+#             */
/*   Updated: 2025/02/07 17:13:40 by iait-ouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	free_int_tab(int **tab)
{
	int	i;

	i = 0;
	while (tab && (tab)[i])
	{
		free((tab)[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}

void	free_char_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && (tab)[i])
	{
		free((tab)[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}

int	free_init(t_data *data)
{
	free(data->window);
	free(data->p);
	free(data->walls);
	return (1);
}

int	free_path(t_data *data, int i)
{
	i--;
	while (i > 0)
	{
		if (data->paths[i])
			free(data->paths[i]);
		i--;
	}
	return (1);
}
