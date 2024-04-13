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
        dprintf(client_fd, "%s\n", team->name);
    return WIN_CMD;
}
