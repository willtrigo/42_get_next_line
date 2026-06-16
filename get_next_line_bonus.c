/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 06:22:06 by dande-je          #+#    #+#             */
/*   Updated: 2026/06/15 22:27:41 by dande-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file get_next_line_bonus.c
 * @brief Implementation of the get_next_line function.
 */

#include "get_next_line_bonus.h"

static char	*ft_accumulate(t_file *file);
static char	*ft_build_line(t_file *file);

/**
 * @brief Main entry point: reads the next line from a file descriptor.
 *
 * Uses static storage per file descriptor to maintain state across calls.
 *
 * @param fd File descriptor to read from.
 * @return The next line (newly allocated), or NULL on error/EOF.
 */
char	*get_next_line(int fd)
{
	static t_file	files[FD_OPEN_LIMIT];
	t_file			*file;

	if (fd < 0 || fd >= FD_OPEN_LIMIT)
		return (NULL);
	file = &files[fd];
	file->fd = fd;
	if (file->cursor >= file->bytes_read)
	{
		file->cursor = 0;
		file->bytes_read = read(fd, file->raw_buf, BUFFER_SIZE);
		if (file->bytes_read <= 0)
		{
			if (file->history)
				return (ft_build_line(file));
			return (NULL);
		}
	}
	return (ft_accumulate(file));
}

/**
 * @brief Accumulates characters into the history linked list until a newline
 * or EOF.
 *
 * @param file Pointer to the file state structure.
 * @return The complete line, or NULL if memory allocation failed.
 */
static char	*ft_accumulate(t_file *file)
{
	t_node	*node;

	while (file->bytes_read > 0)
	{
		node = ft_node_new(file->raw_buf[file->cursor]);
		if (!node)
			return (ft_flush_history(&file->history));
		ft_node_append(&file->history, node);
		file->line_len++;
		if (file->raw_buf[file->cursor++] == '\n')
			break ;
		if (file->cursor >= file->bytes_read)
		{
			file->cursor = 0;
			file->bytes_read = read(file->fd, file->raw_buf, BUFFER_SIZE);
			if (file->bytes_read == READ_ERROR)
				return (ft_flush_history(&file->history));
		}
	}
	return (ft_build_line(file));
}

/**
 * @brief Builds the final string from the linked list and frees the nodes.
 *
 * @param file Pointer to the file state structure.
 * @return Newly allocated string containing the line, or NULL on error.
 */
static char	*ft_build_line(t_file *file)
{
	char	*line;
	t_node	*current;
	t_node	*next;
	size_t	i;

	if (!file->history)
		return (NULL);
	line = malloc(sizeof(char) * (file->line_len + NULL_TERMINATOR));
	if (!line)
		return (ft_flush_history(&file->history));
	i = 0;
	current = file->history;
	while (current)
	{
		next = current->next;
		line[i++] = current->chr;
		free(current);
		current = next;
	}
	line[i] = '\0';
	file->history = NULL;
	file->line_len = 0;
	return (line);
}
