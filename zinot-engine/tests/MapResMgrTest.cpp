//
// Created by patryk on 06.08.16.
//
#include <gtest/gtest.h>

#include <zinot-engine/res-sys/MapResMgr.hpp>
#include <zinot-engine/res-sys/NamesRegister.hpp>
#include <zinot-engine/res/Shader.hpp>

using Zinot::MapResMgr;
using Zinot::NamesRegister;
using Zinot::Shader;

class MapResMgrTest : public ::testing::Test
{
protected:
   MapResMgr mapResMgr;
   NamesRegister & namesRegister;
public:
   MapResMgrTest() : mapResMgr(), namesRegister(mapResMgr.getNamesRegister())
   {
   }
};

TEST_F(MapResMgrTest, OneOwner)
{
   NamesRegister::NameId res1id = namesRegister.getId("OneOwner", true);
   Shader * shd1inst1 = mapResMgr.newRes<Shader>(res1id);

   EXPECT_TRUE(shd1inst1);
   EXPECT_EQ(1, shd1inst1->getRefCount());
   EXPECT_EQ(&mapResMgr, shd1inst1->getResOwner());
   EXPECT_EQ("OneOwner", shd1inst1->getName());
   EXPECT_EQ(res1id, shd1inst1->getResId());

   mapResMgr.deleteRes(res1id);
}

TEST_F(MapResMgrTest, MultipleOwners)
{
   NamesRegister::NameId id = namesRegister.getId("MultipleOwners", true);
   Shader * shd2inst1 = mapResMgr.newRes<Shader>(id);

   EXPECT_TRUE(shd2inst1);
   EXPECT_EQ(&mapResMgr, shd2inst1->getResOwner());
   EXPECT_EQ("MultipleOwners", shd2inst1->getName());
   EXPECT_EQ(id, shd2inst1->getResId());

   EXPECT_EQ(1, shd2inst1->getRefCount());


   Shader * shd2inst2 = mapResMgr.newRes<Shader>(id);

   EXPECT_TRUE(shd2inst2);
   EXPECT_EQ(&mapResMgr, shd2inst2->getResOwner());
   EXPECT_EQ("MultipleOwners", shd2inst2->getName());
   EXPECT_EQ(id, shd2inst2->getResId());

   EXPECT_EQ(2, shd2inst1->getRefCount());
   EXPECT_EQ(2, shd2inst2->getRefCount());

   mapResMgr.deleteRes(id);
   mapResMgr.deleteRes(id);
}
