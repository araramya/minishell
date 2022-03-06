/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabajyan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 16:26:44 by araramya          #+#    #+#             */
/*   Updated: 2022/03/06 18:35:04 by aabajyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	singal_terminate_output(void)
{
	struct termios	settings;

	if (tcgetattr(0, &settings))
		perror("tcsetattr");
	settings.c_lflag &= ~ECHOCTL;
	if (tcsetattr(0, 0, &settings))
		perror("tcsetattr");
}

void	signal_do_nothing(int sig)
{
	(void)sig;
	singal_terminate_output();
	rl_on_new_line();
	rl_redisplay();
}

void	signal_reprompt(int sig)
{
	(void)sig;
	singal_terminate_output();
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_interupt(int sig)
{
	exit(sig);
}
