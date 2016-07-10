#include <zinot-engine/engine/Engine.hpp>

#ifdef DEBUG

//#include <gtest/gtest.h>
#endif

int main(int argc, char * argv[])
{
/*#ifdef DEBUG
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
#endif*/

   Zinot::Engine eng;
   return eng.main();
}
