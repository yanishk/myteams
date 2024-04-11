/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** create
*/

#include "my.h"
#include <uuid/uuid.h>

int create(server_t *server, const int client_fd, my_teams_t *teams)
{
    team_t *team;
    uuid_t tmp_uuid;

    if (error_not_login(server, client_fd) != 0)
        return ERR_CMD;
    if (server->cmd_arg.tab[1] == NULL || server->cmd_arg.tab[2] == NULL) {
        dprintf(client_fd, "%s", "NOT DONNNNNE\n");
        return ERR_CMD;
    }
    team = malloc(sizeof(team_t));
    TAILQ_INSERT_TAIL(&teams->team_head, team, team_entries);
    team->name = server->cmd_arg.tab[1];
    team->description = server->cmd_arg.tab[2];
    uuid_generate_random(tmp_uuid);
    team->uuid = malloc(37);
    uuid_unparse(tmp_uuid, team->uuid);
    return WIN_CMD;
}
