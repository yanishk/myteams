/*
** EPITECH PROJECT, 2024
** all_teams
** File description:
** call_cmd_function
*/

#include "my.h"

int (*cmd_func[NB_CMD])(server_t *server,
    const int client_fd, my_teams_t *team) = {
    &user_login,
    &user_cmd,
    &user_spe_uuid,
    &quit_cmd,
    &send_msg,
    &display_priv_msg,
    &sub_team,
    &port_cmd,
    &help_cmd,
    &noop_cmd,
    &retr_cmd,
    &stor_cmd,
    &list_cmd
};

int error_not_login(server_t *server, const int client_fd)
{
    if (server->clients[server->user_index]->is_connected == false) {
        write(client_fd, FAIL_MSG_LOGIN, strlen(FAIL_MSG_LOGIN));
        return 1;
    }
    return 0;
}

static void check_additional_space(server_t *server,
    const size_t x, const size_t y)
{
    if (server->cmd_arg.tab[x][y + 1] == '\0'
        && server->cmd_arg.tab[x][y] == ' ')
        server->cmd_arg.tab[x][y] = '\0';
}

static int realloc_arg(server_t *server)
{
    size_t size_array = 0;

    for (size_t x = 0; server->cmd_arg.tab[x] != NULL; x++) {
        size_array += 1;
        for (size_t y = 0; server->cmd_arg.tab[x][y] != '\0'; y += 1) {
            check_additional_space(server, x, y);
        }
    }
    for (size_t x = 0; server->cmd_arg.tab[x + 1] != NULL; x += 1) {
        if (strcmp(server->cmd_arg.tab[x], "\0") == 0) {
            server->cmd_arg.tab[x] = server->cmd_arg.tab[x + 1];
            size_array -= 1;
        }
    }
    server->cmd_arg.tab[size_array] = NULL;
    return size_array;
}

void get_user_input(server_t *server, const int client_fd, my_teams_t *teams)
{
    int status = 0;
    char buffer[BUFFER_MAX_SIZE] = {0};

    if (read(client_fd, buffer, BUFFER_MAX_SIZE) == 0)
        return;
    server->cmd_arg.tab = word_array(buffer, "\"\n\r");
    server->cmd_arg.len = 0;
    server->cmd_arg.len = realloc_arg(server);
    for (size_t i = 0; i < NB_CMD; i++) {
        if (server->cmd_arg.len >= 1 &&
        strcmp(server->cmd_arg.tab[0], cmd_lst[i]) == 0) {
            status = cmd_func[i](server, client_fd, teams);
        }
    }
    if (status == 0) {
        write(client_fd, FAIL_CMD_EXIST, strlen(FAIL_CMD_EXIST));
    }
    free(server->cmd_arg.tab);
    server->cmd_arg.len = 0;
}
