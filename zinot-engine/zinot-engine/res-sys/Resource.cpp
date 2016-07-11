#include "Resource.hpp"

namespace Zinot
{

Resource::Resource()
{
   refCount = 0;
   resId = 0;
   resOwner = nullptr;
}

Resource::~Resource()
{ }

Resource::Resource(const Resource & src)
{
   refCount = src.refCount;
   resId = src.resId;
   resOwner = src.resOwner;
}

Resource::Resource(Resource && src)
{
   refCount = std::move(src.refCount);
   resId = std::move(src.resId);
   resOwner = std::move(src.resOwner);
}
}