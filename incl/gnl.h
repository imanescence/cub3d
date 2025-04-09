/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-ouf <aitouflih.iman@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 19:53:19 by iait-ouf          #+#    #+#             */
/*   Updated: 2025/02/07 19:54:11 by iait-ouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H

# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "cub3d.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 10240
# endif

# if BUFFER_SIZE >= INT_MAX
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char	*gnl(int fd);
char	*get_next_line(int fd);
char	*ft_strchr(char *s, char c);
void	ft_strmov(char *s1, char *s2);
char	*read_line(int fd, char *buffer);
char	*ft_strnjoin(char *s1, char *s2, int n);
char	*ft_get_line(char *s1);
char	*gnl_return(char *line);
void	gnl_init(int *bytes_read, char **tmpline, char **tmpbuf);

#endif
