#ifndef EXPORT_PHYSICS_H
#define EXPORT_PHYSICS_H

namespace AgmdPhysics
{
    #ifdef AGMDPHYSICS_EXPORTS
    #   define PHYSICS_EXPORT __declspec(dllexport)
    #else
    #   define PHYSICS_EXPORT __declspec(dllimport)
    #endif

    #ifdef _MSC_VER
    #   pragma warning(disable : 4251)
    #   pragma warning(disable : 4661)
    #endif
}
#endif // EXPORT_PHYSICS_H