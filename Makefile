CLIENT_EXEC = client
SERVER_EXEC = server

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes
RM = rm -f
NM = norminette

CLIENT = SRCS/client.c \
				SRCS/client_utils.c

SERVER = SRCS/server.c \
				SRCS/server_utils.c \

LIBFT = libft/libft.a \
	
all: init $(SERVER_EXEC) $(CLIENT_EXEC)

init: 
	@cd libft && $(MAKE)
	
$(SERVER_EXEC): $(SERVER)
	$(CC) $(CFLAGS) $(SERVER) $(LIBFT) -o $(SERVER_EXEC)

$(CLIENT_EXEC): $(CLIENT)
	$(CC) $(CFLAGS) $(CLIENT) $(LIBFT) -o $(CLIENT_EXEC)

clean:
		@make clean -C ./libft

fclean: 
		@make fclean -C ./libft
		$(RM) $(SERVER_EXEC) $(CLIENT_EXEC)

re: fclean all

.PHONY: norme all fclean re clean

git: 
	git add .
	git commit -m "makefile"
	git push
	clear

norme:
	norminette