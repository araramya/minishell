/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 20:15:18 by aabajyan          #+#    #+#             */
/*   Updated: 2022/02/22 17:52:16 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Parses list of tokens into a Node Tree
 * 
 * @param self 
 * @param tokens 
 * @return t_node* 
 */
t_node	*parser_parse(t_parser *self, t_token *tokens)
{
	t_node	*result;
	t_node	*node;

	result = NULL;
	self->tokens = tokens;
	self->current = tokens;
	self->error = false;
	self->index = 0;
	if (!parser_consume(self, T_BEGIN))
		return (NULL);
	while (self->current && self->current->kind != T_EOF && !self->error)
	{
		node = parser_command_line(self);
		if (!node)
			break ;
		result = node_push(result, node);
	}
	return (result);
}

/**
 * @brief Advances to the next token if there's one
 * 
 * @param self 
 * @return t_token* 
 */
t_token	*parser_advance(t_parser *self)
{
	t_token	*temp;

	temp = self->current;
	if (self->current->kind != T_EOF)
	{
		self->current = self->current->next;
		self->index++;
	}
	return (temp);
}

/**
 * @brief Check if the current token is specific kind
 * 
 * @param self 
 * @param kind 
 * @return t_token* 
 */
t_token	*parser_check(t_parser *self, t_token_kind kind)
{
	if ((self->current->kind & kind) != 0)
		return (self->current);
	return (NULL);
}

/**
 * @brief Check if the current token is specific kind.
 * If so advance to the next token.
 * 
 * @param self 
 * @param kind 
 * @return t_token* 
 */
t_token	*parser_match(t_parser *self, t_token_kind kind)
{
	if (parser_check(self, kind))
		return (parser_advance(self));
	return (NULL);
}

#define FORMAT "Parser error: Expected %s, but got %s at index %d.\n"

/**
 * @brief Check if the current token is specific kind.
 * If so advance to the next token. Or else throw an error.
 * 
 * @param self 
 * @param kind 
 * @return t_token* 
 */
t_token	*parser_consume(t_parser *self, t_token_kind kind)
{
	const char	*expected;
	const char	*actual;

	if (self->error)
		return (NULL);
	if (parser_check(self, kind) != NULL)
		return (parser_advance(self));
	expected = token_kind_to_string(kind);
	actual = token_kind_to_string(self->current->kind);
	printf(FORMAT, expected, actual, self->index);
	self->error = true;
	return (NULL);
}

#undef FORMAT
