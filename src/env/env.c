/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araramya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 17:34:13 by aabajyan          #+#    #+#             */
/*   Updated: 2022/03/06 15:58:21 by araramya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	**g_env = NULL;

char	**env_to_string(void)
{
	size_t	i;
	size_t	j;
	t_env	*entry;
	char	**result;

	result = ft_calloc(TABLE_SIZE, sizeof(char *));
	i = 0;
	j = 0;
	while (i < TABLE_SIZE)
	{
		entry = g_env[i++];
		while (entry)
		{
			if (ft_strcmp("?", entry->key) != 0)
				result[j++] = env_item_to_string(entry);
			entry = entry->next;
		}
	}
	result[j] = NULL;
	return (result);
}

void	env_set(char *key, char *value)
{
	size_t	bucket;
	t_env	*entry;
	t_env	*prev;

	bucket = env_hash(key);
	entry = g_env[bucket];
	if (value == NULL)
		return (env_unset(&g_env, key));
	if (!entry)
	{
		g_env[bucket] = env_pair(key, value);
		return ;
	}
	while (entry)
	{
		if (ft_strcmp(entry->key, key) == 0)
		{
			free(entry->value);
			entry->value = ft_strdup(value);
			return ;
		}
		prev = entry;
		entry = entry->next;
	}
	prev->next = env_pair(key, value);
}

char	*env_get(char *key)
{
	size_t	bucket;
	t_env	*entry;

	bucket = env_hash(key);
	entry = g_env[bucket];
	while (entry)
	{
		if (ft_strcmp(entry->key, key) == 0)
			return (entry->value);
		entry = entry->next;
	}
	return (NULL);
}

void	env_init(void)
{
	size_t	i;

	if (g_env)
		env_deinit();
	g_env = malloc(TABLE_SIZE * sizeof(t_env));
	i = 0;
	while (i < TABLE_SIZE)
		g_env[i++] = NULL;
}

void	env_deinit(void)
{
	size_t	i;

	if (!g_env)
		return ;
	i = 0;
	while (i < TABLE_SIZE)
	{
		if (g_env[i] != NULL)
			env_destroy(g_env[i]);
		++i;
	}
	free(g_env);
	g_env = NULL;
}
