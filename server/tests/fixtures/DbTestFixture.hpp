#include <drogon/drogon.h>
#include <drogon/utils/coroutine.h>
#include <gtest/gtest.h>
#include <vector>
#include "repositories/UserRepository.hpp"

using UserRepository = messenger::repositories::UserRepository;
using User = drogon_model::messenger_db::Users;

using namespace drogon;
using namespace drogon::orm;

void runDrogon() {
    app().addListener("0.0.0.0", 5555);
    app().run();
}

class DbTestSuit : public ::testing::Test {
public:
    static inline std::thread serverThread_;

    static void SetUpTestSuite() {
        app().createDbClient(
            "postgresql",  // rdbms
            std::getenv("POSTGRES_HOST") ?: "localhost",
            5432,  // port
            std::getenv("POSTGRES_DB") ?: "messenger_db",
            std::getenv("POSTGRES_USER") ?: "messenger",
            std::getenv("POSTGRES_PASSWORD") ?: "",
            1  // connections
        );

        serverThread_ = std::thread(runDrogon);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    static void TearDownTestSuite() {
        app().quit();
        serverThread_.join();
    }

    void TearDown() override {
        auto dbClient = app().getDbClient();
        dbClient->execSqlSync("TRUNCATE TABLE users CASCADE;");
    }

protected:
    UserRepository user_repo_;
};