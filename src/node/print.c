/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 21:23:12 by aabajyan          #+#    #+#             */
/*   Updated: 2022/02/24 01:06:45 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Converts an enum into string.
 * 
 * @param kind 
 * @return const char* 
 */
const char	*node_kind_to_string(t_node_kind kind)
{
	if ((kind & NODE_COMMAND) != 0)
		return ("NODE_COMMAND");
	if ((kind & NODE_WORD) != 0)
		return ("NODE_WORD");
	if ((kind & NODE_VARIABLE) != 0)
		return ("NODE_VARIABLE");
	if ((kind & NODE_QUOTED) != 0)
		return ("NODE_QUOTED");
	if ((kind & NODE_BINARY) != 0)
		return ("NODE_BINARY");
	return ("NODE_UNKNOWN");
}

/**
 * @brief Prints binary information
 * 
 * @param self 
 * @param indent 
 */
static void	node_print_binary(t_node *self, int indent)
{
	if (self->lhs && self->rhs)
	{
		node_print_indent(indent);
		printf("binary:\n");
		node_print_indent(indent + 1);
		printf("kind: %s\n", binary_kind_to_string(self->binary_kind));
		node_print_children(self->lhs, "lhs", indent + 1);
		node_print_children(self->rhs, "rhs", indent + 1);
	}
}

/**
 * @brief Prints redirect information
 * 
 * @param self 
 * @param indent 
 */
static void	node_print_redirect(t_node *self, int indent)
{
	if (self->target)
	{
		node_print_indent(indent);
		printf("redirect:\n");
		node_print_indent(indent + 1);
		printf("kind: %s\n", redirect_kind_to_string(self->redirect_kind));
		node_print_children(self->target, "target", indent + 1);
	}
}

/**
 * @brief Prints the node for debugging purposes.
 * 
 * @param self 
 * @param indent 
 */
void	node_print(t_node *self, int indent)
{
	if (!self)
		return ;
	node_print_indent(indent++);
	printf("@%s\n", node_kind_to_string(self->kind));
	node_print_value("value", self->value, indent);
	node_print_children(self->arguments, "arguments", indent);
	node_print_children(self->in_quote, "in_quote", indent);
	node_print_children(self->pipe, "pipe", indent);
	node_print_binary(self, indent);
	node_print_redirect(self, indent);
	node_print_children(self->next, "next", indent - 1);
}
