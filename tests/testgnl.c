#include "../pipex.h"

int main(int argc, char *argv[])
{
    int fd;
    //test access :::

    // fd = open("file2.txt", O_RDWR | O_APPEND);
    fd = access(argv[1], F_OK);
    if (fd == -1)
        perror("ERROR");
    else
        printf("the path is exist");
    // char *str;
    // str = get_next_line(fd);
    // while (str)
    // {
    //     printf("%s\n", str);
    //     free(str);
    //     str = get_next_line(fd);
    // }
}