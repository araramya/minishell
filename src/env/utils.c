/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 17:35:48 by aabajyan          #+#    #+#             */
/*   Updated: 2022/03/02 16:20:06 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_pair(char *key, char *value)
{
	t_env	*env;

	env = ft_calloc(1, sizeof(t_env));
	if (!env)
		return (NULL);
	env->key = ft_strdup(key);
	env->value = ft_strdup(value);
	env->next = NULL;
	return (env);
}

size_t	env_hash(char *key)
{
	size_t	value;
	size_t	length;
	size_t	i;

	value = 0;
	length = ft_strlen(key);
	i = 0;
	while (i < length)
		value *= 37 + key[i++];
	return (value % TABLE_SIZE);
}

void	env_destroy(t_env *env)
{
	if (!env)
		return ;
	if (env->next)
		env_destroy(env->next);
	if (env->key)
		free(env->key);
	if (env->value)
		free(env->value);
	free(env);
}

void	env_unset(t_env ***env, char *key)
{
	size_t	bucket;
	t_env	*entry;
	t_env	*prev;

	bucket = env_hash(key);
	entry = *env[bucket];
	prev = NULL;
	while (entry)
	{
		if (ft_strcmp(entry->key, key) == 0)
		{
			if (prev)
				prev->next = entry->next;
			free(entry->key);
			free(entry->value);
			free(entry);
			if (!prev)
				*env[bucket] = NULL;
			return ;
		}
		prev = entry;
		entry = entry->next;
	}
}
