/*
** EPITECH PROJECT, 2024
** B-NWP-400-PAR-4-1-myftp-mathis.brehm
** File description:
** client_command
*/

#include "my.h"

int quit_cmd(server_t *server, const int client_fd, my_teams_t *teams)
{
    char *uuid;
    char *username;

    if (error_not_login(server, client_fd) != 0)
        return ERR_CMD;
    uuid = strdup(server->clients[server->user_index]->my_uuid);
    username = strdup(server->clients[server->user_index]->username);
    dprintf(client_fd, "%s%s\n%s\n%s", CODE_202, uuid, username, CODE_101);
    teams->new_user->is_logged = false;
    server->clients[server->user_index]->username = malloc(sizeof(char) * 1);
    server->clients[server->user_index]->is_connected = false;
    server->fd_array[server->user_index] = 0;
    close(client_fd);
    return WIN_CMD;
}
