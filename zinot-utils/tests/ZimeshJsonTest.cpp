//
// Created by patryk on 10.12.16.
//
#include <gtest/gtest.h>
#include <zinot-utils/json/JsonReader.hpp>

class ZimeshJsonTest : public ::testing::Test
{
protected:
   Zimesh::ZimeshJsonDao zimeshJsonDao;
};

TEST_F(ZimeshJsonTest, loading)
{
   EXPECT_TRUE(Zimesh::JsonReader::loadFromJson("media/models/table/table.json", zimeshJsonDao));
}
