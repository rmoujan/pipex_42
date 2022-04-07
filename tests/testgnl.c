#include "pipex.h"

int main()
{
    int fd;

    fd = open("file2.txt", O_RDWR | O_APPEND);

    char *str;

    str = get_next_line(fd);
    while (str)
    {
        printf("%s\n", str);
        free(str);
        str = get_next_line(fd);
    }
}