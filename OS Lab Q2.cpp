#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    int src, dest;
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source> <destination>\n", argv[0]);
        exit(1);
    }

    src = open(argv[1], O_RDONLY);
    if (src < 0) {
        perror("Error opening source file");
        exit(1);
    }

    dest = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest < 0) {
        perror("Error opening destination file");
        close(src);
        exit(1);
    }

    while ((bytesRead = read(src, buffer, BUFFER_SIZE)) > 0) {
        if (write(dest, buffer, bytesRead) != bytesRead) {
            perror("Error writing to destination file");
            close(src);
            close(dest);
            exit(1);
        }
    }

    close(src);
    close(dest);

    printf("File copied successfully!\n");
    return 0;
}

