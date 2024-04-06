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
char **my_str_to_word_array(char const *str, char *delim);

// server
int server(const char *port_number);
server_t *init_server_struct(const char *port_number);
int initialize_server(server_t *server);
int run_server(server_t *server);
int insert_client_in_struct(server_t *server, int client_fd);
void close_client_socket(server_t *server);

void get_user_input(server_t *server, int client_fd);
int error_not_login(server_t *server, int client_fd);

int user_login(server_t *server, int client_fd);
int quit_cmd(server_t *server, int client_fd);
int noop_cmd(server_t *server, int client_fd);
int list_cmd(server_t *server, int client_fd);
int pwd_cmd(server_t *server, int client_fd);
int user_cmd(server_t *server, int client_fd);
int cdup_cmd(server_t *server, int client_fd);
int dele_cmd(server_t *server, int client_fd);
int help_cmd(server_t *server, int client_fd);
int pasv_cmd(server_t *server, int client_fd);
int port_cmd(server_t *server, int client_fd);
int retr_cmd(server_t *server, int client_fd);
int stor_cmd(server_t *server, int client_fd);

#endif /* !MY_H_ */
