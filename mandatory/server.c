/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabr <msabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 00:37:47 by msabr             #+#    #+#             */
/*   Updated: 2025/03/21 08:19:50 by msabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minitalk.h"

void	handler(int signum, siginfo_t *info, void *old_msg)
{
	static char	byte;
	static int	bit_count;
	static int	client_pid;

	(void)old_msg;
	if (client_pid == 0)
		client_pid = info->si_pid;
	else if (client_pid != info->si_pid)
	{
		byte = 0;
		bit_count = 0;
		client_pid = info->si_pid;
	}
	if (signum == SIGUSR2)
		byte = byte | (1 << bit_count);
	bit_count++;
	if (bit_count == 8)
	{
		ft_putchar_fd(byte, 1);
		byte = 0;
		bit_count = 0;
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	(void)argv;
	if (argc != 1)
	{
		ft_putstr_fd("Erreur: Invalid arguments\n", 2);
		return (1);
	}
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler;
	sigemptyset(&sa.sa_mask);
	ft_putstr_fd("Server PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd("\nWaiting for messages...\n", 1);
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_putstr_fd("Erreur: Sigaction failed\n", 2);
		return (1);
	}
	while (1)
		pause();
	return (0);
}
