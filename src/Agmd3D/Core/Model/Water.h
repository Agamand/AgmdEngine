/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef WATER_H
#define WATER_H

#include <Vector2.h>
#include <Core/Model/Model.h>


#include <string>

namespace Agmd
{

    struct WaveParameters
    {
        float speed;
        float amplitude;
        float wavelength;
        float steepness;
    };

    struct WaveDirections
    {
        float x;
        float y;
    };

    class AGMD3D_EXPORT Water : public Model
    {
    public:
        Water(ivec2 _size, ivec2 _poly);
        ~Water();

        virtual void Render() const;
        void SetScene(Scene* sc);
        void prepare();

    private:

        void generate();
        void GenerateCubeMap() const;
        void GenerateNormal() const;
        ivec2 size;
        ivec2 n_poly;

        Scene* scene; // Scene use to make Reflection & Refraction texture
        BaseShaderProgram* m_program;
        BaseShaderProgram* m_programWaterNormal;
        mat4 m_projection;
        Texture m_CubeMap;
        Texture m_WaterNormal;
        FrameBuffer* fbo[2];
        RenderBuffer* m_Depth;
        WaveParameters m_PWave[4];
        WaveDirections m_DWave[4];
        float m_timer;
    };

}

#endif //WATER_H