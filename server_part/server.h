#ifndef SERVER_H
# define SERVER_H

# include <signal.h>
# include <errno.h>
# include <limits.h>
# include "ft_printf.h"

# define END '\n'
# define ON 1
# define PAUSE 0
# define TIME_LIMIT 2000
# define CONNECTING_TIME_LIMIT 3000
# define INTERVAL 50
# define ATTEMPTS_LIMIT 3
# define BUF_SIZE 1000

# define UNDEFINED -1

# define USER_PID "\033[32m[ USER - %i ]\033[0m "
# define RECONNECTED "\033[5;33m(Reconnected)\033[0m"
# define NO_ANSWER "\033[1;31m\n[user: %i] is not responding.clean\n\033[0m"

typedef struct s_signal_data
{
	volatile sig_atomic_t		signal;
	volatile sig_atomic_t		connected;
	int							count;
	int							i;
	unsigned char				byte;
	t_list						*queue;
	char						buffer[BUF_SIZE];

}	t_signal_data;

extern t_signal_data	*g_server;

void	deallocate_server(void);
void	print_message(void);
void	add_bit(int signal);
void	turn_next(void);
t_list	*new_client(pid_t client_id);

#endif
