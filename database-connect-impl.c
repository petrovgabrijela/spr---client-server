#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "database-connect.h"

MYSQL* connectToDatabase()
{
    MYSQL *connection = mysql_init(NULL);

    if (connection == NULL) {
        printf("Error %u %s\n", mysql_errno(connection), mysql_error(connection));
        exit(1);
    }

    if (mysql_real_connect(connection, HOST, USERNAME, PASSWORD, DATABASE_NAME, PORT, NULL, 0) == NULL) {
        printf("Error %u: %s\n", mysql_errno(connection), mysql_error(connection));
        exit(1);
    }

    return connection;
}

void closeConnection(MYSQL *connection)
{
   mysql_close(connection);
}
