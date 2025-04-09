/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-ouf <aitouflih.iman@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:32:02 by iait-ouf          #+#    #+#             */
/*   Updated: 2025/02/07 17:37:11 by iait-ouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int	check_file(char *str)
{
	int	i;

	i = ft_strlen(str);
	if (i >= 4 && !ft_strncmp(".cub", &str[i - 4], 5))
		return (0);
	return (1);
}

int	set_data(t_data *data, char *file)
{
	int	fd;

	if (check_file(file))
		return (err_msg(data, "extension .cub !!!\n"));
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (err_msg(data, "fail to open file\n"));
	if (set_texture(data, fd))
		return (1);
	if (check_map(data, fd))
		return (1);
	if (close(fd) == -1)
		return (err_msg(data, "fail to close file\n"));
	return (0);
}
