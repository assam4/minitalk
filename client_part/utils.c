#include "client.h"

void	failure_exit(int err_bit, char *message)
{
	ft_printf("%s [pid: %d]\n", message, getpid());
	exit(err_bit);
}

static void	waiting(int wait_time)
{
	while (g_client.m_signal == UNDEFINED && wait_time--)
		usleep(INTERVAL);
}

static void	send_letter(pid_t server_id, unsigned char letter, int attempts)
{
	int	bit;

	bit = BYTE_SIZE - 1;
	while (bit >= 0)
	{
		g_client.m_signal = UNDEFINED;
		if ((letter >> bit) & 1)
			kill(server_id, SIGUSR2);
		else
			kill(server_id, SIGUSR1);
		usleep(INTERVAL);
		if (g_client.m_signal != SIG1 && --attempts)
		{
			waiting(TIME_LIMIT);
			if (g_client.m_signal == SIG2)
				continue ;
		}
		if (g_client.m_signal != SIG1)
			failure_exit(EXDEV, TIMEOUT);
		attempts = ATTEMPTS_LIMIT;
		--bit;
		usleep(50);
	}
}

void	send_message(pid_t server_id, char *message)
{
	int	i;

	i = -1;
	while (message[++i])
		send_letter(server_id, message[i], ATTEMPTS_LIMIT);
	send_letter(server_id, END, ATTEMPTS_LIMIT);
}
