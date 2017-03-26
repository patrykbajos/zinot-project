//
// Created by patryk on 06.08.16.
//
#include <gtest/gtest.h>

#include <zinot-engine/res-sys/MapResMgr.hpp>
#include <zinot-engine/res-sys/NamesRegister.hpp>

using Zinot::MapResMgr;
using Zinot::NamesRegister;
using Zinot::Resource;

class MapResMgrTest : public ::testing::Test
{
protected:
   MapResMgr mapResMgr;
public:
   MapResMgrTest() : mapResMgr()
   {
   }
};

TEST_F(MapResMgrTest, OneOwner)
{
   QString shd1name = "shader/shd1.shd";
   MapResMgr::ResPtr<Resource> shd1inst1 = mapResMgr.getRes<Resource>(shd1name);

   EXPECT_TRUE(shd1inst1);
   EXPECT_EQ(2, shd1inst1.use_count()); // One here and one in MapResMgr
   EXPECT_EQ(&mapResMgr, shd1inst1->getResOwner());
   EXPECT_EQ("shader/shd1.shd", shd1inst1->getName());
   EXPECT_EQ(1, mapResMgr.getResourcesNum());

   shd1inst1.reset();
   mapResMgr.tryDeleteRes(shd1name);
   EXPECT_EQ(0, mapResMgr.getResourcesNum());
}

TEST_F(MapResMgrTest, MultipleOwners)
{
   QString name = "/multiple/owners.txt";

   MapResMgr::ResPtr<Resource> res1 = mapResMgr.getRes<Resource>(name);

   EXPECT_TRUE(res1);
   EXPECT_EQ(&mapResMgr, res1->getResOwner());
   EXPECT_EQ("/multiple/owners.txt", res1->getName());
   EXPECT_EQ(2, res1.use_count()); // One here and one in MapResMgr

   MapResMgr::ResPtr<Resource> res2 = mapResMgr.getRes<Resource>(name);

   EXPECT_TRUE(res2);
   EXPECT_EQ(&mapResMgr, res2->getResOwner());
   EXPECT_EQ("/multiple/owners.txt", res2->getName());

   EXPECT_EQ(3, res1.use_count()); // Two here and one in MapResMgr
   EXPECT_EQ(3, res2.use_count()); // Two here and one in MapResMgr

   res1.reset();
   mapResMgr.tryDeleteRes(name);   // Here is only one using
   EXPECT_EQ(2, res2.use_count()); // One here and one in MapResMgr

   res2.reset();
   mapResMgr.tryDeleteRes(name);   // Here is only using in MapResMgr so res is deleted

   // ResMgr now is empty
   EXPECT_EQ(0, mapResMgr.getResourcesNum());
}
