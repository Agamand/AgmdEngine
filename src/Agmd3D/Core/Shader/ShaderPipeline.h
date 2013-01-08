#ifndef _SHADERPIPELINE_H_
#define _SHADERPIPELINE_H_

#include <Config/Fwd.h>
#include <Core/Enums.h>

#include <Core/Shader/ShaderProgram.h>

#include <string>

namespace Agmd
{
    class ShaderPipeline
    {
    public:

        ShaderPipeline();
        ~ShaderPipeline();

        bool Enable(TRenderPass pass) const;
        void Disable() const;

        static ShaderPipeline* GetDefaultPipeline();
    private:
        ShaderProgram m_pipeline[MAX_RENDERPASS];
        static ShaderPipeline* s_defaultPipeline;
    };
}

#endif /* _SHADERPIPELINE_H_ */