#include "header.h"

int mx_sendmail(const char *to, const char *from, const char *subject, const char *message) {
    from = NULL;
    int p2cFd[2];

    int ret = pipe(p2cFd);
    if (ret) {
        return ret;
    }
    pid_t child_pid = fork();
    if (child_pid < 0) {
        close(p2cFd[0]);
        close(p2cFd[1]);

        return child_pid;
    }
    else if (!child_pid) {
        dup2(p2cFd[0], 0);
        close(p2cFd[0]);
        close(p2cFd[1]);

        char n =execlp("mail", "mail", "-s", subject, to, message);
        printf("EXEC: %c\n", n);
    }

    close(p2cFd[0]);

    ret = write(p2cFd[1], message, mx_strlen(message));
    if (ret < 0) {
        return ret;
    }
    close(p2cFd[1]);

    if (waitpid(child_pid, &ret, 0) == -1) {
        return ret;
    }
    return 0;
}
