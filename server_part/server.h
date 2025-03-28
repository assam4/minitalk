#ifndef SERVER_H
# define SERVER_H

# include <signal.h>
# include <errno.h>
# include <limits.h>
# include "ft_printf.h"

# define END '\n'
# define ON 1
# define PAUSE 0
# define TIME_LIMIT 600000
# define CONNECTING_TIME_LIMIT 24000000
# define INTERVAL 50
# define ATTEMPTS_LIMIT 2

# define UNDEFINED -1

# define USER_PID "\033[32m[ USER - %i ]\033[0m "
# define RECONNECTED "\033[5;33m(Reconnected)\033[0m"
# define NO_ANSWER "\033[1;31m\n[user: %i] is not responding.clean\n\033[0m"

typedef struct s_signal_data
{
	int				signal;
	int				count;
	int				connected;
	unsigned char	byte;
	t_list			*queue;
}	t_signal_data;

extern t_signal_data	*g_server;

void	add_bit(int signal);
void	turn_next(void);
t_list	*new_client(pid_t client_id);
pid_t	top(void);

#endif
