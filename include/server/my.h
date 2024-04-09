/*
** EPITECH PROJECT, 2024
** bs_myFTP_select
** File description:
** my
*/

#ifndef MY_H_
    #define MY_H_

    #include "server.h"
    #include "teams.h"
    #include <uuid/uuid.h>
    #include <stddef.h>

// lib
int array_size(char **array);
void print_array(char **array);
void free_array(char **array);
char *concat_strings(char *str1, char *str2, char *delim);
char *does_path_exists(char *str);
bool does_file_exists(char *str);
bool array_is_number(char **array);
char **word_array(char const *str, char *delim);

// server
int server(const char *port_number);
server_t *init_server_struct(const char *port_number);
int initialize_server(server_t *server);
int run_server(server_t *server);
int insert_client_in_struct(server_t *server, int client_fd);
void close_client_socket(server_t *server);

void get_user_input(server_t *server, int client_fd, my_teams_t *team);
int error_not_login(server_t *server, int client_fd);

int user_login(server_t *server, int client_fd, my_teams_t *team);
int quit_cmd(server_t *server, int client_fd, my_teams_t *team);
int noop_cmd(server_t *server, int client_fd, my_teams_t *team);
int list_cmd(server_t *server, int client_fd, my_teams_t *team);
int pwd_cmd(server_t *server, int client_fd, my_teams_t *team);
int user_cmd(server_t *server, int client_fd, my_teams_t *team);
int user_spe_uuid(server_t *server, int client_fd, my_teams_t *team);
int cdup_cmd(server_t *server, int client_fd, my_teams_t *team);
int send_msg(server_t *server, int client_fd, my_teams_t *team);
int help_cmd(server_t *server, int client_fd, my_teams_t *team);
int pasv_cmd(server_t *server, int client_fd, my_teams_t *team);
int port_cmd(server_t *server, int client_fd, my_teams_t *team);
int retr_cmd(server_t *server, int client_fd, my_teams_t *team);
int stor_cmd(server_t *server, int client_fd, my_teams_t *team);


//fill struct
void fill_user_tailq(my_teams_t *teams);
void print_user_tailq(my_teams_t teams);
void fill_team_tailq(my_teams_t *teams);
void print_team_tailq(my_teams_t teams);

// database
void parse_database(my_teams_t *teams);
void save_database(const my_teams_t teams);
void parse_teams(my_teams_t *teams, char *line, bool *is_user);
void parse_users(my_teams_t *teams, char *line, bool *is_user);

#endif /* !MY_H_ */
