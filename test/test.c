/*
** EPITECH PROJECT, 2024
** my_teams
** File description:
** test
*/

    #include <stddef.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <sys/queue.h>


typedef struct channel_id {
    char *team_uuid;
    int id;
    TAILQ_ENTRY(channel_id) entries;
} channel_id_t;

typedef struct teams {
    int team_id;
    char *uuid;
    char *name;
    char *description;
    TAILQ_ENTRY(teams) entries;             /* Tail queue */
} team_t;

typedef struct teams_belong {
    char *uuid;
    TAILQ_ENTRY(teams_belong) entries;             /* Tail queue */
} team_belong_t;

typedef struct user_id {
    // team_belong_t *teams_uuid;
    // TAILQ_HEAD(, team_belong_t) team_belong_uuid;
    int id;
    TAILQ_ENTRY(user_id) entries;
} user_id_t ;

TAILQ_HEAD(tailhead, teams);

int main(void)
{
    struct teams *n1_team, *n2_team, *n3_team, *np_team;
    struct user_id *n1_user_id, *n2_user_id, *n3_user_id, *np_user_id;
    struct teams_belong *n1_teams_belong, *n2_teams_belong, *n3_teams_belong, *np_teams_belong;
    struct tailhead head_team;
    struct tailhead head_user_id;
    struct tailhead head_teams_belong;
    int i;

    TAILQ_INIT(&head_team);
    // TAILQ_INIT(&head_teams_belong);

    n1_team = malloc(sizeof(team_t));
    TAILQ_INSERT_HEAD(&head_team, n1_team, entries);
    n1_team->uuid = "uuid";
    n1_team->description = "test Team";
    n1_team->name = "test";
    n1_team->team_id = 1;

    // n1_teams_belong = malloc(sizeof(team_belong_t));
    // TAILQ_INSERT_HEAD(&head_teams_belong, n1_teams_belong, entries);

    TAILQ_INIT(&head_user_id);
    n1_user_id = malloc(sizeof(user_id_t));
    TAILQ_INSERT_HEAD(&head_user_id, n1_user_id, entries);
    n1_user_id->id = 1;
    // TAILQ_INSERT_HEAD(&n1_user_id->team_belong_uuid, n1_teams_belong, entries);



    // TAILQ_INSERT_HEAD(&head_channel_id, n1_channel_id, entries);
    // n1_channel_id->id = 1;

    // n1 = malloc(sizeof(struct entry));      /* Insert at the tail */
    // TAILQ_INSERT_TAIL(&head, n1, entries);
    // n1->data = 20;
    // n1->uuid = "Peut";

    // n2 = malloc(sizeof(struct entry));      /* Insert after */
    // TAILQ_INSERT_AFTER(&head, n1, n2, entries);
    // n2->data = 30;
    // n2->uuid = "Etre";

    // n3 = malloc(sizeof(struct entry));      /* Insert before */
    // TAILQ_INSERT_BEFORE(n2, n3, entries);
    // n3->data = 40;
    // n3->uuid = ":)";

    // TAILQ_REMOVE(&head, n2, entries);       /* Deletion */
    // free(n2);
                                            /* Forward traversal */
    i = 0;
    TAILQ_FOREACH(np_team, &head_team, entries)
        printf("%s: uuid = %s; desc = %s; id = %d\n", np_team->name, np_team->uuid, np_team->description, np_team->team_id);
                                            /* Reverse traversal */
    // TAILQ_FOREACH_REVERSE(np, &head, tailhead, entries)
        // printf("%i\n", np->data);
                                            /* TailQ deletion */
    n1_team = TAILQ_FIRST(&head_team);
    while (n1_team != NULL) {
        n2_team = TAILQ_NEXT(n1_team, entries);
        free(n1_team);
        n1_team = n2_team;
    }
    TAILQ_INIT(&head_team);

    exit(EXIT_SUCCESS);
}
