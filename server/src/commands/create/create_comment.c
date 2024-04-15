/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** create_comment
*/

#include "my.h"
#include <uuid/uuid.h>

static void fill_comment(server_t *server,
    thread_t *thread, const int client_fd)
{
    thread_msg_t *comment;

    if (TAILQ_EMPTY(&thread->thread_msg_head))
        TAILQ_INIT(&thread->thread_msg_head);
    comment = malloc(sizeof(thread_msg_t));
    TAILQ_INSERT_TAIL(&thread->thread_msg_head,
        comment, thread_msg_entries);
    comment->uuid_sender =
        strdup(server->clients[server->user_index]->new_user->uuid);
    strcpy(comment->body, server->cmd_arg.tab[1]);
    comment->timestamp = time(NULL);
    dprintf(client_fd, "%s%s\n%s\n%ld\n%s\n%s", CODE_217, thread->uuid,
    server->clients[server->user_index]->my_uuid, thread->timestamp,
    comment->body, CODE_101);
    server_event_reply_created(thread->uuid, comment->uuid_sender,
    comment->body);
}

static void init_channel(server_t *server, my_teams_t *teams,
    channel_t *channel, const int client_fd)
{
    thread_t *thread;

    for ((thread) = ((&channel->thread_head)->tqh_first); (thread);
        (thread) = ((thread)->thread_entries.tqe_next)) {
        if (strcmp(thread->uuid, teams->command_context->thread_uuid) == 0)
            fill_comment(server, thread, client_fd);
    }
}

static void find_channel(server_t *server,
    my_teams_t *teams, team_t *above_team, const int client_fd)
{
    channel_t *channel;

    for ((channel) = ((&above_team->channel_head)->tqh_first);
    (channel); (channel) = ((channel)->channel_entries.tqe_next)) {
        if (strcmp(channel->uuid, teams->command_context->channel_uuid) == 0) {
            init_channel(server, teams, channel, client_fd);
        }
    }
}

int create_comment(server_t *server, const int client_fd, my_teams_t *teams)
{
    team_t *above_team;

    if (server->cmd_arg.len != 2) {
        dprintf(client_fd, "%s",
            "create.c/error_channel : not enough argument\n");
        return ERR_CMD;
    }
    if (strlen(server->cmd_arg.tab[1]) >= MAX_BODY_LENGTH)
        return ERR_CMD;
    for ((above_team) = ((&teams->team_head)->tqh_first); (above_team);
        (above_team) = ((above_team)->team_entries.tqe_next)) {
        if (strcmp(above_team->uuid, teams->command_context->team_uuid) == 0) {
            find_channel(server, teams, above_team, client_fd);
        }
    }
    return WIN_CMD;
}
