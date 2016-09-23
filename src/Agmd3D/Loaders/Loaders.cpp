/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Loaders/Loaders.h>
#include <Loaders/ImagesLoader.h>
#include <Loaders/ShadersLoader.h>
#include <Loaders/ShaderProgramsLoader.h>
#include <Loaders/ObjLoader.h>
#include <Loaders/TxtLoader.h>
#include <Loaders/ShaderPipelineLoader.h>
#include <Core/MediaManager.h>
#include <Debug/New.h>


namespace Agmd
{
    void RegisterLoaders()
    {
        MediaManager& mediaManager = MediaManager::Instance();

        mediaManager.RegisterLoader(new ImagesLoader, "bmp, dds, jpg, pcx, png, pnm, raw, sgi, tga, tif");
        mediaManager.RegisterLoader(new ShadersLoader(SHADER_VERTEX), "vert");
        mediaManager.RegisterLoader(new ShadersLoader(SHADER_PIXEL), "frag");
        mediaManager.RegisterLoader(new ShadersLoader(SHADER_GEOMETRY), "geom");
        mediaManager.RegisterLoader(new ShadersLoader(SHADER_TESS_CONTROL), "tessc");
        mediaManager.RegisterLoader(new ShadersLoader(SHADER_TESS_EVALUATION), "tesse");
        mediaManager.RegisterLoader(new ShaderProgramsLoader(), "glsl, hlsl");
        //mediaManager.RegisterLoader(new TxtLoader(),"txt");
        mediaManager.RegisterLoader(new ObjLoader(), "obj");
        mediaManager.RegisterLoader(new ShaderPipelineLoader(), "shader");
    }
} // namespace Agmd
