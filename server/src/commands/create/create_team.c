/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** create_team
*/

#include "my.h"
#include <uuid/uuid.h>

static int error_create_team(server_t *server,
    const int client_fd, my_teams_t *teams)
{
    team_t *team_exist;

    if (server->cmd_arg.tab[1] == NULL || server->cmd_arg.tab[2] == NULL) {
        dprintf(client_fd, "%s", "create.c/create : not enough argument\n");
        return ERR_CMD;
    }
    TAILQ_FOREACH(team_exist, &teams->team_head, team_entries) {
        if (strcmp(team_exist->name, server->cmd_arg.tab[1]) == 0) {
            dprintf(client_fd, "%s",
                "create.c/error_create_team : name already used\n");
            return ERR_CMD;
        }
    }
    return WIN_CMD;
}

int create_team(server_t *server, const int client_fd, my_teams_t *teams)
{
    team_t *team;
    uuid_t tmp_uuid;
    time_t msg_time;

    if (error_create_team(server, client_fd, teams) == ERR_CMD)
        return ERR_CMD;
    team = malloc(sizeof(team_t));
    TAILQ_INSERT_TAIL(&teams->team_head, team, team_entries);
    team->name = server->cmd_arg.tab[1];
    team->description = server->cmd_arg.tab[2];
    uuid_generate_random(tmp_uuid);
    team->uuid = malloc(37);
    uuid_unparse(tmp_uuid, team->uuid);
    msg_time = time(NULL);
    dprintf(client_fd, "%s", "create.c/create : succesfully created a team\n");
    return WIN_CMD;
}
