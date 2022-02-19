/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 19:31:38 by aabajyan          #+#    #+#             */
/*   Updated: 2022/02/19 19:31:47 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_memset(void *buffer, int c, size_t size)
{
	char			*cb;
	unsigned int	i;

	cb = buffer;
	i = 0;
	while (i < size)
		cb[i++] = c;
	return (cb);
}
