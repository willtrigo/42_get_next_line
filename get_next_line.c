/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 06:22:06 by dande-je          #+#    #+#             */
/*   Updated: 2023/09/01 07:56:56 by dande-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*get_next_line(int fd)
{
	static t_file_info	file;
	size_t				buf_len;
	ssize_t				i;
	char				*buf_hist_temp;
	size_t				buf_hist_temp_len;

	if (!fd || BUFFER_SIZE == 0)
		return (NULL);
	i = -1;
	file.fd = fd;
	// free(file.buf);
	file.buf = calloc(sizeof(char), BUFFER_SIZE + 1);
	file.read = read(file.fd, file.buf, BUFFER_SIZE);
	if (file.read == -1)
		return (NULL);
	buf_len = ft_strlen(file.buf);
	if (file.read == 0)
		return (NULL);
	if (file.buf_hist == NULL)
	{
		file.buf_hist = malloc(sizeof(char) * buf_len + 1);
		if (!file.buf_hist)
			return (NULL);
		file.buf_hist = ft_strjoin("", file.buf);
		// free(file.buf);
	}
	else
	{
		buf_hist_temp_len = ft_strlen(file.buf_hist);
		buf_hist_temp = malloc(sizeof(char) * (buf_len + buf_hist_temp_len + 1));
		if (!buf_hist_temp)
			return (NULL);
		buf_hist_temp = ft_strjoin("", file.buf_hist);
		free(file.buf_hist);
		file.buf_hist = malloc(sizeof(char) * buf_len + buf_hist_temp_len + 1);
		if (!file.buf_hist)
			return (NULL);
		file.buf_hist = ft_strjoin(buf_hist_temp, file.buf);
		free(buf_hist_temp);
	}
	free(file.buf);
	return (file.buf_hist);
}
