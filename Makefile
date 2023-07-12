CSRCS = src/client.c \
		src/minitalk_utils.c

COBJS = $(CSRCS:.c=.o)

SSRCS = src/server.c \
		src/minitalk_utils.c

SOBJS = $(SSRCS:.c=.o)

CSRCS_BONUS = src/client_bonus.c \
		src/minitalk_utils.c

COBJS_BONUS = $(CSRCS_BONUS:.c=.o)

SSRCS_BONUS = src/server_bonus.c \
		src/minitalk_utils.c

SOBJS_BONUS = $(SSRCS_BONUS:.c=.o)

CLIENT = client

SERVER = server

CLIENT_BONUS = client_bonus

SERVER_BONUS = server_bonus

CC = gcc

FLAGS = -Wall -Wextra -Werror

RM = rm -f

all:		$(CLIENT) $(SERVER)

$(CLIENT):			$(COBJS)
				$(CC) -o $(CLIENT) $(FLAGS) $(COBJS)

$(SERVER):			$(SOBJS)
				$(CC) -o $(SERVER) $(FLAGS) $(SOBJS)

bonus:		$(CLIENT_BONUS) $(SERVER_BONUS)

$(CLIENT_BONUS): 	$(COBJS_BONUS)
				$(CC) -o $(CLIENT_BONUS) $(FLAGS) $(COBJS_BONUS)

$(SERVER_BONUS): 	$(SOBJS_BONUS)
				$(CC) -o $(SERVER_BONUS) $(FLAGS) $(SOBJS_BONUS)

clean:
				$(RM) $(COBJS) $(SOBJS) $(COBJS_BONUS) $(SOBJS_BONUS)

fclean: 	clean
				$(RM) $(CLIENT) $(SERVER) $(CLIENT_BONUS) $(SERVER_BONUS)

re:			fclean all

.PHONY: all clean fclean re 