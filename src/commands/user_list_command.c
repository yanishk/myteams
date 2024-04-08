/*
** EPITECH PROJECT, 2024
** B-NWP-400-PAR-4-1-myftp-mathis.brehm
** File description:
** user_command.c
*/

#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "my.h"
#include "teams.h"

int user_cmd(server_t *server, int client_fd, my_teams_t *teams)
{
    user_t *np_user;

    if (error_not_login(server, client_fd) != 0)
        return ERR_CMD;
    TAILQ_FOREACH(np_user, &teams->head_user, user_entries)
        dprintf(client_fd, "%s\n", np_user->name);
    dprintf(client_fd, "%s", CODE_200);
    return WIN_CMD;
}

int user_spe_uuid(server_t *server, int client_fd, my_teams_t *teams)
{
    user_t *np_user;

    if (server->cmd_arg.tab[1] == NULL) {
        dprintf(client_fd, "%s", FAIL_CMD_EXIST);
        return ERR_CMD;
    }
    if (error_not_login(server, client_fd) != 0)
        return ERR_CMD;
    TAILQ_FOREACH(np_user, &teams->head_user, user_entries) {
        if (strcmp(np_user->uuid, server->cmd_arg.tab[1]) == 0) {
            dprintf(client_fd, "%s\n", np_user->name);
            dprintf(client_fd, "%s\n", np_user->uuid);
        }
    }
    dprintf(client_fd, "%s", CODE_200);
    return WIN_CMD;
}