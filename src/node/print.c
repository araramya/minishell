/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 21:23:12 by aabajyan          #+#    #+#             */
/*   Updated: 2022/02/23 14:57:17 by aabajyan         ###   ########.fr       */
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
	return ("NODE_UNKNOWN");
}

/**
 * @brief Prints a whitespace indent * 2 times
 * 
 * @param indent 
 */
static void	node_print_indent(int indent)
{
	indent *= 2;
	while (indent-- > 0)
		write(1, " ", 1);
}

static void	node_print_children(t_node *node, const char *name, int indent)
{
	if (node)
	{
		node_print_indent(indent);
		printf("%s:\n", name);
		node_print(node, indent + 1);
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
	if (self->value)
	{
		node_print_indent(indent);
		printf("value: '%s'\n", self->value);
	}
	node_print_children(self->arguments, "arguments", indent);
	node_print_children(self->in_quote, "in_quote", indent);
	node_print_children(self->pipe, "pipe", indent);
	if (self->target)
	{
		node_print_indent(indent);
		printf("redirect:\n");
		node_print_indent(indent + 1);
		printf("kind: %s\n", redirect_kind_to_string(self->redirect_kind));
		node_print_children(self->target, "target", indent + 1);
	}
	if (self->next)
		node_print(self->next, indent - 1);
}
