CLIENT_EXEC = client
SERVER_EXEC = server

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes
RM = rm -f
NM = norminette

CLIENT = client.c

SERVER = server.c \
				server_utils.c \

LIBFT = libft/libft.a \
	
all: init $(SERVER_EXEC) $(CLIENT_EXEC)

init: 
	@cd libft && $(MAKE)
	
$(SERVER_EXEC): $(SERVER) $(HEADER)
	$(CC) $(CFLAGS) $(SERVER) $(LIBFT) -o $(SERVER_EXEC)

$(CLIENT_EXEC): $(SRCS_CLIENT) $(HEADER)
	$(CC) $(CFLAGS) $(CLIENT) $(LIBFT) -o $(CLIENT_EXEC)

clean:
		make clean -C ./libft

fclean: 
		make fclean -C ./libft
		$(RM) $(SERVER_EXEC) $(CLIENT_EXEC)
git: 
	git add .
	git commit -m "makefile"
	git push
	clear

norme:
	norminette