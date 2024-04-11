/*
** EPITECH PROJECT, 2024
** B-NWP-400-PAR-4-1-myftp-mathis.brehm
** File description:
** user_command
*/

#include "my.h"

static void add_user(server_t *server, const char *username,
    user_t *new_user, const int client_fd)
{
    server->clients[server->user_index]->username =
    malloc(sizeof(char) * strlen(username));
    server->clients[server->user_index]->username = strdup(username);
    server->clients[server->user_index]->is_connected = true;
    server->clients[server->user_index]->my_uuid = new_user->uuid;
    dprintf(client_fd, "%s%s\n%s\n", CODE_201, new_user->uuid, username);
}

static int error_login(server_t *server, const int client_fd)
{
    if (server->clients[server->user_index]->is_connected == true) {
        dprintf(client_fd, "%s", ALRD_LOGIN);
        return ERR_CMD;
    }
    if (server->cmd_arg.tab[1] == NULL) {
        write(client_fd, FAIL_MSG_LOGIN, strlen(FAIL_MSG_LOGIN));
        return ERR_CMD;
    }
    return WIN_CMD;
}

int user_login(server_t *server, const int client_fd, my_teams_t *teams)
{
    uuid_t tmp_uuid;

    if (error_login(server, client_fd) == ERR_CMD)
        return ERR_CMD;
    TAILQ_FOREACH(teams->new_user, &teams->user_head, user_entries) {
        if (strcmp(teams->new_user->name, server->cmd_arg.tab[1]) == 0) {
            add_user(server, server->cmd_arg.tab[1],
                teams->new_user, client_fd);
            return WIN_CMD;
        }
    }
    teams->new_user = malloc(sizeof(user_t));
    TAILQ_INSERT_TAIL(&teams->user_head, teams->new_user, user_entries);
    teams->new_user->name = server->cmd_arg.tab[1];
    uuid_generate_random(tmp_uuid);
    teams->new_user->uuid = malloc(37);
    uuid_unparse(tmp_uuid, teams->new_user->uuid);
    add_user(server, server->cmd_arg.tab[1], teams->new_user, client_fd);
    return WIN_CMD;
}
