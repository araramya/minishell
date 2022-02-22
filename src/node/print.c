/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 21:23:12 by aabajyan          #+#    #+#             */
/*   Updated: 2022/02/22 17:43:54 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	node_print_indent(int indent)
{
	indent *= 2;
	while (indent-- > 0)
		write(1, " ", 1);
}

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
	if (self->arguments)
	{
		node_print_indent(indent);
		printf("arguments:\n");
		node_print(self->arguments, indent + 1);
	}
	if (self->in_quote)
	{
		node_print_indent(indent);
		printf("in_quote:\n");
		node_print(self->in_quote, indent + 1);
	}
	if (self->next)
		node_print(self->next, indent - 1);
}
