/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** list_comment
*/

#include "my.h"

static void display_threads(const int client_fd,
    my_teams_t *teams, thread_t *thread)
{
    thread_msg_t *thread_msg;

    TAILQ_FOREACH(thread_msg, &thread->thread_msg_head, thread_msg_entries) {
        dprintf(client_fd, "%s\n", thread_msg->body);
    }
}

static void find_thread(const int client_fd,
    my_teams_t *teams, channel_t *channel)
{
    thread_t *thread;

    TAILQ_FOREACH(thread, &channel->thread_head, thread_entries) {
        if (strcmp(thread->uuid, teams->command_context->thread_uuid) == 0) {
            display_threads(client_fd, teams, thread);
        }
    }
}

static void find_channel(const int client_fd, my_teams_t *teams, team_t *team)
{
    channel_t *channel;

    TAILQ_FOREACH(channel, &team->channel_head, channel_entries) {
        if (strcmp(channel->uuid, teams->command_context->channel_uuid) == 0) {
            find_thread(client_fd, teams, channel);
        }
    }
}

int list_comment(const int client_fd, my_teams_t *teams)
{
    team_t *team;

    TAILQ_FOREACH(team, &teams->team_head, team_entries) {
        if (strcmp(team->uuid, teams->command_context->team_uuid) == 0) {
            find_channel(client_fd, teams, team);
        }
    }
    return WIN_CMD;
}
