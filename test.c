#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int fd;
    fd = open(argv[1], O_RDWR ,0666);
    printf("%d", fd);
    return (0);
}