#include "Resource.hpp"

#include <zinot-engine/res-sys/MapResMgr.hpp>

namespace Zinot {

    Resource::~Resource() {
        auto &namesReg = resOwner->getNamesRegister();
        namesReg.deleteId(resId);
    }

    QString Resource::getName() {
        return resOwner->getNamesRegister().getName(resId);
    }

}