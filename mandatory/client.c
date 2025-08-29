/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabr <msabr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 14:52:40 by msabr             #+#    #+#             */
/*   Updated: 2025/03/18 02:01:50 by msabr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minitalk.h"

static void	send_bit(int pid, int bit)
{
	if (bit == 0)
		kill(pid, SIGUSR1);
	else if (bit == 1)
		kill(pid, SIGUSR2);
	usleep(200);
	usleep(200);
}

static void	send_char(int pid, char c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		send_bit(pid, (c >> i) & 1);
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

int	main(int argc, char **argv)
{
	int	pid;

	if (argc != 3 || !argv[1] || !argv[2])
	{
		ft_putstr_fd("Error: Invalid arguments\n", 2);
		return (1);
	}
	pid = ft_atoi(argv[1]);
	if (!is_valid_pid(argv[1]) || kill(pid, 0) == -1
		|| pid == getpid() || pid <= 0)
		return (ft_putstr_fd("Error: Invalid PID\n", 2), 1);
	send_str(pid, argv[2]);
	return (0);
}
