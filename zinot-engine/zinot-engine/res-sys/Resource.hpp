#ifndef RESOURCE_HPP
#define RESOURCE_HPP

#include <cstdint>
#include <QString>

namespace Zinot {
    class MapResMgr;

    class Engine;

    class Resource {
    public:
        typedef uint32_t ResId;
    private:
        Engine *engine = nullptr;
        MapResMgr *resOwner = nullptr;

        ResId resId = 0;
        bool loaded = false;
    protected:
    public:
        void setLoaded(bool loaded) {
            Resource::loaded = loaded;
        }

    public:
        Resource(Engine *engine, MapResMgr *resOwner, ResId resId) : engine(engine), resOwner(resOwner), resId(resId) {}

        virtual ~Resource();

        virtual ResId getResId() {
            return resId;
        }

        virtual MapResMgr *getResOwner() {
            return resOwner;
        }

        virtual Engine *getEngine() const {
            return engine;
        }

        virtual bool isLoaded() const {
            return loaded;
        }

        virtual QString getName();
    };
}

#endif // RESOURCE_HPP
