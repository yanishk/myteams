/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** teams
*/

#ifndef TEAMS_H_
    #define TEAMS_H_

    #include <sys/queue.h>
    #include <stdlib.h>
    #include <stddef.h>
    #include <stdbool.h>
    #include <stdio.h>
    #include <time.h>

enum TEAM_CONTEXT {
    NOTHING,
    TEAM,
    CHANNEL,
    THREAD
};

typedef struct command_context {
    enum TEAM_CONTEXT team_context;
    char *team_uuid;
    char *channel_uuid;
    char *thread_uuid;
} command_context_t;

typedef struct private_msg {
    char *uuid_sender;
    char *uuid_other;
    char *body;
    time_t timestamp;
    TAILQ_ENTRY(private_msg) private_msg_entries;
} private_msg_t;

typedef struct team_belong {
    char *uuid;
    TAILQ_ENTRY(team_belong) belong_entries;
} team_belong_t;

typedef struct user {
    char *uuid;
    char *name;
    bool is_logged;
    TAILQ_HEAD(, team_belong) team_belong_head;
    TAILQ_ENTRY(user) user_entries;
} user_t;

typedef struct thread_msg {
    char *body;
    time_t timestamp;
    TAILQ_ENTRY(thread_msg) thread_msg_entries;
} thread_msg_t;

typedef struct thread {
    char *uuid;
    char *name;
    char *description;
    time_t timestamp;
    TAILQ_HEAD(, thread_msg) thread_msg_head;
    TAILQ_ENTRY(thread) thread_entries;
} thread_t;

typedef struct channel {
    char *uuid;
    char *name;
    char *description;
    TAILQ_HEAD(, thread) thread_head;
    TAILQ_ENTRY(channel) channel_entries;
} channel_t;

typedef struct team {
    char *uuid;
    char *name;
    char *description;
    TAILQ_HEAD(, channel) channel_head;
    TAILQ_ENTRY(team) team_entries;
} team_t;

typedef struct my_teams {
    TAILQ_HEAD(, user) user_head;
    TAILQ_HEAD(, team) team_head;
    TAILQ_HEAD(, private_msg) priv_msg_head;
    user_t *new_user;
    command_context_t *command_context;
} my_teams_t;

#endif /* !TEAMS_H_ */
