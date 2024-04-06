/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** teams
*/

#ifndef TEAMS_H_
#define TEAMS_H_

    #include <sys/queue.h>

typedef struct team_belong {
    char *uuid;
    TAILQ_ENTRY(teams_belong) belong_entries;
} team_belong_t;

typedef struct user {
    char *uuid;
    char *name;
    TAILQ_HEAD(user_team_head, teams_belong) team_belong_uuid_head;
    TAILQ_ENTRY(user_id) user_entries;
} user_t;

typedef struct team {
    char *uuid;
    char *name;
    char *description;
    TAILQ_HEAD(team_channel_head, channel) channel_head;
    TAILQ_ENTRY(teams) team_entries;
} team_t;

typedef struct channel {
    char *uuid;
    char *description;
    char *name;
    TAILQ_HEAD(thread_channel_head, thread) thread_head;
    TAILQ_ENTRY(channel) channel_entries;
} channel_t;

typedef struct thread {
    char *uuid;
    char *name;
    TAILQ_HEAD(msg_thread_head, message_thread) thread_msg_body_head;
    TAILQ_ENTRY(thread) thread_entries;
} thread_t;

typedef struct message_thread {
    char *body;
    TAILQ_ENTRY(message_thread) msg_thread_entries;
} message_thread_t;

#endif /* !TEAMS_H_ */
