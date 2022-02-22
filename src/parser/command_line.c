/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 21:45:09 by aabajyan          #+#    #+#             */
/*   Updated: 2022/02/22 17:41:28 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*parser_command_line(t_parser *self)
{
	return (parser_simple_command(self));
}

t_node	*parser_simple_command(t_parser *self)
{
	t_node	*arguments;
	t_node	*result;
	t_node	*temp;

	arguments = NULL;
	parser_ignore_whitespace(self);
	temp = parser_word(self);
	while (temp)
	{
		arguments = node_push(arguments, temp);
		parser_ignore_whitespace(self);
		temp = parser_word(self);
	}
	if (arguments == NULL)
		return (NULL);
	result = node_create(NODE_COMMAND);
	result->arguments = arguments;
	return (result);
}

t_node	*parser_quoted(t_parser *self)
{
	t_node	*in_quote;
	t_node	*result;

	in_quote = NULL;
	while (!parser_match(self, T_DOUBLE_QUOTE | T_EOF))
		in_quote = node_push(in_quote, parser_simple_word(self));
	result = node_create(NODE_QUOTED);
	if (!result)
	{
		node_destroy(in_quote);
		return (NULL);
	}
	result->in_quote = in_quote;
	return (result);
}

t_node	*parser_simple_word(t_parser *self)
{
	bool	is_env;
	t_token	*word;
	t_node	*result;

	is_env = (parser_match(self, T_DOLLAR_SIGN) != NULL);
	word = parser_consume(self, T_EOF | T_WORD | T_WHITESPACE);
	if (!word || word->kind == T_EOF)
		return (NULL);
	if (is_env)
		result = node_create(NODE_VARIABLE);
	else
		result = node_create(NODE_WORD);
	result->value = ft_strdup(word->slice);
	return (result);
}

t_node	*parser_word(t_parser *self)
{
	if (parser_match(self, T_DOUBLE_QUOTE))
		return (parser_quoted(self));
	return (parser_simple_word(self));
}

void	parser_ignore_whitespace(t_parser *self)
{
	while (parser_check(self, T_WHITESPACE))
		parser_advance(self);
}
