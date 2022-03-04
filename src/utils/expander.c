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

char	**expander_eval(t_node *node)
{
	char	**result;
	size_t	size;
	size_t	i;
	size_t	j;
	char	*temp;

	size = node_size(node);
	if (size == 0)
		return (NULL);
	result = ft_calloc(size + 1, sizeof(char *));
	i = 0;
	j = 0;
	while (i++ < size)
	{
		temp = expander_node(node);
		if (temp)
			result[j++] = temp;
		node = node->next;
	}
	result[j] = NULL;
	return (result);
}

static char	*expander_simple_word(t_node *node)
{
	char		*temp;
	t_string	string;

	if ((node->kind & NODE_VARIABLE) != 0)
	{
		if (!(ft_isalnum(node->value[0]) || node->value[0] == '?'))
		{
			string_init(&string);
			string_push(&string, "$");
			string_push(&string, node->value);
			return (string_freeze(&string));
		}
		temp = env_get(node->value);
		if (!temp)
			return (NULL);
		return (ft_strdup(temp));
	}
	if ((node->kind & NODE_QUOTED) != 0)
		return (expander_quoted(node->in_quote));
	return (ft_strdup(node->value));
}

char	*expander_word(t_node *node)
{
	t_string	temp;
	t_node		*merge;
	char		*temp_value;

	string_init(&temp);
	temp_value = expander_simple_word(node);
	string_push(&temp, temp_value);
	free(temp_value);
	merge = node->merged;
	while (merge)
	{
		temp_value = expander_simple_word(merge);
		if (temp_value)
		{
			string_push(&temp, temp_value);
			free(temp_value);
		}
		merge = merge->merged;
	}
	return (string_freeze(&temp));
}

char	*expander_node(t_node *node)
{
	if (!node)
		return (NULL);
	if ((node->kind & (NODE_WORD | NODE_VARIABLE | NODE_QUOTED)) != 0)
		return (expander_word(node));
	return (NULL);
}

char	*expander_quoted(t_node *node)
{
	t_string	string;
	char		*temp;

	string_init(&string);
	string_push(&string, "");
	while (node)
	{
		temp = expander_node(node);
		string_push(&string, temp);
		free(temp);
		node = node->next;
	}
	return (string_freeze(&string));
}
