/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** create_comment
*/

#include "my.h"
#include <uuid/uuid.h>

static void init_channel(server_t *server, my_teams_t *teams,
    channel_t *channel)
{
    thread_t *thread;
    thread_msg_t *comment;

    for ((thread) = ((&channel->thread_head)->tqh_first); (thread);
        (thread) = ((thread)->thread_entries.tqe_next)) {
        if (strcmp(thread->uuid, teams->command_context->thread_uuid) == 0) {
            comment = malloc(sizeof(thread_msg_t));
            TAILQ_INSERT_TAIL(&thread->thread_msg_head,
                comment, thread_msg_entries);
            comment->body = server->cmd_arg.tab[1];
        }
    }
}

static void find_channel(server_t *server,
    my_teams_t *teams, team_t *above_team)
{
    channel_t *channel;

    for ((channel) = ((&above_team->channel_head)->tqh_first);
    (channel); (channel) = ((channel)->channel_entries.tqe_next)) {
        if (strcmp(channel->uuid, teams->command_context->channel_uuid) == 0) {
            init_channel(server, teams, channel);
        }
    }
}

int create_comment(server_t *server, const int client_fd, my_teams_t *teams)
{
    team_t *above_team;

    if (server->cmd_arg.tab[1] == NULL) {
        dprintf(client_fd, "%s",
            "create.c/error_channel : not enough argument\n");
        return ERR_CMD;
    }
    for ((above_team) = ((&teams->team_head)->tqh_first); (above_team);
        (above_team) = ((above_team)->team_entries.tqe_next)) {
        if (strcmp(above_team->uuid, teams->command_context->team_uuid) == 0) {
            find_channel(server, teams, above_team);
        }
    }
    return WIN_CMD;
}
