/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** parse_database
*/

#include "teams.h"
#include "my.h"

static void fill_user_team_belong(user_t *new_user, char **array)
{
    team_belong_t *new_team_belong;

    TAILQ_INIT(&new_user->team_belong_head);
    for (int i = 1; array[i] != NULL; i += 1) {
        new_team_belong = malloc(sizeof(team_belong_t));
        TAILQ_INSERT_TAIL(&new_user->team_belong_head, new_team_belong,
            belong_entries);
        new_team_belong->uuid = array[i];
    }
}

static void parse_users(my_teams_t *teams, char *line)
{
    static user_t *new_user;
    char **array = word_array(line, "\t\n=,");

    if (strcmp(line, "user:\n") == 0) {
        new_user = malloc(sizeof(user_t));
        TAILQ_INSERT_TAIL(&teams->user_head, new_user, user_entries);
    }
    if (array_size(array) < 2) {
        free(array);
        return;
    }
    if (strncmp(line, "\tuuid=", strlen("\tuuid=")) == 0)
        new_user->uuid = strdup(array[1]);
    if (strncmp(line, "\tname=", strlen("\tname=")) == 0)
        new_user->name = strdup(array[1]);
    if (strncmp(line, "\tteams_uuid=", strlen("\tteams_uuid=")) == 0)
        fill_user_team_belong(new_user, array);
    free(array);
}

void parse_database(my_teams_t *teams)
{
    FILE *stream = fopen("database", "r");
    char *line = NULL;
    size_t len = 0;

    if (!stream)
        return;
    while (getline(&line, &len, stream) != -1)
        parse_users(teams, line);
    fclose(stream);
    if (line != NULL)
        free(line);
}
