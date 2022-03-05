/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 19:41:46 by aabajyan          #+#    #+#             */
/*   Updated: 2022/03/05 02:41:45 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Initialises string struct.
 * 
 * @param self 
 */
void	string_init(t_string *self)
{
	self->buffer = NULL;
	self->capacity = 0;
	self->size = 0;
}

/**
 * @brief Pushes a string into the struct.
 * 
 * @param self 
 * @param src 
 * @return int 
 */
int	string_push(t_string *self, const char *src)
{
	size_t	size;

	size = ft_strlen(src);
	if (!(self && size > 0))
	{
		if (self->buffer == NULL && src)
		{
			self->buffer = ft_calloc(1, sizeof(char));
			self->buffer[0] = '\0';
		}
		return (1);
	}
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

int	string_move(t_string *self, char *src)
{
	if (!src)
		return (1);
	string_push(self, src);
	free(src);
	return (0);
}

/**
 * @brief Deinitialises the string struct and frees the buffer.
 * 
 * @param self 
 * @return int 
 */
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

/**
 * @brief Converts struct ot char*
 * 
 * @param self 
 * @return char* 
 */
char	*string_freeze(t_string *self)
{
	char	*result;

	if (self->buffer == NULL)
		result = NULL;
	else
		result = ft_strdup(self->buffer);
	string_deinit(self);
	return (result);
}
