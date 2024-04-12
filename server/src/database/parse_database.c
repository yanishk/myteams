/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** parse_database
*/

#include "parsing.h"
#include "teams.h"
#include "my.h"

void parse_mp(my_teams_t *teams, char *line, int *is_user)
{
    static private_msg_t *dm;
    char **array = word_array(line, "\t\n=,:");

    if (strcmp(line, "private_message:\n") == 0) {
        dm = malloc(sizeof(private_msg_t));
        TAILQ_INSERT_TAIL(&teams->priv_msg_head, dm, private_msg_entries);
        *is_user = 2;
    }
    if (*is_user != 2 || array_size(array) < 2) {
        free(array);
        return;
    }
    if (strncmp(line, "uuid_sender=", strlen("uuid_sender=")) == 0)
        dm->uuid_sender = strdup(array[1]);
    if (strncmp(line, "uuid_other=", strlen("uuid_other=")) == 0)
        dm->uuid_other = strdup(array[1]);
    if (strncmp(line, "body=", strlen("body=")) == 0)
        dm->body = strdup(array[1]);
}

void parse_database(my_teams_t *teams)
{
    FILE *stream = fopen(".database", "r");
    char *line = NULL;
    size_t len = 0;
    int is_user = 0;

    if (!stream)
        return;
    while (getline(&line, &len, stream) != -1) {
        parse_users(teams, line, &is_user);
        parse_teams(teams, line, &is_user);
        parse_mp(teams, line, &is_user);
    }
    fclose(stream);
    if (line != NULL)
        free(line);
}
