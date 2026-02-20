#include <drogon/orm/Result.h>
#include "fixtures/UserTestFixture.hpp"

using UserRepository = messenger::repositories::UserRepository;
using User = drogon_model::messenger_db::Users;

using namespace drogon;
using namespace drogon::orm;

TEST_F(UserTestFixture, TestCreate) {
    /* When valid data is provided,
    create() should return true
    and the user should be retrievable via getAll() */
    bool res = sync_wait(
        repo_.create("konobeitsev3", "Ivan konobeitsev", "hash_idk")
    );
    EXPECT_TRUE(res);
    auto users = sync_wait(repo_.getAll());
    EXPECT_EQ(users.size(), 1);
    User user = users[0];
    EXPECT_EQ(user.getValueOfHandle(), "konobeitsev3");
}

TEST_F(UserTestFixture, TestCreateSameHandle) {
    /* When user with given handle already exists,
    create() with the same handle should return false
    and no new user should be created */
    bool res = sync_wait(
        repo_.create("konobeitsev3", "Ivan konobeitsev", "hash_idk")
    );
    EXPECT_TRUE(res);
    bool res2 = sync_wait(
        repo_.create("konobeitsev3", "Ivan konobeitsev", "hash_idk")
    );
    EXPECT_FALSE(res2);
    auto users = sync_wait(repo_.getAll());
    EXPECT_EQ(users.size(), 1);
}

TEST_F(UserTestFixture, TestGetByHandle) {
    /* When user with given handle exists,
    getByHandle() should return it */
    bool res = sync_wait(
        repo_.create("konobeitsev3", "Ivan konobeitsev", "hash_idk")
    );
    EXPECT_TRUE(res);
    auto result = sync_wait(repo_.getByHandle("konobeitsev3"));
    EXPECT_TRUE(result.has_value());
    auto user = result.value();
    EXPECT_EQ(user.getValueOfHandle(), "konobeitsev3");
}

TEST_F(UserTestFixture, TestGetByHandleFail) {
    /* When user with given handle doesn't exist,
    getByHandle() should return nullopt */
    bool res = sync_wait(
        repo_.create("konobeitsev3", "Ivan konobeitsev", "hash_idk")
    );
    EXPECT_TRUE(res);
    auto result = sync_wait(repo_.getByHandle("some_user"));
    EXPECT_FALSE(result.has_value());
}

TEST_F(UserTestFixture, TestGetById) {
    /* When user with given id exists,
    getById() should return it */
    bool res = sync_wait(
        repo_.create("konobeitsev3", "Ivan konobeitsev", "hash_idk")
    );
    EXPECT_TRUE(res);
    auto result = sync_wait(repo_.getByHandle("konobeitsev3"));
    EXPECT_TRUE(result.has_value());
    auto user = result.value();
    auto result2 = sync_wait(repo_.getById(user.getValueOfId()));
    EXPECT_TRUE(result2.has_value());
    auto user2 = result2.value();
    EXPECT_EQ(user.getValueOfId(), user2.getValueOfId());
}

TEST_F(UserTestFixture, TestGetByIdFail) {
    /* When user with given id doesn't exist,
    getById() should return nullopt */
    bool res = sync_wait(
        repo_.create("konobeitsev3", "Ivan konobeitsev", "hash_idk")
    );
    EXPECT_TRUE(res);
    auto result = sync_wait(repo_.getById(100));
    EXPECT_FALSE(result.has_value());
}

TEST_F(UserTestFixture, TestGetAll) {
    /* When getAll called,
    it should return all users*/
    bool res1 = sync_wait(repo_.create("user1", "user1", "hash_idk"));
    bool res2 = sync_wait(repo_.create("user2", "user1", "hash_idk"));
    bool res3 = sync_wait(repo_.create("user3", "user1", "hash_idk"));
    EXPECT_TRUE(res1);
    EXPECT_TRUE(res2);
    EXPECT_TRUE(res3);
    auto users = sync_wait(repo_.getAll());
    EXPECT_EQ(users.size(), 3);
}

TEST_F(UserTestFixture, TestConcurrentCreateSameHandle) {
    /* When multiple threads attemp to create users
    with the same handle concurrently,
    exactly one should succeed
    and the rest should fail*/

    // otherwise the test does nothing
    EXPECT_TRUE(std::thread::hardware_concurrency() > 1);
    std::vector<std::thread> threads;
    std::atomic<int> success_count{0};
    for (int i = 0; i < 10; i++) {
        threads.push_back(std::thread([&]() {
            bool res = sync_wait(repo_.create(
                "konobeitsev3", "Ivan konobeitsev", "hash_idk"
            ));
            if (res) {
                success_count++;
            }
        }));
    }
    for (auto &t : threads) {
        t.join();
    }
    EXPECT_EQ(success_count, 1);
    auto users = sync_wait(repo_.getAll());
    EXPECT_EQ(users.size(), 1);
}
