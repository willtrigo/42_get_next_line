/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 07:04:07 by dande-je          #+#    #+#             */
/*   Updated: 2026/06/15 22:25:33 by dande-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file get_next_line_bonus.h
 * @brief Header file for the get_next_line function.
 *
 * This module implements a function that reads a line from a file descriptor
 * without knowing its size in advance. It supports multiple simultaneous
 * file descriptors and uses a linked list to accumulate characters efficiently.
 *
 * @note The behavior is undefined if BUFFER_SIZE is set to 0 or negative.
 * @note Compile with `-DBUFFER_SIZE=<value>` to customize the read buffer size.
 */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define FD_OPEN_LIMIT 1024
# define NULL_TERMINATOR 1
# define READ_ERROR -1

/**
 * @struct s_node
 * @brief Node of the singly linked list used to build lines character
 * by character.
 */
typedef struct s_node	t_node;
struct s_node
{
	char	chr;
	t_node	*next;
};

/**
 * @struct s_file
 * @brief Internal state structure for each file descriptor.
 *
 * This structure maintains the reading state for a specific file descriptor,
 * allowing get_next_line to work correctly with multiple fds simultaneously.
 */
typedef struct s_file	t_file;
struct s_file
{
	int			fd;
	ssize_t		cursor;
	ssize_t		line_len;
	ssize_t		bytes_read;
	char		raw_buf[BUFFER_SIZE];
	t_node		*history;
};

/**
 * @brief Reads the next line from a file descriptor.
 *
 * Returns a line (including the terminating newline if present)
 * read from the given file descriptor. The line is allocated with malloc()
 * and must be freed by the caller.
 *
 * @param fd The file descriptor to read from.
 * @return 
 * - The line that was read (including '\\n' if present), or
 * - NULL if an error occurred, EOF was reached, or fd is invalid.
 */
char		*get_next_line(int fd);

/* -------------------------------------------------------------------------- */
/*  Utility functions (internal)                                              */
/* -------------------------------------------------------------------------- */

char		*ft_flush_history(t_node **history);
t_node		*ft_node_new(char chr);
void		ft_node_append(t_node **history, t_node *node);

#endif  // GET_NEXT_LINE_BONUS_H
