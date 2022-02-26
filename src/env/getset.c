/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 17:35:48 by aabajyan          #+#    #+#             */
/*   Updated: 2022/02/26 22:51:42 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*env_get(t_env *self, char *name)
{
	t_env	*env;

	env = env_find(self, name);
	if (env)
		return (env->value);
	env = env_push(self, env_create(name, getenv(name)));
	if (env)
		return (env->value);
	return (NULL);
}

t_env	*env_unset(t_env *self, char *name)
{
	t_env	*env;
	t_env	*target;

	env = self;
	target = NULL;
	if (self && ft_strcmp(self->name, name) == 0)
	{
		env_destroy(self, true);
		return (NULL);
	}
	while (env)
	{
		if (env->next && ft_strcmp(env->next->value, name) == 0)
		{
			target = env->next;
			break ;
		}
		env = env->next;
	}
	if (!target)
		return (self);
	env->next = target->next;
	env_destroy(target, false);
	return (env);
}
