/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 23:49:49 by aabajyan          #+#    #+#             */
/*   Updated: 2022/02/27 17:35:47 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**expander_eval(t_shell *self, t_node *node)
{
	char	**result;
	size_t	size;
	size_t	index;

	size = node_size(node);
	if (size == 0)
		return (NULL);
	result = ft_calloc(size + 1, sizeof(char *));
	index = 0;
	while (index < size)
	{
		result[index++] = expander_node(self, node);
		node = node->next;
	}
	result[index] = NULL;
	return (result);
}

static char	*expander_word(t_shell *self, t_node *node)
{
	t_string	temp;
	char		*result;
	t_node		*merge;
	char		*temp_value;

	string_init(&temp);
	string_push(&temp, node->value);
	merge = node->merged;
	while (merge)
	{
		temp_value = expander_node(self, merge);
		if (temp_value)
		{
			string_push(&temp, temp_value);
			free(temp_value);
		}
		merge = merge->merged;
	}
	result = ft_strdup(temp.buffer);
	string_deinit(&temp);
	return (result);
}

char	*expander_node(t_shell *self, t_node *node)
{
	if (!node)
		return (NULL);
	if ((node->kind & NODE_WORD) != 0)
		return (expander_word(self, node));
	if ((node->kind & NODE_VARIABLE) != 0)
		return (ft_strdup(getenv(node->value)));
	if ((node->kind & NODE_QUOTED) != 0)
		return (expander_quoted(self, node->in_quote));
	return (NULL);
}

char	*expander_quoted(t_shell *self, t_node *node)
{
	t_string	string;
	char		*result;
	char		*temp;

	string_init(&string);
	while (node)
	{
		temp = expander_node(self, node);
		string_push(&string, temp);
		free(temp);
		node = node->next;
	}
	result = ft_strdup(string.buffer);
	string_deinit(&string);
	return (result);
}
