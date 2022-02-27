/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 23:49:49 by aabajyan          #+#    #+#             */
/*   Updated: 2022/02/27 17:27:19 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**interpreter_eval(t_shell *self, t_node *node)
{
	char	**result;
	size_t	size;
	size_t	index;

	while ((node->kind & NODE_BINARY) != 0)
	{
		self->env = env_set(self->env, node->lhs->value, node->rhs->value);
		node = node->next;
	}
	size = node_size(node);
	if (size == 0)
		return (NULL);
	result = ft_calloc(size + 1, sizeof(char *));
	index = 0;
	while (index < size)
	{
		result[index++] = interpreter_node(self, node);
		node = node->next;
	}
	result[index] = NULL;
	return (result);
}

char	*interpreter_node(t_shell *self, t_node *node)
{
	if (!node)
		return (NULL);
	if ((node->kind & NODE_WORD) != 0)
		return (ft_strdup(node->value));
	if ((node->kind & NODE_VARIABLE) != 0)
		return (ft_strdup(getenv(node->value)));
	if ((node->kind & NODE_QUOTED) != 0)
		return (interpreter_quoted(self, node->in_quote));
	if ((node->kind & NODE_BINARY) != 0)
		return (interpreter_binary(self, node));
	return (NULL);
}

char	*interpreter_quoted(t_shell *self, t_node *node)
{
	t_string	string;
	char		*result;
	char		*temp;

	string_init(&string);
	while (node)
	{
		temp = interpreter_node(self, node);
		string_push(&string, temp);
		free(temp);
		node = node->next;
	}
	result = ft_strdup(string.buffer);
	string_deinit(&string);
	return (result);
}

char	*interpreter_binary(t_shell *self, t_node *node)
{
	t_string	buffer;
	char		*result;

	(void)self;
	string_init(&buffer);
	string_push(&buffer, node->lhs->value);
	string_push(&buffer, "=");
	string_push(&buffer, node->rhs->value);
	result = ft_strdup(buffer.buffer);
	string_deinit(&buffer);
	return (result);
}
