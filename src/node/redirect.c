/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <aabajyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 19:12:53 by aabajyan          #+#    #+#             */
/*   Updated: 2022/02/22 19:24:13 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redirect_kind	token_kind_to_redirect_kind(t_token_kind kind)
{
	if ((kind & T_LESS) != 0)
		return (R_LEFT);
	if ((kind & T_GREAT) != 0)
		return (R_RIGHT);
	if ((kind & T_DOUBLE_LESS) != 0)
		return (R_DOUBLE_LEFT);
	if ((kind & T_DOUBLE_GREAT) != 0)
		return (R_DOUBLE_RIGHT);
	return (R_NONE);
}

const char	*redirect_kind_to_string(t_redirect_kind kind)
{
	if ((kind & R_LEFT) != 0)
		return ("R_LEFT");
	if ((kind & R_RIGHT) != 0)
		return ("R_RIGHT");
	if ((kind & R_DOUBLE_LEFT) != 0)
		return ("R_DOUBLE_LEFT");
	if ((kind & R_DOUBLE_RIGHT) != 0)
		return ("R_DOUBLE_RIGHT");
	return ("R_UNKNOWN");
}
