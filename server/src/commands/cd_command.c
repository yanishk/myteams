/*
** EPITECH PROJECT, 2024
** B-NWP-400-PAR-4-1-myftp-mathis.brehm
** File description:
** cd_command
*/

#include <dirent.h>
#include "my.h"

int list_cmd(server_t *server, int client_fd, my_teams_t *)
{
    if (error_not_login(server, client_fd) != 0) {
        return ERR_CMD;
    }
    dprintf(client_fd, "%s", CODE_NOT_IMPLEMENTED);
    if (server->clients[server->user_index]->is_connected == true) {
        return WIN_CMD;
    }
    return WIN_CMD;
}

int cdup_cmd(server_t *server, int client_fd, my_teams_t *)
{
    if (error_not_login(server, client_fd) != 0) {
        return ERR_CMD;
    }
    dprintf(client_fd, "%s", CODE_NOT_IMPLEMENTED);
    if (server->clients[server->user_index]->is_connected == true) {
        return WIN_CMD;
    }
    return WIN_CMD;
}
