/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 22:35:21 by aabajyan          #+#    #+#             */
/*   Updated: 2022/03/10 18:08:55 by aabajyan         ###   ########.fr       */
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
 * @brief Same as parser match, but only advances if it doesn't match
 * 
 * @param self 
 * @param kind 
 * @return t_token* 
 */
t_token	*parser_notmatch(t_parser *self, t_token_kind kind)
{
	if (!parser_check(self, kind))
		return (parser_advance(self));
	return (NULL);
}

t_token	*parser_check2(t_parser *self, t_token_kind kind)
{
	while (parser_check(self, T_WHITESPACE))
		parser_advance(self);
	return (parser_check(self, kind));
}

/**
 * @brief Initialize a parser
 * 
 * @param self 
 * @param tokens 
 */
void	parser_init(t_parser *self, t_token *tokens)
{
	self->tokens = tokens;
	self->current = tokens;
	self->error = false;
	self->in_quote = false;
	self->is_env = false;
	self->heredoc = false;
	self->index = 0;
	self->heredoc_exit = 0;
}

/**
 * @brief Write an error message and destroy node if exists
 * 
 * @param self 
 * @param message 
 * @param node 
 * @return t_node* 
 */
t_node	*parser_error(t_parser *self, char *message, t_node *node)
{
	if (self->error)
		return (NULL);
	ft_putstr_fd("Parser error: ", 2);
	ft_putstr_fd(message, 2);
	ft_putchar_fd('\n', 2);
	if (node)
		node_destroy(node);
	self->error = true;
	return (NULL);
}
