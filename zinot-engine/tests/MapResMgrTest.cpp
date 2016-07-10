#include <gtest/gtest.h>
#include <zinot-engine/resources/MapResMgr.hpp>
#include <zinot-engine/engine/resources/Shader.hpp>

/*class MapResMgrTest : public ::testing::Test
{
protected:
	virtual void SetUp();
	virtual void TearDown();
	Zinot::MapResMgr * resMgr;
};

void MapResMgrTest::SetUp()
{
	resMgr = new Zinot::MapResMgr();
}

void MapResMgrTest::TearDown()
{
	delete resMgr;
}

TEST_F(MapResMgrTest, operations)
{
	// Pobiera zasob
	auto res = resMgr->getRes("shader");

	// Jesli cos jest przypisane
	// POWINNO SIE WYKONAC!!!
	if (res == nullptr)
	{
		res = resMgr->newRes("shader", new Zinot::Shader);
	}

	auto res2 = resMgr->getRes("shader");
	EXPECT_EQ(res, res2);

	resMgr->deleteRes("shader");
	resMgr->deleteRes("shader");
}*/
