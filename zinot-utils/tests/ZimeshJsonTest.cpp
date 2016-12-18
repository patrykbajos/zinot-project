//
// Created by patryk on 10.12.16.
//
#include <gtest/gtest.h>
#include <zinot-utils/zimesh-json/ZimeshJsonReader.hpp>

class ZimeshJsonTest : public ::testing::Test
{
protected:
   Zimesh::ZimeshJsonDao zimeshJsonDao;
};

TEST_F(ZimeshJsonTest, loading)
{
   EXPECT_TRUE(Zimesh::ZimeshJsonReader::loadFromJson("media/models/table.json", zimeshJsonDao));
   Zimesh::ZimeshJsonDao & dao = zimeshJsonDao;
}
