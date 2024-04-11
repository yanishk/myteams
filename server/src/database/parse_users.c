/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** parse_users
*/

#include "parsing.h"
#include "teams.h"
#include "my.h"

static void fill_team_belong(user_t *user, char **array)
{
    team_belong_t *team_belong;

    TAILQ_INIT(&user->team_belong_head);
    for (int i = 1; array[i] != NULL; i += 1) {
        team_belong = malloc(sizeof(team_belong_t));
        TAILQ_INSERT_TAIL(&user->team_belong_head, team_belong,
            belong_entries);
        team_belong->uuid = array[i];
    }
}

static void fill_private_message(user_t *user, char **array)
{
    private_msg_t *private_msg;

    TAILQ_INIT(&user->private_msg_head);
    for (int i = 1; array[i] != NULL; i += 2) {
        if (strcmp(array[i], "user_id") == 0) {
            private_msg = malloc(sizeof(private_msg_t));
            TAILQ_INSERT_TAIL(&user->private_msg_head, private_msg,
                private_msg_entries);
            private_msg->uuid_other = array[i + 1];
        }
        if (strcmp(array[i], "body") == 0) {
            private_msg->body = array[i + 1];
        }
    }
}

static void fill_user(char *line, user_t *user, char **array)
{
    if (strncmp(line, "\tuuid=", strlen("\tuuid=")) == 0)
        user->uuid = strdup(array[1]);
    if (strncmp(line, "\tname=", strlen("\tname=")) == 0)
        user->name = strdup(array[1]);
    if (strncmp(line, "\tteams_uuid=", strlen("\tteams_uuid=")) == 0)
        fill_team_belong(user, array);
    if (strncmp(line, "\tprivate_message=", strlen("\tprivate_message=")) == 0)
        fill_private_message(user, array);
}

void parse_users(my_teams_t *teams, char *line, bool *is_user)
{
    static user_t *user;
    char **array = word_array(line, "\t\n=,:");

    if (strcmp(line, "user:\n") == 0) {
        user = malloc(sizeof(user_t));
        TAILQ_INSERT_TAIL(&teams->user_head, user, user_entries);
        *is_user = true;
    }
    if (array_size(array) < 2 || !*is_user) {
        free(array);
        return;
    }
    fill_user(line, user, array);
    free(array);
}
