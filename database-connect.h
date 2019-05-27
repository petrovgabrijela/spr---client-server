#define DATABASE_NAME "torrent"
#define HOST "localhost"
#define PORT 3306
#define USERNAME "root"
#define PASSWORD "0644494599lL?"

MYSQL* connectToDatabase();
void closeConnection(MYSQL *connection);
