//
// Created by patryk on 10.07.16.
//
#include <gtest/gtest.h>

#include <zinot-engine/res-sys/NamesRegister.hpp>
using Zinot::NamesRegister;

class NamesRegisterTest : public ::testing::Test
{
protected:
   NamesRegister namesRegister;
   NamesRegister::NameId name1, name2, name3;
};

TEST_F(NamesRegisterTest, BasicTest)
{
   name1 = namesRegister.getId("name1");
   name2 = namesRegister.getId("name2");
   name3 = namesRegister.getId("name3");

   EXPECT_EQ(name1, namesRegister.getId("name1"));
   EXPECT_EQ(name2, namesRegister.getId("name2"));
   EXPECT_EQ(name3, namesRegister.getId("name3"));

   EXPECT_EQ("name1", namesRegister.getName(name1));
   EXPECT_EQ("name2", namesRegister.getName(name2));
   EXPECT_EQ("name3", namesRegister.getName(name3));

   namesRegister.deleteId(name1);
   EXPECT_EQ(0, namesRegister.getId("name1", false));
   namesRegister.deleteId(name2);
   EXPECT_EQ(0, namesRegister.getId("name2", false));

   namesRegister.deleteName("name3");
   EXPECT_EQ(0, namesRegister.getId("name3", false));

}
