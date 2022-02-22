/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 20:34:11 by aabajyan          #+#    #+#             */
/*   Updated: 2022/02/22 18:13:15 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Creates a node with specific type.
 * 
 * @param kind 
 * @return t_node* 
 */
t_node	*node_create(t_node_kind kind)
{
	t_node	*node;

	node = ft_calloc(1, sizeof(t_node));
	if (!node)
		return (NULL);
	node->kind = kind;
	return (node);
}

/**
 * @brief Returns the last element of the node.
 * 
 * @param self 
 * @return t_node* 
 */
t_node	*node_last(t_node *self)
{
	while (self != NULL && self->next != NULL)
		self = self->next;
	return (self);
}

/**
 * @brief Pushes the node to the destination.
 * 
 * @param self 
 * @param src 
 * @return t_node* 
 */
t_node	*node_push(t_node *self, t_node *src)
{
	t_node	*last;

	if (self == NULL)
		return (src);
	last = node_last(self);
	last->next = src;
	return (self);
}

/**
 * @brief Recursively destroy all values in the node
 * 
 * @param self 
 */
void	node_destroy(t_node *self)
{
	if (self == NULL)
		return ;
	if (self->arguments != NULL)
		node_destroy(self->arguments);
	if (self->next != NULL)
		node_destroy(self->next);
	if (self->in_quote != NULL)
		node_destroy(self->in_quote);
	if (self->value != NULL)
		free(self->value);
	free(self);
}
