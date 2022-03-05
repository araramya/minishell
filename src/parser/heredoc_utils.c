/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 10:09:48 by aabajyan          #+#    #+#             */
/*   Updated: 2022/03/05 10:10:17 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parser_join_values(t_node *node)
{
	t_string	string;

	string_init(&string);
	while (node)
	{
		if ((node->kind & NODE_VARIABLE) != 0)
			string_push(&string, "$");
		if (node->value)
			string_push(&string, node->value);
		node = node->merged;
	}
	return (string_freeze(&string));
}

char	*parser_get_identifer(t_parser *self)
{
	t_node	*identifer;
	char	*string;

	identifer = parser_word(self);
	if (!identifer)
		return (NULL);
	string = parser_join_values(identifer);
	node_destroy(identifer);
	return (string);
}
