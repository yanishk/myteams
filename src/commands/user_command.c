/*
** EPITECH PROJECT, 2024
** B-NWP-400-PAR-4-1-myftp-mathis.brehm
** File description:
** user_command
*/

#include "my.h"

static void add_user(server_t *server, const char *username)
{
    server->clients[server->user_index]->username =
    malloc(sizeof(char) * strlen(username));
    server->clients[server->user_index]->username = strdup(username);
    server->clients[server->user_index]->is_connected = true;
}

int user_login(server_t *server, int client_fd)
{
    if (server->cmd_arg.len == 1) {
        write(client_fd, FAIL_MSG_LOGIN, strlen(FAIL_MSG_LOGIN));
        return ERR_CMD;
    }
    write(client_fd, SUC_MSG_LOGIN, strlen(SUC_MSG_LOGIN));
    add_user(server, server->cmd_arg.tab[1]);
    return WIN_CMD;
}
