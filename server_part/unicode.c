#include "server.h"

void	print_message(void)
{
	char	*iter;

	iter = g_server->message;
	while (iter && *iter)
	{
		if (((*iter >> 7) & 1) == 0)
			iter += write(STDOUT_FILENO, iter, 1);
		else
		{
			if (((*iter >> 6) & 1) == 0)
				iter += write(STDOUT_FILENO, iter, 2);
			else
			{
				if (((*iter >> 5) & 1) == 0)
					iter += write(STDOUT_FILENO, iter, 3);
				else
					iter += write(STDOUT_FILENO, iter, 4);
			}
		}
	}
	write(STDOUT_FILENO, "\n", 1);
}
