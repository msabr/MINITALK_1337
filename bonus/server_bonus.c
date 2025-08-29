/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabr <msabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 00:37:47 by msabr             #+#    #+#             */
/*   Updated: 2025/03/21 08:39:12 by msabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minitalk_bonus.h"

int	check_uni_bytes(unsigned char c)
{
	if (c < 192)
		return (1);
	else if (c < 224)
		return (2);
	else if (c < 240)
		return (3);
	else
		return (4);
}

void	process_byte(char byte, int *position, int client_pid)
{
	static char	buffer[4];
	static int	tmp;

	if (*position == 0)
		tmp = check_uni_bytes(byte);
	buffer[(*position)++] = byte;
	tmp--;
	if (tmp == 0)
	{
		buffer[*position] = '\0';
		ft_putstr_fd(buffer, 1);
		*position = 0;
	}
	if (byte == '\0')
		kill(client_pid, SIGUSR2);
}

void	handler(int signum, siginfo_t *info, void *old_msg)
{
	static int	bit_count;
	static char	byte;
	static int	position;
	static int	client_pid;

	(void)old_msg;
	if (client_pid == 0)
		client_pid = info->si_pid;
	else if (client_pid != info->si_pid)
	{
		byte = 0;
		position = 0;
		bit_count = 0;
		client_pid = info->si_pid;
	}
	if (signum == SIGUSR2)
		byte = byte | (1 << bit_count);
	bit_count++;
	if (bit_count == 8)
	{
		process_byte(byte, &position, client_pid);
		bit_count = 0;
		byte = 0;
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	(void)argv;
	if (argc != 1)
	{
		ft_putstr_fd("\033[31mErreur: Invalid arguments\033[0m\n", 2);
		return (1);
	}
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler;
	sigemptyset(&sa.sa_mask);
	ft_putstr_fd("Server PID: \033[31m", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd("\n\033[33mWaiting for messages...\033[0m\n", 1);
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_putstr_fd("\033[31mErreur: Sigaction failed\033[0m\n", 2);
		return (1);
	}
	while (1)
		pause();
	return (0);
}
