/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 06:22:06 by dande-je          #+#    #+#             */
/*   Updated: 2023/09/13 16:23:09 by dande-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_buf(t_file_info *file);
char	*ft_print_line(t_file_info *file);

char	*get_next_line(int fd)
{
	static t_file_info	file[FD_OPEN_LIMIT];

	if ((!fd || fd > FD_OPEN_LIMIT || fd < 0) && fd != 0)
		return (NULL);
	if (file[fd].i >= file[fd].read || file[fd].i == 0)
	{
		file[fd].i = 0;
		while (file[fd].i < BUFFER_SIZE)
			file[fd].buf[file[fd].i++] = '\0';
		file[fd].i = 0;
		file[fd].len = 0;
		file[fd].fd = fd;
		file[fd].buf_hist = NULL;
		file[fd].read = read(fd, file[fd].buf, BUFFER_SIZE);
		if (file[fd].read == FAIL)
			return (free_buf(file[fd].buf_hist));
	}
	if (file[fd].read <= 0 || file[fd].buf[file[fd].i] == '\0')
		return (free_buf(file[fd].buf_hist));
	if (file[fd].read < 0 && file[fd].buf_hist)
		return (free_buf(file[fd].buf_hist));
	return (ft_read_buf(&file[fd]));
}

char	*ft_read_buf(t_file_info *file)
{
	file->len = 0;
	while (file->read > 0)
	{
		ft_add_buf(&file->buf_hist, ft_buf_new(file->buf[file->i]));
		if (file->buf[file->i] == '\n' || file->buf[file->i] == '\0')
			break ;
		file->i++;
		file->len++;
		if (file->i >= file->read)
		{
			file->i = 0;
			file->read = read(file->fd, file->buf, BUFFER_SIZE);
			if (file->read == FAIL)
				return (free_buf(file->buf_hist));
		}
	}
	file->i++;
	file->len++;
	return (ft_print_line(file));
}

char	*ft_print_line(t_file_info *file)
{
	t_buf_hist	*buf_hist_temp;
	char		*line;
	size_t		i;

	line = malloc(sizeof(char) * (file->len + NULL_BYTE));
	if (!(line || file->fd) && file->fd != 0)
	{
		free(line);
		return (NULL);
	}
	i = 0;
	buf_hist_temp = NULL;
	while (file->buf_hist)
	{
		buf_hist_temp = file->buf_hist->next;
		line[i++] = file->buf_hist->buf_char;
		free(file->buf_hist);
		file->buf_hist = buf_hist_temp;
	}
	line[i] = '\0';
	return (line);
}
