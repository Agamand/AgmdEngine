#ifndef SKY_H
#define SKY_H



#include <Config/Fwd.h>
#include <Config/Export.h>
#include <Core/SceneObject/Displayable.h>

namespace Agmd
{
    class AGMD_EXPORT Sky : public Displayable
    {

    public:
        Sky(float size = 1.0f);
        virtual ~Sky();
        


    protected:
        float m_fSize;
    };
}

#endif //SKY_H