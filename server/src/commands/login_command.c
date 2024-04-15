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
    dprintf(client_fd, "%s%s\n%s\n%s", CODE_201, new_user->uuid,
    username, CODE_101);
    server_event_user_logged_in(server->clients[server->user_index]->my_uuid);
}

static int error_login(server_t *server, const int client_fd)
{
    if (server->clients[server->user_index]->is_connected == true) {
        dprintf(client_fd, "%s%s", CODE_301, CODE_101);
        return ERR_CMD;
    }
    if (server->cmd_arg.len != 2) {
        dprintf(client_fd, "%s%s", CODE_301, CODE_101);
        return ERR_CMD;
    }
    if (strlen(server->cmd_arg.tab[1]) >= MAX_NAME_LENGTH) {
        dprintf(client_fd, "%s%s", CODE_301, CODE_101);
        return ERR_CMD;
    }
    return WIN_CMD;
}

static void create_new_user(server_t *server, const int client_fd,
    my_teams_t *teams)
{
    uuid_t tmp_uuid;

    teams->new_user = malloc(sizeof(user_t));
    TAILQ_INSERT_TAIL(&teams->user_head, teams->new_user, user_entries);
    strcpy(teams->new_user->name, server->cmd_arg.tab[1]);
    uuid_generate_random(tmp_uuid);
    teams->new_user->uuid = malloc(37);
    teams->new_user->is_logged = true;
    teams->new_user->is_team_belong_init = false;
    uuid_unparse(tmp_uuid, teams->new_user->uuid);
    add_user(server, server->cmd_arg.tab[1], teams->new_user, client_fd);
    server_event_user_created(teams->new_user->uuid, teams->new_user->name);
}

int user_login(server_t *server, const int client_fd, my_teams_t *teams)
{
    if (error_login(server, client_fd) == ERR_CMD)
        return ERR_CMD;
    for ((teams->new_user) = ((&teams->user_head)->tqh_first);
        (teams->new_user); (teams->new_user) =
        ((teams->new_user)->user_entries.tqe_next)) {
        if (strcmp(teams->new_user->name, server->cmd_arg.tab[1]) == 0) {
            add_user(server, server->cmd_arg.tab[1],
                teams->new_user, client_fd);
            teams->new_user->is_logged = true;
            return WIN_CMD;
        }
    }
    create_new_user(server, client_fd, teams);
    return WIN_CMD;
}
