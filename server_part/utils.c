#include "server.h"

void	turn_next(void)
{
	t_list	*temp;
	int		wait_time;

	g_server->byte = 0;
	g_server->count = 0;
	g_server->connected = PAUSE;
	kill(top(), SIGUSR1);
	while (g_server->connected == PAUSE)
	{
		wait_time = CONNECTING_TIME_LIMIT;
		temp = g_server->queue;
		g_server->queue = g_server->queue->next;
		free(temp->content);
		free(temp);
		if (!g_server->queue)
			return ;
		kill(top(), SIGUSR2);
		while (g_server->connected == PAUSE && --wait_time)
			usleep(INTERVAL);
		if (g_server->connected == ON)
			return ;
		else
			ft_printf(NO_ANSWER, (int)top());
	}
}

void	add_bit(int signal)
{
	if (signal == SIGUSR2)
		g_server->byte |= (1 << (7 - g_server->count));
	++(g_server->count);
	if (g_server->count == 8)
	{
		g_server->count = 0;
		if (g_server->byte == '\0')
		{
			write(STDOUT_FILENO, "\n", sizeof(char));
			turn_next();
		}
		else
			write(STDOUT_FILENO, &g_server->byte, sizeof(char));
		g_server->byte = 0;
	}
}

t_list	*new_client(pid_t client_id)
{
	t_list	*new_client;

	new_client = ft_calloc(1, sizeof(t_list));
	if (!new_client)
		return (NULL);
	new_client->content = ft_calloc(1, sizeof(pid_t));
	if (!new_client->content)
		return (free(new_client), NULL);
	*(pid_t *)new_client->content = client_id;
	return (new_client);
}
