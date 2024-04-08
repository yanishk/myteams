/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** fill_struct
*/

#include "../../include/server/teams.h"

void fill_user_tailq(my_teams_t *teams)
{
    user_t *n1_user;
    team_belong_t *n1_team_belong;
    private_msg_t *n1_private_msg;

    n1_user = malloc(sizeof(user_t));
    TAILQ_INSERT_TAIL(&teams->head_user, n1_user, user_entries);
    n1_user->uuid = "uuid1";
    n1_user->name = "eva";

    TAILQ_INIT(&n1_user->team_belong_uuid_head);
    n1_team_belong = malloc(sizeof(team_belong_t));
    TAILQ_INSERT_TAIL(&n1_user->team_belong_uuid_head, n1_team_belong, belong_entries);
    n1_team_belong->uuid = "enorme";

    TAILQ_INIT(&n1_user->private_msg_head);
    n1_private_msg = malloc(sizeof(private_msg_t));
    TAILQ_INSERT_TAIL(&n1_user->private_msg_head, n1_private_msg, private_msg_entries);
    n1_private_msg->body = "mathis c un gros nul";

    n1_team_belong = malloc(sizeof(team_belong_t));
    TAILQ_INSERT_TAIL(&n1_user->team_belong_uuid_head, n1_team_belong, belong_entries);
    n1_team_belong->uuid = "excellentissime";

    n1_user = malloc(sizeof(user_t));
    TAILQ_INSERT_TAIL(&teams->head_user, n1_user, user_entries);
    n1_user->uuid = "uuid2";
    n1_user->name = "yanis";

    TAILQ_INIT(&n1_user->team_belong_uuid_head);
    n1_team_belong = malloc(sizeof(team_belong_t));
    TAILQ_INSERT_TAIL(&n1_user->team_belong_uuid_head, n1_team_belong, belong_entries);
    n1_team_belong->uuid = "oooooooooooooo";
}

void print_tailq(my_teams_t teams)
{
    user_t *np_user;
    team_belong_t *np_team_belong;

    TAILQ_FOREACH(np_user, &teams.head_user, user_entries) {
        printf("user_uuid: %s\n", np_user->uuid);
        printf("user_name: %s\n", np_user->name);
        TAILQ_FOREACH(np_team_belong, &np_user->team_belong_uuid_head,
            belong_entries) {
            printf("user team_uuid: %s\n", np_team_belong->uuid);
        }
    }
}