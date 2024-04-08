/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** fill_struct
*/

#include "teams.h"

void fill_user_tailq(my_teams_t *teams)
{
    user_t *user;
    team_belong_t *team_belong;

    user = malloc(sizeof(user_t));
    TAILQ_INSERT_TAIL(&teams->user_head, user, user_entries);
    user->uuid = "uuid1";
    user->name = "gros caca";

    TAILQ_INIT(&user->team_belong_head);
    team_belong = malloc(sizeof(team_belong_t));
    TAILQ_INSERT_TAIL(&user->team_belong_head, team_belong, belong_entries);
    team_belong->uuid = "enorme";

    team_belong = malloc(sizeof(team_belong_t));
    TAILQ_INSERT_TAIL(&user->team_belong_head, team_belong, belong_entries);
    team_belong->uuid = "excellentissime";

    user = malloc(sizeof(user_t));
    TAILQ_INSERT_TAIL(&teams->user_head, user, user_entries);
    user->uuid = "uuid2";
    user->name = "yanis";

    TAILQ_INIT(&user->team_belong_head);
    team_belong = malloc(sizeof(team_belong_t));
    TAILQ_INSERT_TAIL(&user->team_belong_head, team_belong, belong_entries);
    team_belong->uuid = "oooooooooooooo";
}

void fill_team_tailq(my_teams_t *teams)
{
    team_t *team;
    channel_t *channel;
    thread_t *thread;
    message_thread_t *thread_message;

    team = malloc(sizeof(team_t));
    TAILQ_INSERT_TAIL(&teams->team_head, team, team_entries);
    team->uuid = "team_uuid1";
    team->name = "team_name1";
    team->description = "ceci est une description de la team1";

    TAILQ_INIT(&team->channel_head);
    channel = malloc(sizeof(channel_t));
    TAILQ_INSERT_TAIL(&team->channel_head, channel, channel_entries);
    channel->uuid = "channel_uuid1";
    channel->name = "channel_name1";
    channel->description = "ceci est une description du channel 1";

    TAILQ_INIT(&channel->thread_head);
    thread = malloc(sizeof(thread_t));
    TAILQ_INSERT_TAIL(&channel->thread_head, thread, thread_entries);
    thread->uuid = "thread_uuid1";
    thread->name = "thread_name1";
    thread->description = "ceci est une description du thread 1";

    TAILQ_INIT(&thread->message_thread_head);
    thread_message = malloc(sizeof(message_thread_t));
    TAILQ_INSERT_TAIL(&thread->message_thread_head, thread_message, msg_thread_entries);
    thread_message->body = "thread message body1";

    thread_message = malloc(sizeof(message_thread_t));
    TAILQ_INSERT_TAIL(&thread->message_thread_head, thread_message, msg_thread_entries);
    thread_message->body = "thread message body2";

    thread_message = malloc(sizeof(message_thread_t));
    TAILQ_INSERT_TAIL(&thread->message_thread_head, thread_message, msg_thread_entries);
    thread_message->body = "thread message body3";
}

void print_user_tailq(my_teams_t teams)
{
    user_t *user;
    team_belong_t *team_belong;

    TAILQ_FOREACH(user, &teams.user_head, user_entries) {
        printf("user_uuid: %s\n", user->uuid);
        printf("user_name: %s\n", user->name);
        TAILQ_FOREACH(team_belong, &user->team_belong_head,
            belong_entries) {
            printf("user team_uuid: %s\n", team_belong->uuid);
        }
    }
}

void print_team_tailq(my_teams_t teams)
{
    team_t *team;
    channel_t *channel;
    thread_t *thread;
    message_thread_t *thread_message;

    TAILQ_FOREACH(team, &teams.team_head, team_entries) {
        printf("team_uuid: %s\n", team->uuid);
        printf("team_name: %s\n", team->name);
        printf("team_description: %s\n", team->description);
        TAILQ_FOREACH(channel, &team->channel_head, channel_entries) {
            printf("channel_uuid: %s\n", channel->uuid);
            printf("channel_name: %s\n", channel->name);
            printf("channel_description: %s\n", channel->description);
            TAILQ_FOREACH(thread, &channel->thread_head, thread_entries) {
                printf("thread_uuid: %s\n", thread->uuid);
                printf("thread_name: %s\n", thread->name);
                printf("thread_description: %s\n", thread->description);
                TAILQ_FOREACH(thread_message, &thread->message_thread_head, msg_thread_entries) {
                    printf("thread_message: %s\n", thread_message->body);
                }
            }
        }
    }
}
