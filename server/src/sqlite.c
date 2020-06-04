#include "header.h"

void mx_init_sqli() {
	sqlite3 *db;
	//char *zErrMsg = 0;
	int rc = sqlite3_open("uchat.db", &db);

	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		exit(1);
	}
	else 
		fprintf(stderr, "Opened database successfully\n");
	//sqlite3_close(db)
}
