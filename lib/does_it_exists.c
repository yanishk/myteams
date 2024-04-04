/*
** EPITECH PROJECT, 2024
** B-NWP-400-PAR-4-1-myftp-yanis.harkouk
** File description:
** does_exists
*/

#include <stdbool.h>
#include <sys/stat.h>
#include <stddef.h>

char *does_path_exists(char *str)
{
    struct stat sb;
    char *path = NULL;

    if (stat(str, &sb) == 0 && (sb.st_mode & S_IFDIR))
        path = str;
    return path;
}

bool does_file_exists(char *str)
{
    struct stat sb;

    return (stat(str, &sb) == 0 && (sb.st_mode & S_IFREG));
}
