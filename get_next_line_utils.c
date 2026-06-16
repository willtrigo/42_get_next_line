/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dande-je <dande-je@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 06:22:34 by dande-je          #+#    #+#             */
/*   Updated: 2026/06/15 22:35:35 by dande-je         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file get_next_line_utils.c
 * @brief Utility functions for get_next_line.
 */

#include "get_next_line.h"

/**
 * @brief Appends a node to the end of the linked list.
 *
 * @param history Pointer to the head of the list.
 * @param node Node to append.
 */
void	ft_node_append(t_node **history, t_node *node)
{
	t_node	*tail;

	if (!node)
		return ;
	if (!*history)
	{
		*history = node;
		return ;
	}
	tail = *history;
	while (tail->next)
		tail = tail->next;
	tail->next = node;
}

/**
 * @brief Creates a new node containing a single character.
 *
 * @param chr Character to store.
 * @return Pointer to the new node, or NULL on allocation failure.
 */
t_node	*ft_node_new(char chr)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->chr = chr;
	node->next = NULL;
	return (node);
}

/**
 * @brief Frees all nodes in the history list and resets the pointer.
 *
 * @param history Pointer to the head pointer of the list.
 * @return Always returns NULL (for convenience in error paths).
 */
char	*ft_flush_history(t_node **history)
{
	t_node	*next;
	t_node	*current;

	current = *history;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*history = NULL;
	return (NULL);
}
