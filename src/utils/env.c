/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 19:14:55 by aabajyan          #+#    #+#             */
/*   Updated: 2022/02/24 19:27:45 by aabajyan         ###   ########.fr       */
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

t_env	*env_find(t_env *self, char *name)
{
	while (self)
	{
		if (ft_strcmp(name, self->name) == 0)
			return (self);
		self = self->next;
	}
	return (NULL);
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
