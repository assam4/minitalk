#include "server.h"

static void	reset_params(void)
{
	free(g_server->message);
	g_server->message = NULL;
	g_server->capacity = 0;
	g_server->count = 0;
	g_server->byte = 0;
}

void	turn_next(void)
{
	t_list	*temp;
	int		wait_time;

	reset_params();
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

static void	add_to_message(void)
{
	char	*temp;

	temp = NULL;
	if (!g_server->capacity
		|| (int)ft_strlen(g_server->message) == g_server->capacity - 1)
	{
		if (g_server->capacity)
		{
			temp = g_server->message;
			g_server->capacity = g_server->capacity * 2 - 1;
		}
		else
			g_server->capacity = ALLOCATION_SIZE;
		g_server->message = ft_calloc(g_server->capacity, sizeof(char));
		if (!g_server->message)
		{
			deallocate_server();
			free(temp);
			exit(EXIT_FAILURE);
		}
	}
	if (temp)
		ft_strlcpy(g_server->message, temp, ft_strlen(temp) + 1);
	free(temp);
	g_server->message[ft_strlen(g_server->message)] = g_server->byte;
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
			write(STDOUT_FILENO,
				g_server->message,
				ft_strlen(g_server->message));
			write(STDOUT_FILENO, "\n", 1);
			turn_next();
		}
		else
			add_to_message();
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
