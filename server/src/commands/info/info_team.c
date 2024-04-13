/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** info_team
*/

#include "my.h"

int info_team(const int client_fd, my_teams_t *teams)
{
    team_t *team;

    TAILQ_FOREACH(team, &teams->team_head, team_entries) {
        if (strcmp(team->uuid, teams->command_context->team_uuid) == 0) {
            dprintf(client_fd, "%s\n", team->uuid);
            dprintf(client_fd, "%s\n", team->name);
            dprintf(client_fd, "%s\n", team->description);
        }
    }
    return WIN_CMD;
}
