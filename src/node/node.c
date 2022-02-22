/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 20:34:11 by aabajyan          #+#    #+#             */
/*   Updated: 2022/02/22 17:34:58 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*node_create(t_node_kind kind)
{
	t_node	*node;

	node = ft_calloc(1, sizeof(t_node));
	if (!node)
		return (NULL);
	node->kind = kind;
	return (node);
}

t_node	*node_last(t_node *self)
{
	while (self != NULL && self->next != NULL)
		self = self->next;
	return (self);
}

t_node	*node_push(t_node *self, t_node *src)
{
	t_node	*last;

	if (self == NULL)
		return (src);
	last = node_last(self);
	last->next = src;
	return (self);
}

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
