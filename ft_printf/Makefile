NAME = libftprintf.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I./libft

AR = ar rcs

SRCS := ft_printf_utils.c ft_printf.c
OBJS := $(SRCS:.c=.o)

LIBFT = ./libft/libft.a

# libft.a object files
LIBFT_OBJS = ft_isalnum.o ft_isprint.o ft_memcmp.o ft_putchar_fd.o ft_split.o ft_strlcat.o ft_strncmp.o \
	     ft_substr.o ft_atoi.o ft_isalpha.o ft_itoa.o ft_memcpy.o ft_putendl_fd.o ft_strchr.o \
	     ft_strlcpy.o ft_strnstr.o ft_tolower.o ft_bzero.o ft_isascii.o ft_memmove.o ft_putnbr_fd.o \
	     ft_strdup.o ft_strlen.o ft_strrchr.o ft_toupper.o ft_calloc.o ft_isdigit.o ft_memchr.o \
	     ft_memset.o ft_putstr_fd.o ft_strjoin.o ft_strmapi.o ft_strtrim.o ft_lstadd_back_bonus.o \
	     ft_lstadd_front_bonus.o ft_lstclear_bonus.o ft_lstdelone_bonus.o ft_lstiter_bonus.o \
	     ft_lstlast_bonus.o ft_lstmap_bonus.o ft_lstnew_bonus.o ft_lstsize_bonus.o ft_striteri.o
all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C libft
	$(MAKE) -C libft bonus

# make rules
$(NAME): $(OBJS) $(LIBFT)
	# unzip libft in project dir
	ar x $(LIBFT)
	# cat libft object and printf objects in archive
	$(AR) $(NAME) $(OBJS) $(LIBFT_OBJS)
	# delete libft objects
	rm -f $(LIBFT_OBJS)

%.o: %.c ft_printf.h
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJS)
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re
