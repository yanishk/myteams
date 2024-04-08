/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** test
*/

#include <fcntl.h>
#include "teams.h"
#include "my.h"

void save_users(const my_teams_t teams)
{
    int fd = open("database", O_WRONLY | O_TRUNC | O_CREAT, 422);
    user_t *np_user;
    team_belong_t *np_team_belong;

    dprintf(fd, "struct user:\n");
    TAILQ_FOREACH(np_user, &teams.user_head, user_entries) {
        dprintf(fd, "user:\n");
        dprintf(fd, "\tuuid=%s\n", np_user->uuid);
        dprintf(fd, "\tname=%s\n", np_user->name);
        dprintf(fd, "\tteams_uuid=");
        TAILQ_FOREACH(np_team_belong, &np_user->team_belong_uuid_head,
            belong_entries) {
            dprintf(fd, "%s", np_team_belong->uuid);
            if (TAILQ_NEXT(np_team_belong, belong_entries) != NULL)
                dprintf(fd, ",");
            if (TAILQ_NEXT(np_team_belong, belong_entries) == NULL)
                dprintf(fd, "\n");
        }
    }
    close(fd);
}

void fill_user_team_belong(my_teams_t *teams, user_t *new_user, char **array)
{
    team_belong_t *new_team_belong;

    TAILQ_INIT(&new_user->team_belong_uuid_head);
    for (int i = 1; array[i] != NULL; i += 1) {
        new_team_belong = malloc(sizeof(team_belong_t));
        TAILQ_INSERT_TAIL(&new_user->team_belong_uuid_head, new_team_belong,
            belong_entries);
        new_team_belong->uuid = array[i];
    }
}

void parse_users(my_teams_t *teams, char *line)
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
        fill_user_team_belong(teams, new_user, array);
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

void fill_user_tailq(my_teams_t *teams)
{
    user_t *n1_user;
    team_belong_t *n1_team_belong;

    n1_user = malloc(sizeof(user_t));
    TAILQ_INSERT_TAIL(&teams->user_head, n1_user, user_entries);
    n1_user->uuid = "uuid1";
    n1_user->name = "gros caca";

    TAILQ_INIT(&n1_user->team_belong_uuid_head);
    n1_team_belong = malloc(sizeof(team_belong_t));
    TAILQ_INSERT_TAIL(&n1_user->team_belong_uuid_head, n1_team_belong, belong_entries);
    n1_team_belong->uuid = "enorme";

    n1_team_belong = malloc(sizeof(team_belong_t));
    TAILQ_INSERT_TAIL(&n1_user->team_belong_uuid_head, n1_team_belong, belong_entries);
    n1_team_belong->uuid = "excellentissime";

    n1_user = malloc(sizeof(user_t));
    TAILQ_INSERT_TAIL(&teams->user_head, n1_user, user_entries);
    n1_user->uuid = "uuid2";
    n1_user->name = "yanis";

    TAILQ_INIT(&n1_user->team_belong_uuid_head);
    n1_team_belong = malloc(sizeof(team_belong_t));
    TAILQ_INSERT_TAIL(&n1_user->team_belong_uuid_head, n1_team_belong, belong_entries);
    n1_team_belong->uuid = "oooooooooooooo";
}

void fill_team_tailq(my_teams_t *teams)
{
    team_t *n1_team;

    n1_team = malloc(sizeof(team_t));
    TAILQ_INSERT_TAIL(&teams->team_head, n1_team, team_entries);
    n1_team->uuid = "team_uuid1";
    n1_team->name = "team_name1";
    n1_team->description = "ceci est une description de la team1";
}

void print_user_tailq(my_teams_t teams)
{
    user_t *np_user;
    team_belong_t *np_team_belong;

    TAILQ_FOREACH(np_user, &teams.user_head, user_entries) {
        printf("user_uuid: %s\n", np_user->uuid);
        printf("user_name: %s\n", np_user->name);
        TAILQ_FOREACH(np_team_belong, &np_user->team_belong_uuid_head,
            belong_entries) {
            printf("user team_uuid: %s\n", np_team_belong->uuid);
        }
    }
}

void print_team_tailq(my_teams_t teams)
{
    team_t *np_team;

    TAILQ_FOREACH(np_team, &teams.team_head, team_entries) {
        printf("team_uuid: %s\n", np_team->uuid);
        printf("team_name: %s\n", np_team->name);
        printf("team_description: %s\n", np_team->description);
    }

}

int main(void)
{
    my_teams_t teams;

    TAILQ_INIT(&teams.user_head);
    // parse_database(&teams);
    // fill_user_tailq(&teams);
    // save_users(teams);
    // print_user_tailq(teams);

    TAILQ_INIT(&teams.team_head);
    fill_team_tailq(&teams);
    print_team_tailq(teams);
}
