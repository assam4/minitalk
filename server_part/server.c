#include "server.h"

t_signal_data	*g_server;

pid_t	top(void)
{
	return (*((pid_t *)g_server->queue->content));
}

void	deallocate_server(void)
{
	free(g_server->message);
	ft_lstclear(&(g_server->queue), free);
	free(g_server);
	g_server = NULL;
}

static void	handle_signal(int signal, siginfo_t *info, void *context)
{
	(void)context;
	if (!g_server->queue
		|| (top() == info->si_pid && g_server->connected == PAUSE))
	{
		if (!g_server->queue)
			ft_lstadd_front(&(g_server->queue), new_client(info->si_pid));
		else
			ft_printf(RECONNECTED);
		ft_printf(USER_PID, (int)top());
		g_server->connected = ON;
		return ;
	}
	else if (g_server->queue && top() != info->si_pid)
	{
		ft_lstadd_back(&(g_server->queue), new_client(info->si_pid));
		kill(info->si_pid, SIGUSR2);
	}
	else if (top() == info->si_pid && g_server->connected == ON)
		g_server->signal = signal;
}

static void	servicing(void)
{
	int	wait_time;
	int	attempts;

	attempts = ATTEMPTS_LIMIT;
	while (g_server->queue)
	{
		wait_time = TIME_LIMIT;
		g_server->signal = UNDEFINED;
		kill(top(), SIGUSR1);
		while (g_server->signal == UNDEFINED && --attempts)
		{
			while (g_server->signal == UNDEFINED && --wait_time)
				usleep(INTERVAL);
			if (g_server->signal == UNDEFINED)
				kill(top(), SIGUSR2);
		}
		if (g_server->signal == UNDEFINED)
		{
			ft_printf(NO_ANSWER, (int)top());
			turn_next();
		}
		add_bit(g_server->signal);
		attempts = ATTEMPTS_LIMIT;
		usleep(INTERVAL);
	}
}

int	main(void)
{
	struct sigaction	server_action;

	g_server = ft_calloc(1, sizeof(t_signal_data));
	if (!g_server)
		return (ENOMEM);
	server_action.sa_sigaction = handle_signal;
	server_action.sa_flags = SA_SIGINFO;
	sigemptyset(&server_action.sa_mask);
	sigaction(SIGUSR1, &server_action, NULL);
	sigaction(SIGUSR2, &server_action, NULL);
	ft_printf("Server PID: %d\n", getpid());
	while (1)
	{
		pause();
		servicing();
	}
	deallocate_server();
	return (EXIT_SUCCESS);
}
