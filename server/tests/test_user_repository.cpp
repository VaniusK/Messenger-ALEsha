#include "fixtures/DbTestFixture.hpp"

using UserRepository = messenger::repositories::UserRepository;
using User = drogon_model::messenger_db::Users;

using namespace drogon;
using namespace drogon::orm;

TEST_F(DbTestSuit, TestCreate) {
    /* When valid data is provided,
    create() should return true
    and the user should be retrievable via getAll() */
    bool res = sync_wait(
        user_repo_.create("konobeitsev3", "Ivan konobeitsev", "hash_idk")
    );
    EXPECT_TRUE(res);
    auto users = sync_wait(user_repo_.getAll());
    EXPECT_EQ(users.size(), 1);
    User user = users[0];
    EXPECT_EQ(user.getValueOfHandle(), "konobeitsev3");
}

TEST_F(DbTestSuit, TestGetByHandle) {
    /* When user with given handle exists,
    getByHandle() should return it */
    bool res = sync_wait(
        user_repo_.create("konobeitsev3", "Ivan konobeitsev", "hash_idk")
    );
    EXPECT_TRUE(res);
    auto result = sync_wait(user_repo_.getByHandle("konobeitsev3"));
    EXPECT_TRUE(result.has_value());
    auto user = result.value();
    EXPECT_EQ(user.getValueOfHandle(), "konobeitsev3");
}

TEST_F(DbTestSuit, TestGetById) {
    /* When user with given id exists,
    getById() should return it */
    bool res = sync_wait(
        user_repo_.create("konobeitsev3", "Ivan konobeitsev", "hash_idk")
    );
    EXPECT_TRUE(res);
    auto result = sync_wait(user_repo_.getByHandle("konobeitsev3"));
    EXPECT_TRUE(result.has_value());
    auto user = result.value();
    auto result2 = sync_wait(user_repo_.getById(user.getValueOfId()));
    EXPECT_TRUE(result2.has_value());
    auto user2 = result2.value();
    EXPECT_EQ(user.getValueOfId(), user2.getValueOfId());
}

TEST_F(DbTestSuit, TestCreateSameHandle) {
    /* When user with given handle already exists,
    create() with the same handle should return false
    and no new user should be created */
    bool res = sync_wait(
        user_repo_.create("konobeitsev3", "Ivan konobeitsev", "hash_idk")
    );
    EXPECT_TRUE(res);
    bool res2 = sync_wait(
        user_repo_.create("konobeitsev3", "Ivan konobeitsev", "hash_idk")
    );
    EXPECT_FALSE(res2);
    auto users = sync_wait(user_repo_.getAll());
    EXPECT_EQ(users.size(), 1);
}
