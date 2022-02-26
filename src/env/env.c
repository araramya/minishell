/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 17:34:13 by aabajyan          #+#    #+#             */
/*   Updated: 2022/02/26 22:51:39 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_create(char *name, char *value)
{
	t_env	*env;

	env = ft_calloc(1, sizeof(t_env));
	if (!env)
		return (NULL);
	env->name = ft_strdup(name);
	env->value = ft_strdup(value);
	env->next = NULL;
	return (env);
}

t_env	*env_last(t_env *self)
{
	while (self != NULL && self->next != NULL)
		self = self->next;
	return (self);
}

t_env	*env_push(t_env *self, t_env *src)
{
	t_env	*last;

	if (self == NULL)
		return (src);
	last = env_last(self);
	last->next = src;
	return (last->next);
}

t_env	*env_set(t_env *self, char *name, char *value)
{
	t_env	*find;

	find = env_find(self, name);
	if (find)
	{
		if (find->value)
			free(find->value);
		find->value = ft_strdup(value);
		return (find);
	}
	return (env_push(self, env_create(name, value)));
}

void	env_destroy(t_env *self, bool recursive)
{
	if (!self)
		return ;
	if (self->next && recursive)
		env_destroy(self->next, recursive);
	if (self->name)
		free(self->name);
	if (self->value)
		free(self->value);
	free(self);
}
