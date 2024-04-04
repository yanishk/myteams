##
## EPITECH PROJECT, 2023
## myteams_server
## File description:
## Makefile
##

SRC = \
    ./src/initialize_server.c \
    ./src/insert_client_in_struct.c \
    ./src/close_client_socket.c \
    ./src/run_server.c \
    ./src/server.c \
    ./src/commande/not_implemented_command.c \
    ./src/commande/cd_command.c \
    ./src/commande/cwd_command.c \
    ./src/commande/call_cmd_function.c \
    ./src/commande/user_command.c \
    ./src/commande/help/help_cmd.c \
    ./src/commande/delete_command.c \
    ./src/commande/client_command.c	\
	./main.c

LIB = \
    ./lib/is_number.c \
    ./lib/does_it_exists.c \
    ./lib/concat_strings.c \
    ./lib/array_functions.c	\
	./lib/word_array.c

OBJ = $(SRC:.c=.o)   \
	$(LIB:.c=.o)

CFLAGS = -Wall -Wextra -iquote include/server

CPPFLAGS = -iquote include/server

FLAGS_DEBUG = -g3

BIN_NAME = myteams_server

all: $(OBJ)
	@$(CC) -o $(BIN_NAME) $(OBJ) $(CFLAGS) && \
    	echo -e '\e[1m\e[32m\n[✔] COMPILED:\e[0m' || \
    	echo -e '\e[1m\e[31m\n[✘] \e[4mBUILD FAILED:\e[0m'

debug: CFLAGS += $(FLAGS_DEBUG)
debug: all

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(BIN_NAME)

re: fclean all

.PHONY: clean fclean re
