#include "client.h"

t_client	g_client;

static int	pid_validation(char *str)
{
	if (!str)
		return (EXIT_FAILURE);
	while (*str)
	{
		if (!ft_isdigit(*str))
		{
			exit(EXIT_FAILURE);
			return (EXIT_FAILURE);
		}
		++str;
	}
	return (EXIT_SUCCESS);
}

static void	handle(int signal, siginfo_t *info, void *context)
{
	(void)context;
	if (g_client.connected != ON)
	{
		if (signal == SIGUSR1)
			g_client.connected = ON;
		else if (signal == SIGUSR2)
		{
			if (g_client.connected == WAIT)
			{
				kill(info->si_pid, SIGUSR2);
				g_client.connected = CONNECTING;
			}
			else
				g_client.connected = WAIT;
		}
	}
	else
	{
		if (signal == SIGUSR2)
			g_client.m_signal = SIG2;
		else if (signal == SIGUSR1)
			g_client.m_signal = SIG1;
	}
}

static void	waiting_server(void)
{
	int	wait_time;

	wait_time = CONNECTING_TIME_LIMIT;
	while (wait_time-- && g_client.connected == WAIT)
		usleep(INTERVAL);
	if (g_client.connected == WAIT)
		failure_exit(EXDEV, CONNECTING_TIMEOUT);
	wait_time = TIME_LIMIT;
	while (wait_time-- && g_client.connected == CONNECTING)
		usleep(INTERVAL);
	if (g_client.connected == CONNECTING)
		failure_exit(EXDEV, TIMEOUT);
}

static void	communicate(pid_t server_id, char *message)
{
	int	attempts;

	attempts = ATTEMPTS_LIMIT;
	g_client.connected = UNDEFINED;
	kill(server_id, SIGUSR1);
	while (g_client.connected == UNDEFINED && --attempts)
	{
		usleep(TIME_LIMIT);
		if (g_client.connected == UNDEFINED)
			kill(server_id, SIGUSR1);
	}
	if (g_client.connected == UNDEFINED)
		failure_exit(EXDEV, TIMEOUT);
	else if (g_client.connected == WAIT)
		waiting_server();
	send_message(server_id, message);
}

int	main(int argc, char **argv)
{
	pid_t				server_id;
	struct sigaction	sa;

	if (argc != EXPECTED_ARGC || pid_validation(argv[1]))
		failure_exit(EINVAL, INVALID_ARG);
	server_id = ft_atoi(argv[1]);
	if (!server_id)
		failure_exit(ECONNREFUSED, INVALID_ARG);
	sa.sa_sigaction = handle;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	communicate(server_id, argv[2]);
	return (EXIT_SUCCESS);
}
