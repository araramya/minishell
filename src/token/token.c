/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 20:29:51 by aabajyan          #+#    #+#             */
/*   Updated: 2022/03/10 16:54:52 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Create a token with kind and value.
 * 
 * @param kind 
 * @param slice 
 * @return t_token* 
 */
t_token	*token_create(t_token_kind kind, char *slice)
{
	t_token	*self;

	self = ft_calloc(1, sizeof(t_token));
	if (self == NULL)
		return (NULL);
	self->kind = kind;
	self->slice = slice;
	return (self);
}

/**
 * @brief Recursively destroy tokens with it's values.
 * 
 * @param self 
 */
void	token_destroy(t_token *self)
{
	if (self == NULL)
		return ;
	if (self->next != NULL)
		token_destroy(self->next);
	if (self->slice != NULL)
		free(self->slice);
	free(self);
}

/**
 * @brief Returns the last element of the token.
 * 
 * @param self 
 * @return t_token* 
 */
t_token	*token_last(t_token *self)
{
	while (self != NULL && self->next != NULL)
		self = self->next;
	return (self);
}

/**
 * @brief Pushes the token to the destination.
 * 
 * @param self 
 * @param src 
 * @return t_token* 
 */
t_token	*token_push(t_token *self, t_token *src)
{
	t_token	*last;

	if (self == NULL)
		return (src);
	last = token_last(self);
	last->next = src;
	return (self);
}

/**
 * @brief Prints the token for debugging purposes.
 * 
 * @param self 
 * @param indent 
 */
void	token_print(t_token *self)
{
	if (self != NULL)
	{
		printf("%s: '%s'\n", token_kind_to_string(self->kind), self->slice);
		if (self->next != NULL)
			token_print(self->next);
	}
}
