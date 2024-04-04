/*
** EPITECH PROJECT, 2024
** bs_myFTP_select
** File description:
** my
*/

#ifndef MY_H_
    #define MY_H_

    #include "server.h"

// lib
int array_size(char **array);
void print_array(char **array);
void free_array(char **array);
char *concat_strings(char *str1, char *str2, char *delim);
char *does_path_exists(char *str);
bool does_file_exists(char *str);
bool array_is_number(char **array);

// server
int server(const char *port_number);
server_t *init_server_struct(const char *port_number);
int initialize_server(server_t *server);
int run_server(server_t *server);
int insert_client_in_struct(server_t *server, int client_fd);
void close_client_socket(server_t *server, clients_t *client);

#endif /* !MY_H_ */
