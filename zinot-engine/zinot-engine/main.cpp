#include <zinot-engine/eng/Engine.hpp>

#ifndef NDEBUG
#include <gtest/gtest.h>
#endif

int main(int argc, char * argv[])
{
#ifndef NDEBUG
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
#endif

   Zinot::Engine eng;
   return eng.main();
}
