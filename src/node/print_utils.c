/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 01:03:39 by aabajyan          #+#    #+#             */
/*   Updated: 2022/03/05 16:58:09 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Prints a whitespace indent * 2 times
 * 
 * @param indent 
 */
void	node_print_indent(int indent)
{
	indent *= 2;
	while (indent-- > 0)
		printf(" ");
}

/**
 * @brief Prints specidied children if exists
 * 
 * @param node 
 * @param name 
 * @param indent 
 */
void	node_print_children(t_node *node, char *name, int indent)
{
	if (node)
	{
		node_print_indent(indent);
		printf("%s:\n", name);
		node_print(node, indent + 1);
	}
}

/**
 * @brief Prints a value if exists
 * 
 * @param name 
 * @param value 
 * @param indent 
 */
void	node_print_value(char *name, char *value, int indent)
{
	if (name && value)
	{
		node_print_indent(indent);
		printf("%s: '%s'\n", name, value);
	}
}

t_node	*node_create_value(t_node_kind kind, char *value)
{
	t_node	*node;

	node = node_create(kind);
	if (!node)
		return (NULL);
	node->value = ft_strdup(value);
	return (node);
}
