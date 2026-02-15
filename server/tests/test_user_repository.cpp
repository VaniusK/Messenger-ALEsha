#include <drogon/drogon.h>
#include <drogon/utils/coroutine.h>
#include <gtest/gtest.h>
#include <repositories/UserRepository.hpp>
#include <vector>

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

        std::thread serverThread(runDrogon);
        serverThread.detach();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    static void TearDownTestSuite() {
        app().quit();
    }

    void TearDown() override {
        auto dbClient = app().getDbClient();
        dbClient->execSqlSync("TRUNCATE TABLE users CASCADE;");
    }
};

TEST_F(DbTestSuit, TestCreate) {
    bool res = sync_wait(
        UserRepository::create("konobeitsev3", "Ivan_konobeitsev", "hash_idk")
    );
    EXPECT_TRUE(res);
    auto users = sync_wait(UserRepository::getAll());
    EXPECT_EQ(users.size(), 1);
    User user = users[0];
    EXPECT_EQ(user.getValueOfHandle(), "konobeitsev3");
}

TEST_F(DbTestSuit, TestGetByHandle) {
    bool res = sync_wait(
        UserRepository::create("konobeitsev3", "Ivan_konobeitsev", "hash_idk")
    );
    EXPECT_TRUE(res);
    auto result = sync_wait(UserRepository::getByHandle("konobeitsev3"));
    EXPECT_TRUE(result.has_value());
    auto user = result.value();
    EXPECT_EQ(user.getValueOfHandle(), "konobeitsev3");
}

TEST_F(DbTestSuit, TestGetById) {
    bool res = sync_wait(
        UserRepository::create("konobeitsev3", "Ivan_konobeitsev", "hash_idk")
    );
    EXPECT_TRUE(res);
    auto result = sync_wait(UserRepository::getByHandle("konobeitsev3"));
    EXPECT_TRUE(result.has_value());
    auto user = result.value();
    auto result2 = sync_wait(UserRepository::getById(user.getValueOfId()));
    EXPECT_TRUE(result2.has_value());
    auto user2 = result2.value();
    EXPECT_EQ(user.getValueOfId(), user2.getValueOfId());
}

TEST_F(DbTestSuit, TestCreateSameHandle) {
    bool res = sync_wait(
        UserRepository::create("konobeitsev3", "Ivan_konobeitsev", "hash_idk")
    );
    EXPECT_TRUE(res);
    bool res2 = sync_wait(
        UserRepository::create("konobeitsev3", "Ivan_konobeitsev", "hash_idk")
    );
    EXPECT_FALSE(res2);
}
