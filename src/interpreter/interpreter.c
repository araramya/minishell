/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 23:49:49 by aabajyan          #+#    #+#             */
/*   Updated: 2022/02/27 00:30:56 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	interpreter_eval(t_shell *self, t_node *node)
{
	(void)self;
	(void)node;
	return (0);
}

char	*interpreter_variable(t_shell *self, t_node *node)
{
	return (env_get(self->env, node->value));
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

char	*interpreter_word(t_shell *self, t_node *node)
{
	(void)self;
	return (node->value);
}
