/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 07:04:07 by dande-je          #+#    #+#             */
/*   Updated: 2023/09/13 16:22:31 by dande-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define FD_OPEN_LIMIT 1024
# define NULL_BYTE 1
# define FAIL -1

typedef struct s_buf_hist	t_buf_hist;
struct s_buf_hist
{
	char		buf_char;
	t_buf_hist	*next;
};

typedef struct s_file_info	t_file_info;
struct s_file_info
{
	int			fd;
	ssize_t		i;
	ssize_t		len;
	ssize_t		read;
	char		buf[BUFFER_SIZE];
	t_buf_hist	*buf_hist;
};

char		*get_next_line(int fd);
char		*free_buf(t_buf_hist *buf);
t_buf_hist	*ft_buf_new(char c);
void		ft_add_buf(t_buf_hist **buf_hist, t_buf_hist *buf_new);

#endif
