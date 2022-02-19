/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 19:31:57 by aabajyan          #+#    #+#             */
/*   Updated: 2022/02/19 19:32:03 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_calloc(size_t el_num, size_t el_size)
{
	void	*ptr;

	if (el_num == 0 && el_size == 0)
	{
		el_num = 1;
		el_size = 1;
	}
	ptr = malloc(el_num * el_size);
	if (ptr)
		ft_memcpy(ptr, 0, el_num * el_size);
	return (ptr);
}
