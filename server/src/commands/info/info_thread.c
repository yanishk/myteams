/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** info_thread
*/

#include "my.h"

static void display_info_channel(const int client_fd,
    my_teams_t *teams, thread_t *thread)
{
    if (strcmp(thread->uuid, teams->command_context->thread_uuid) == 0) {
        dprintf(client_fd, "%s\n", thread->uuid);
        dprintf(client_fd, "%ld\n", thread->timestamp);
        dprintf(client_fd, "%s\n", thread->name);
        dprintf(client_fd, "%s\n", thread->description);
    }
}

static void find_channel(const int client_fd, my_teams_t *teams, team_t *team)
{
    channel_t *channel;
    thread_t *thread;

    TAILQ_FOREACH(channel, &team->channel_head, channel_entries) {
        if (strcmp(channel->uuid, teams->command_context->channel_uuid) == 0) {
            TAILQ_FOREACH(thread, &channel->thread_head, thread_entries)
                display_info_channel(client_fd, teams, thread);
        }
    }
}

int info_thread(const int client_fd, my_teams_t *teams)
{
    team_t *team;

    TAILQ_FOREACH(team, &teams->team_head, team_entries) {
        if (strcmp(team->uuid, teams->command_context->team_uuid) == 0)
            find_channel(client_fd, teams, team);
    }
    return WIN_CMD;
}
