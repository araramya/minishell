/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 00:32:01 by aabajyan          #+#    #+#             */
/*   Updated: 2022/02/23 20:53:16 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Same as parser_match, but it ignores all whitespaces
 * 
 * @param self 
 * @param kind 
 * @return t_token* 
 */
t_token	*parser_match2(t_parser *self, t_token_kind kind)
{
	while (parser_check(self, T_WHITESPACE))
		parser_advance(self);
	return (parser_match(self, kind));
}

/**
 * @brief Parse a quoted string
 * 
 * quoted -> T_DOUBLE_QUOTE simple_word+ T_DOUBLE_QUOTE
 * 
 * @param self 
 * @return t_node* 
 */
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

/**
 * @brief Parse a simple word
 * 
 * simple_word -> T_DOLLAR_SIGN? T_WORD | T_WHITESPACE
 * 
 * @param self 
 * @return t_node* 
 */
t_node	*parser_simple_word(t_parser *self)
{
	bool	is_env;
	t_token	*word;
	t_node	*result;

	is_env = (parser_match(self, T_DOLLAR_SIGN) != NULL);
	word = parser_match(self, T_EOF | T_WORD | T_WHITESPACE | T_EQUALS);
	if (!word || word->kind == T_EOF)
		return (NULL);
	if (is_env)
		result = node_create(NODE_VARIABLE);
	else
		result = node_create(NODE_WORD);
	result->value = ft_strdup(word->slice);
	if (parser_check(self, T_WORD | T_DOLLAR_SIGN))
		result->next = parser_simple_word(self);
	return (result);
}

/**
 * @brief Parse a binary
 * 
 * binary -> simple_word = simple_word
 * 
 * @param self 
 * @return t_node* 
 */
t_node	*parser_binary(t_parser *self)
{
	t_node	*word;
	t_node	*result;
	t_token	*check;

	word = parser_simple_word(self);
	check = parser_match(self, T_EQUALS);
	if (check && !parser_check(self, T_WHITESPACE))
	{
		result = node_create(NODE_BINARY);
		result->lhs = word;
		result->rhs = parser_simple_word(self);
		result->binary_kind = token_kind_to_binary_kind(check->kind);
		return (result);
	}
	return (word);
}

/**
 * @brief Parse a word
 * 
 * word -> simple_word | quoted
 * 
 * @param self 
 * @return t_node* 
 */
t_node	*parser_word(t_parser *self)
{
	if (parser_match2(self, T_DOUBLE_QUOTE))
		return (parser_quoted(self));
	return (parser_binary(self));
}