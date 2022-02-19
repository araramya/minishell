/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 20:29:51 by aabajyan          #+#    #+#             */
/*   Updated: 2022/02/19 20:33:48 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_token	*token_last(t_token *self)
{
	while (self != NULL && self->next != NULL)
		self = self->next;
	return (self);
}

t_token	*token_push(t_token *self, t_token *src)
{
	t_token	*last;

	if (self == NULL)
		return (src);
	last = token_last(self);
	last->next = src;
	return (last->next);
}

void	token_print(t_token *self)
{
	if (self != NULL)
	{
		printf("%s: '%s'\n", token_kind_to_string(self->kind), self->slice);
		if (self->next != NULL)
			token_print(self->next);
	}
}
