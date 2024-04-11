##
## EPITECH PROJECT, 2023
## myteams_server
## File description:
## Makefile
##

SERVER_SRC =                                        \
    ./server/src/initialize_server.c                \
    ./server/src/insert_client_in_struct.c          \
    ./server/src/close_client_socket.c              \
    ./server/src/run_server.c                       \
    ./server/src/server.c                           \
    ./server/src/commands/not_implemented_command.c \
    ./server/src/commands/cd_command.c              \
    ./server/src/commands/login_command.c           \
    ./server/src/commands/call_cmd_function.c       \
    ./server/src/commands/help/help_cmd.c           \
    ./server/src/commands/client_command.c	        \
    ./server/src/commands/user_list_command.c       \
    ./server/src/commands/private_msg.c             \
    ./server/src/database/parse_database.c          \
    ./server/src/database/save_database.c           \
    ./server/src/database/parse_teams.c             \
    ./server/src/database/parse_users.c             \
	./server/main.c

CLIENT_SRC =                                 \
    ./client/src/client.c					 \
	./client/src/redirect_print.c

LIB =                                       \
    lib/is_number.c                         \
    lib/does_it_exists.c                    \
    lib/concat_strings.c                    \
    lib/array_functions.c	                \
	lib/word_array.c

SERVER_OBJ = $(SERVER_SRC:.c=.o)                           \
	$(LIB:.c=.o)

CLIENT_OBJ = $(CLIENT_SRC:.c=.o)                           \
	$(LIB:.c=.o)

CFLAGS = -Wall -Wextra -luuid

CPPFLAGS = -iquote server/include -iquote client/include -iquote libs/myteams

FLAGS_DEBUG = -g3

SERVER_BIN_NAME = myteams_server

CLIENT_BIN_NAME = myteams_cli

all: $(SERVER_OBJ) $(CLIENT_OBJ)
	$(CC) -o $(SERVER_BIN_NAME) $(SERVER_OBJ) $(CFLAGS) && \
    $(CC) -o $(CLIENT_BIN_NAME) $(CLIENT_OBJ) $(CFLAGS) \
    libs/myteams/libmyteams.so

debug: CFLAGS += $(FLAGS_DEBUG)
debug: all

clean:
	$(RM) $(SERVER_OBJ)     \
    $(RM) $(CLIENT_OBJ)

fclean: clean
	$(RM) $(SERVER_BIN_NAME)    \
    $(RM) $(CLIENT_BIN_NAME)

re: fclean all

.PHONY: clean fclean re
