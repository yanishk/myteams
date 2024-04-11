/*
** EPITECH PROJECT, 2024
** B-NWP-400-PAR-4-1-myftp-mathis.brehm
** File description:
** client_command
*/

#include "my.h"

int quit_cmd(server_t *server, const int client_fd, my_teams_t *)
{
    char *uuid = strdup(server->clients[server->user_index]->my_uuid);
    char *username = strdup(server->clients[server->user_index]->username);

    if (error_not_login(server, client_fd) != 0)
        return ERR_CMD;
    server->clients[server->user_index]->is_connected = false;
    dprintf(client_fd, "%s%s\n%s\n", CODE_202, uuid, username);
    return WIN_CMD;
}

int noop_cmd(server_t *server, const int client_fd, my_teams_t *)
{
    if (error_not_login(server, client_fd) != 0) {
        return ERR_CMD;
    }
    write(client_fd, CODE_200, strlen(CODE_200));
    return WIN_CMD;
}
