#include <drogon/drogon.h>

int main() {
    setbuf(stdout, nullptr); // disabling stdout buffer for real-time logs in console(comment on realease and turn on file logs)
    
    LOG_INFO << "Starting server on port 5555";

    drogon::app().loadConfigFile("config.json");

    drogon::orm::PostgresConfig dbConfig;
    dbConfig.host = std::getenv("POSTGRES_HOST") ?: "localhost";
    dbConfig.port = 5432;
    dbConfig.databaseName = std::getenv("POSTGRES_DB") ?: "messenger_db";
    dbConfig.username = std::getenv("POSTGRES_USER") ?: "messenger";
    dbConfig.password = std::getenv("POSTGRES_PASSWORD") ?: "";
    dbConfig.connectionNumber = 50;
    dbConfig.name = "default";
    dbConfig.timeout = -1.0;
    dbConfig.isFast = true;
    drogon::app().addDbClient(dbConfig);
    drogon::app().setThreadNum(0);
    drogon::app().run();
    return 0;
}
