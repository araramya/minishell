/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 19:41:46 by aabajyan          #+#    #+#             */
/*   Updated: 2022/02/19 19:47:40 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	string_init(t_string *self)
{
	self->buffer = NULL;
	self->capacity = 0;
	self->size = 0;
}

int	string_push(t_string *self, const char *src)
{
	size_t	size;

	if (!(self && src))
		return (1);
	size = ft_strlen(src);
	if (self->capacity < self->size + size)
	{
		self->capacity += size;
		self->buffer = ft_realloc(self->buffer, self->capacity);
		if (!self->buffer)
			return (1);
	}
	while (*src != '\0')
		self->buffer[self->size++] = *src++;
	self->buffer[self->size] = '\0';
	return (0);
}

int	string_deinit(t_string *self)
{
	if (!self)
		return (1);
	if (self->buffer)
	{
		free(self->buffer);
		self->buffer = NULL;
	}
	return (0);
}
