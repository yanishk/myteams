##
## EPITECH PROJECT, 2024
## B-OOP-400-PAR-4-1-tekspice-wilson.bordichon
## File description:
## Makefile
##

SRC	=	main.c 												\
		src/server.c 										\
		src/initialize_server.c 							\
		src/run_server.c 									\
		src/insert_client_in_struct.c 						\
		src/close_client_socket.c							\
		lib/array_functions.c 								\
		lib/concat_strings.c 								\
		lib/does_it_exists.c 								\
		lib/is_number.c 									\

CC = gcc

OBJ	=	$(SRC:.c=.o)

RM = rm -f

CPPFLAGS += -iquote include/server

CFLAGS += -Wall -Wextra -g

NAME	=	myteams_server

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re:	 fclean all

.PHONY = all clean fclean re
