/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabr <msabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:52:40 by msabr             #+#    #+#             */
/*   Updated: 2025/03/18 08:49:33 by msabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minitalk_bonus.h"

static void	send_char(int pid, char c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (((c >> i) & 1) == 0)
			kill(pid, SIGUSR1);
		else if (((c >> i) & 1) == 1)
			kill(pid, SIGUSR2);
		usleep(200);
		usleep(200);
		i++;
	}
	usleep(20);
}

static void	send_str(int pid, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		send_char(pid, str[i]);
		i++;
	}
	send_char(pid, '\0');
	usleep(20);
}

static int	is_valid_pid(char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	while (str[i] == ' ' || ('\t' <= str[i] && str[i] <= '\r'))
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	while (*str == '0')
		str++;
	if (ft_strlen(str) > 10 || ft_atoi(str) > 2147483647)
		return (0);
	return (1);
}

static void	successfully_send(int signal)
{
	if (signal == SIGUSR2)
		ft_putstr_fd("\033[32m message sent successfully\n\033[0m", 1);
}

int	main(int argc, char **argv)
{
	int	pid;

	if (argc != 3 || !argv[1] || !argv[2])
	{
		ft_putstr_fd("\033[31mError: Invalid arguments\033[0m\n", 2);
		return (1);
	}
	pid = ft_atoi(argv[1]);
	if (!is_valid_pid(argv[1]) || kill(pid, 0) == -1
		|| pid == getpid() || pid <= 0)
		return (ft_putstr_fd("\033[31mError: Invalid PID\033[0m\n", 2), 1);
	signal(SIGUSR2, successfully_send);
	send_str(pid, argv[2]);
	return (0);
}
