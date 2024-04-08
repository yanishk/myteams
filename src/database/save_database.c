/*
** EPITECH PROJECT, 2024
** myteams
** File description:
** save_database
*/

#include <unistd.h>
#include <fcntl.h>
#include "teams.h"

static void save_team_belong(int fd, user_t *user)
{
    team_belong_t *team_belong;

    dprintf(fd, "\tteams_uuid=");
    TAILQ_FOREACH(team_belong, &user->team_belong_head,
        belong_entries) {
        dprintf(fd, "%s", team_belong->uuid);
        if (TAILQ_NEXT(team_belong, belong_entries) != NULL)
            dprintf(fd, ",");
        if (TAILQ_NEXT(team_belong, belong_entries) == NULL)
            dprintf(fd, "\n");
    }
}

static void save_private_msg(int fd, user_t *user)
{
    private_msg_t *private_msg;

    dprintf(fd, "\tprivate_message=");
    TAILQ_FOREACH(private_msg, &user->private_msg_head,
        private_msg_entries) {
        dprintf(fd, "user_id=%s,", private_msg->uuid_other);
        dprintf(fd, "body=%s", private_msg->body);
        if (TAILQ_NEXT(private_msg, private_msg_entries) != NULL)
            dprintf(fd, ",");
        if (TAILQ_NEXT(private_msg, private_msg_entries) == NULL)
            dprintf(fd, "\n");
    }
}

static void save_users(const my_teams_t teams)
{
    user_t *user;
    int fd = open("database", O_WRONLY | O_TRUNC | O_CREAT, 422);

    dprintf(fd, "struct user:\n");
    TAILQ_FOREACH(user, &teams.user_head, user_entries) {
        dprintf(fd, "user:\n");
        dprintf(fd, "\tuuid=%s\n", user->uuid);
        dprintf(fd, "\tname=%s\n", user->name);
        save_team_belong(fd, user);
        save_private_msg(fd, user);
    }
    close(fd);
}

void save_database(const my_teams_t teams)
{
    save_users(teams);
}
