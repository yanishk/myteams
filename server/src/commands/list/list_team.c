/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** list_team
*/

#include "my.h"

int list_team(const int client_fd, my_teams_t *teams)
{
    team_t *team;

    TAILQ_FOREACH(team, &teams->team_head, team_entries)
        dprintf(client_fd, "%s%s\n%s\n%s\n", CODE_208,
        team->uuid, team->name, team->description);
    dprintf(client_fd, "%s", CODE_101);
    return WIN_CMD;
}
