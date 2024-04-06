/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** test
*/

    #include <stddef.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <sys/queue.h>

typedef struct teams_belong {
    char *uuid;
    TAILQ_ENTRY(teams_belong) belong_entries;
} team_belong_t;

typedef struct user_id {
    TAILQ_HEAD(tailhead, teams_belong) team_belong_uuid_head;
    int id;
    TAILQ_ENTRY(user_id) entries;
} user_id_t;

int main(void)
{
    TAILQ_HEAD(tailhead, user_id) head_user_id;
    user_id_t *n1_user_id, *np_user_id;
    team_belong_t *n1_team_belong, *np_team_belong;

    TAILQ_INIT(&head_user_id);
    n1_user_id = malloc(sizeof(user_id_t));
    TAILQ_INSERT_TAIL(&head_user_id, n1_user_id, entries);
    n1_user_id->id = 1;

    TAILQ_INIT(&n1_user_id->team_belong_uuid_head);
    n1_team_belong = malloc(sizeof(team_belong_t));
    TAILQ_INSERT_TAIL(&n1_user_id->team_belong_uuid_head, n1_team_belong, belong_entries);
    n1_team_belong->uuid = "enorme";

    n1_team_belong = malloc(sizeof(team_belong_t));
    TAILQ_INSERT_TAIL(&n1_user_id->team_belong_uuid_head, n1_team_belong, belong_entries);
    n1_team_belong->uuid = "excellentissime";

    n1_user_id = malloc(sizeof(user_id_t));
    TAILQ_INSERT_TAIL(&head_user_id, n1_user_id, entries);
    n1_user_id->id = 2;

    TAILQ_INIT(&n1_user_id->team_belong_uuid_head);
    n1_team_belong = malloc(sizeof(team_belong_t));
    TAILQ_INSERT_TAIL(&n1_user_id->team_belong_uuid_head, n1_team_belong, belong_entries);
    n1_team_belong->uuid = "oooooooooooooo";

    TAILQ_FOREACH(np_user_id, &head_user_id, entries) {
        printf("%d\n", np_user_id->id);
        TAILQ_FOREACH(np_team_belong, &np_user_id->team_belong_uuid_head, belong_entries) {
            printf("%s\n", np_team_belong->uuid);
        }
    }
}