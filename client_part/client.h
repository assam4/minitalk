#ifndef CLIENT_H
# define CLIENT_H

# include "ft_printf.h"
# include <signal.h>
# include <stdio.h>
# include <errno.h>

# define UNDEFINED -1
# define ON 1
# define WAIT 2
# define CONNECTING 3
# define SIG1 42
# define SIG2 4242

# define BYTE_SIZE 8
# define END '\0'

# define EXPECTED_ARGC 3
# define TIME_LIMIT 600000
# define INTERVAL 100
# define CONNECTING_TIME_LIMIT 1200000
# define ATTEMPTS_LIMIT 10

# define WAITING "\nServer is overloaded. Waiting ... "
# define INVALID_ARG "\nInvalid args!.Try with correct arguments."
# define TIMEOUT "\nTimeout! Server did not respond within 1 minute."
# define CONNECTING_TIMEOUT "\nTimeout! Server did not respond within 2 minute."

typedef struct s_client
{
	int	connected;
	int	m_signal;
}	t_client;

extern t_client	g_client;

void	failure_exit(int err, char *message);
void	send_message(pid_t server_id, char *message);

#endif
