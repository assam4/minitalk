SERVER = server
CLIENT = client

CC = cc
CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=address

PRINTF_DIR = ./ft_printf/
SERVER_DIR = ./server_part/
CLIENT_DIR = ./client_part/
INCLUDES = -I$(PRINTF_DIR)libft/ -I$(PRINTF_DIR) -I$(SERVER_DIR) 

SERVER_SRC = $(SERVER_DIR)server.c $(SERVER_DIR)utils.c $(SERVER_DIR)unicode.c
SERVER_OBJ = $(SERVER_SRC:.c=.o)

CLIENT_SRC = $(CLIENT_DIR)client.c $(CLIENT_DIR)utils.c
CLIENT_OBJ = $(CLIENT_SRC:.c=.o)

all: $(SERVER) $(CLIENT)

$(SERVER): $(PRINTF_DIR)libftprintf.a $(SERVER_OBJ)
	$(CC) $(CFLAGS) $(SERVER_OBJ) -L$(PRINTF_DIR) -lftprintf -o $(SERVER)

$(CLIENT): $(PRINTF_DIR)libftprintf.a $(CLIENT_OBJ)
	$(CC) $(CFLAGS) $(CLIENT_OBJ) -L$(PRINTF_DIR) -lftprintf -o $(CLIENT)

$(PRINTF_DIR)libftprintf.a:
	$(MAKE) -C $(PRINTF_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(SERVER_OBJ)
	rm -f $(CLIENT_OBJ)
	$(MAKE) -C $(PRINTF_DIR) clean

fclean: clean
	rm -f $(SERVER)
	rm -f $(CLIENT)
	$(MAKE) -C $(PRINTF_DIR) fclean

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus
