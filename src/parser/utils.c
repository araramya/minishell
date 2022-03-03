/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 22:35:21 by aabajyan          #+#    #+#             */
/*   Updated: 2022/03/03 22:35:24 by aabajyan         ###   ########.fr       */
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

t_token	*parser_notmatch(t_parser *self, t_token_kind kind)
{
	if (!parser_check(self, kind))
		return (parser_advance(self));
	return (NULL);
}
