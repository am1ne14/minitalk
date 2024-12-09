CC = gcc
FLAGS = -Wall -Werror -Wextra
CLIENT_SRC = client.c
SERVER_SRC = server.c
FT_PRINTF_PATH = ft_printf
FT_PRINTF_ARCHIVE =$(FT_PRINTF_PATH)/libftprintf.a
CLIENT = client
SERVER = server

all : $(CLIENT) $(SERVER)

$(FT_PRINTF_ARCHIVE) : 
	make -C $(FT_PRINTF_PATH)

$(CLIENT) : $(CLIENT_SRC) $(FT_PRINTF_ARCHIVE)
	$(CC) $(FLAGS) -o $(CLIENT) $(CLIENT_SRC) -L$(FT_PRINTF_PATH) -lftprintf

$(SERVER) : $(SERVER_SRC) $(FT_PRINTF_ARCHIVE)
	$(CC) $(FLAGS) -o $(SERVER) $(SERVER_SRC) -L$(FT_PRINTF_PATH) -lftprintf

clean :
	make -C $(FT_PRINTF_PATH) clean

fclean : clean
	make -C $(FT_PRINTF_PATH) fclean
	rm -f $(CLIENT) $(SERVER)

re : fclean all

.PHONY: all clean fclean re
