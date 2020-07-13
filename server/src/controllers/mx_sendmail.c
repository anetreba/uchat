#include "header.h"

int mx_sendmail(const char *to, const char *from, const char *subject, const char *message) {
    int retval = -1;
    FILE *mailpipe = popen("sendmail -t", "w");
    if (mailpipe != NULL) {
        fprintf(mailpipe, "To: %s\n", to);
        fprintf(mailpipe, "From: %s\n", from);
        fprintf(mailpipe, "Subject: %s\n\n", subject);
        fwrite(message, 1, mx_strlen(message), mailpipe);
        fwrite(".\n", 1, 2, mailpipe);
        pclose(mailpipe);
        retval = 0;
    }
    else {
        perror("Failed to invoke sendmail");
    }
    return retval;
}
