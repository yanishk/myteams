##
## EPITECH PROJECT, 2023
## myteams_server
## File description:
## Makefile
##

SRC =                                        \
    ./src/client.c

LIB =                                        \
    ../lib/is_number.c                       \
    ../lib/does_it_exists.c                  \
    ../lib/concat_strings.c                  \
    ../lib/array_functions.c	             \
	../lib/word_array.c

OBJ = $(SRC:.c=.o)                           \
	$(LIB:.c=.o)

CFLAGS = -Wall -Wextra -luuid

CPPFLAGS = -iquote ../include/client

FLAGS_DEBUG = -g3

BIN_NAME = myteams_cli

all: $(OBJ)
	@$(CC) -o $(BIN_NAME) $(OBJ) $(CFLAGS) ./libmyteams.so && \
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
