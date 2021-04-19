// Tekno's htab tests! wohoo
// @ligockym modificated

// for debug std::cout :)
#include <iostream>

// including C library from C++ file
extern "C" {
    #include "htab.h"
}

#include "gtest/gtest.h"
#include "htab_internal.h"

#define HTAB_BUCKET_COUNT 20

// Testing function
void for_each_add_one(htab_pair_t *data) {
    data->value = data->value + 1;
}

// empty htabs
class HtabEmpty : public ::testing::Test {
protected:
    HtabEmpty() {
        htab = htab_init(HTAB_BUCKET_COUNT);
    }
    virtual void TearDown() {
        htab_free(htab);
    }

    htab_t *htab;
};

// filled htabs
class HtabFilled : public ::testing::Test {
protected:
    HtabFilled() {
        htab = htab_init(HTAB_BUCKET_COUNT);
        key1 = htab_lookup_add(htab, "key1");
        key1->value = 1;

        key2 = htab_lookup_add(htab, "key2");
        key2 = htab_lookup_add(htab, "key2");
        key2->value = 2;

        key3 = htab_lookup_add(htab, "key3");
        key3 = htab_lookup_add(htab, "key3");
        key3 = htab_lookup_add(htab, "key3");
        key3->value = 3;

        keyNone = htab_lookup_add(htab, "");
        keyNone->value = 4;

    }
    virtual void TearDown() {
        htab_free(htab);
    }

    htab_t *htab;
    htab_pair_t *key1;
    htab_pair_t *key2;
    htab_pair_t *key3;
    htab_pair_t *keyNone;
};

// test htab_init and htab_free
TEST(Htab, Test_lifecycle) {
    htab_t *htab;
    EXPECT_NO_THROW({
        htab = htab_init(HTAB_BUCKET_COUNT);
    });
    EXPECT_TRUE(htab != NULL);

    EXPECT_NO_THROW({
        htab_free(htab);
    });
}

/**************************************************************************/
/*                            EMPTY HTAB TESTS                            */
/**************************************************************************/

TEST_F(HtabEmpty, Test_lookup_add) {
    EXPECT_TRUE(htab_lookup_add(htab, "key1") != NULL);
}
TEST_F(HtabEmpty, Test_lookup_add_multiple) {
    htab_pair_t *pair1 = htab_lookup_add(htab, "key1");
    EXPECT_EQ(pair1->value, 0);
    htab_pair_t *pair2 = htab_lookup_add(htab, "key1");
    htab_pair_t *pair3 = htab_lookup_add(htab, "key2");
    EXPECT_TRUE(pair1 != NULL);
    EXPECT_TRUE(pair3 != NULL);
    EXPECT_EQ(pair1, pair2);
    EXPECT_NE(pair1, pair3);
    EXPECT_EQ(pair2->value, 0);
    EXPECT_EQ(pair3->value, 0);
}

TEST_F(HtabEmpty, Test_find) {
    EXPECT_TRUE(htab_find(htab, "key1") == NULL);
}
TEST_F(HtabEmpty, Test_size) {
    EXPECT_EQ(htab_size(htab), 0);
}
TEST_F(HtabEmpty, Test_bucket_count) {
    EXPECT_EQ(htab_bucket_count(htab), HTAB_BUCKET_COUNT);
}
TEST_F(HtabEmpty, Test_erase) {
    EXPECT_FALSE(htab_erase(htab, "key"));
}

TEST_F(HtabEmpty, Test_for_each) {
    EXPECT_NO_THROW({
        htab_for_each(htab, for_each_add_one);
    });
}
TEST_F(HtabEmpty, Test_move) {
    htab_t *tmp;

    EXPECT_NO_THROW({
        tmp = htab_move(100, htab);
        htab_free(htab);

        htab = htab_move(5, tmp);
        htab_free(tmp);
    });
}
TEST_F(HtabEmpty, Test_clear) {
    EXPECT_NO_THROW({
        htab_clear(htab);
    });
}

/**************************************************************************/
/*                            FILLED HTAB TESTS                           */
/**************************************************************************/

TEST_F(HtabFilled, Test_find) {
    // Key 1, key 2, key 3, keyNone are from fixture
    keyNone = htab_find(htab, "");
    htab_pair_t *key4 = htab_find(htab, "key4");

    ASSERT_TRUE(key1 != nullptr);
    ASSERT_TRUE(key2 != nullptr);
    ASSERT_TRUE(key3 != nullptr);
    ASSERT_TRUE(keyNone != nullptr );
    ASSERT_TRUE(key4 == nullptr);

    ASSERT_EQ(key1->value, 1);
    ASSERT_EQ(key2->value, 2);
    ASSERT_EQ(key3->value, 3);
    ASSERT_EQ(keyNone->value, 4);
}
TEST_F(HtabFilled, Test_size) {
    EXPECT_EQ(htab_size(htab), 4);
}
TEST_F(HtabFilled, Test_bucket_count) {
    EXPECT_EQ(htab_bucket_count(htab), HTAB_BUCKET_COUNT);
}
TEST_F(HtabFilled, Test_erase) {

    // Original items key1, key2, key3, keyNone

    EXPECT_EQ(htab_size(htab), 4);
    EXPECT_TRUE(htab_erase(htab, "key1"));

    htab_pair_t *key2_m = htab_find(htab, "key2");
    htab_pair_t *key3_m = htab_find(htab, "key3");
    htab_pair_t *keyNone_m = htab_find(htab, "");

    EXPECT_EQ(key2_m, key2);
    EXPECT_EQ(key3_m, key3);
    EXPECT_EQ(keyNone_m, keyNone);

    EXPECT_EQ(htab_size(htab), 3);
    EXPECT_FALSE(htab_erase(htab, "key1"));

    EXPECT_EQ(key2_m, key2);
    EXPECT_EQ(key3_m, key3);
    EXPECT_EQ(keyNone_m, keyNone);

    EXPECT_EQ(htab_size(htab), 3);
    EXPECT_TRUE(htab_erase(htab, "key2"));

    EXPECT_EQ(key3_m, key3);
    EXPECT_EQ(keyNone_m, keyNone);

    EXPECT_EQ(htab_size(htab), 2);
    EXPECT_FALSE(htab_erase(htab, "key4")); // non existing

    EXPECT_EQ(key3_m, key3);
    EXPECT_EQ(keyNone_m, keyNone);

    EXPECT_EQ(htab_size(htab), 2);
    // remove item with "" key
    EXPECT_TRUE(htab_erase(htab, ""));
    EXPECT_EQ(htab_size(htab), 1);

    EXPECT_TRUE(htab_erase(htab, "key3"));
    EXPECT_EQ(htab_size(htab), 0);
}

TEST_F(HtabFilled, Test_for_each) {
    EXPECT_NO_THROW({
        htab_for_each(htab, for_each_add_one);
    });

    EXPECT_EQ(key1->value, 2);
    EXPECT_EQ(key2->value, 3);
    EXPECT_EQ(key3->value, 4);

}
TEST_F(HtabFilled, Test_move) {
    htab_t *tmp1;
    htab_t *tmp2;

    size_t origin_size = htab->size;

    EXPECT_NO_THROW({
        // --- htab -> tmp1
        tmp1 = htab_move(HTAB_BUCKET_COUNT, htab);

        // check if new size is same as old
        ASSERT_EQ(tmp1->size, origin_size);
        ASSERT_EQ(tmp1->arr_size, HTAB_BUCKET_COUNT);

        // check if all items from old table are in tmp1
        htab_pair_t *new_key1 = htab_find(tmp1, "key1");
        htab_pair_t *new_key2 = htab_find(tmp1, "key2");
        htab_pair_t *new_key3 = htab_find(tmp1, "key3");
        htab_pair_t *new_key4 = htab_find(tmp1, "key4"); // does not exist

        ASSERT_EQ(new_key1->value, 1);
        ASSERT_EQ(new_key2->value, 2);
        ASSERT_EQ(new_key3->value, 3);
        ASSERT_EQ(new_key4, nullptr);

        // check if old values are no longer in original table
        ASSERT_EQ(htab_find(htab, "key1"), nullptr);
        ASSERT_EQ(htab_find(htab, "key2"), nullptr);
        ASSERT_EQ(htab_find(htab, "key3"), nullptr);
        ASSERT_EQ(htab_find(htab, ""), nullptr);

        htab_free(htab);

        // --- tmp1 -> tmp2
        origin_size = tmp1->size;
        tmp2 = htab_move(HTAB_BUCKET_COUNT * 5, tmp1);

        // check if new size is same as old
        ASSERT_EQ(tmp2->size, origin_size);
        ASSERT_EQ(tmp2->arr_size, HTAB_BUCKET_COUNT * 5);

        new_key1 = htab_find(tmp2, "key1");
        new_key2 = htab_find(tmp2, "key2");
        new_key3 = htab_find(tmp2, "key3");
        new_key4 = htab_find(tmp2, "key4"); // does not exist

        ASSERT_EQ(new_key1->value, 1);
        ASSERT_EQ(new_key2->value, 2);
        ASSERT_EQ(new_key3->value, 3);
        ASSERT_EQ(new_key4, nullptr);

        htab_free(tmp1);

        // --- tmp2 -> htab
        origin_size = tmp2->size;
        htab = htab_move(HTAB_BUCKET_COUNT / 5, tmp2);
        ASSERT_EQ(htab->size, origin_size);
        ASSERT_EQ(htab->arr_size, HTAB_BUCKET_COUNT / 5);
        htab_free(tmp2);
    });


}
TEST_F(HtabFilled, Test_clear) {
    EXPECT_EQ(htab_size(htab), 4);
    EXPECT_NO_THROW({
        htab_clear(htab);
    });
    EXPECT_EQ(htab_size(htab), 0);
}