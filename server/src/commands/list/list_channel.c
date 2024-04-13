/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** list_channel
*/

#include "my.h"

int list_channel(const int client_fd, my_teams_t *teams)
{
    team_t *team;
    channel_t *channel;

    TAILQ_FOREACH(team, &teams->team_head, team_entries) {
        if (strcmp(team->uuid, teams->command_context->team_uuid) == 0) {
            TAILQ_FOREACH(channel, &team->channel_head, channel_entries) {
                dprintf(client_fd, "%s\n", channel->name);
            }
        }
    }
    return WIN_CMD;
}
