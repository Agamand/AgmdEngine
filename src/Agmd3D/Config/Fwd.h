/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _FWD_H_
#define _FWD_H_


namespace Agmd
{
    //General Class

    class MediaManager;
    class Renderer;
    class Resource;
    class ResourceManager;
    class Declaration;
    class AgmdApp;
    class TextureBase;
    class Texture;
    class Image;
    class FontManager;
    class GraphicString;
    class Scene;
    class Material;
    struct DeclarationElement;
    template <class> class Loader;


    //Shader Class

    class BaseShader;
    class Shader;
    class BaseShaderProgram;
    class ShaderProgram;
    class ShaderPipeline;

    //Buffer Class

    class BaseBuffer;
    template <class> class Buffer;
    class FrameBuffer;
    class RenderBuffer;

    //Model Class

    class Model;
    class Terrain;
    class Water;
    class Sky;
    class Light;

    //GUI Class

    class GUIMgr;
    class AWidget;
    class AContainer;
    class AWindow;
    class ATextBox;
    class AButton;

    //Rendering Mode
    class RenderingMode;
    class ForwardRendering;
    class VertexRendering;
    class DeferredRendering;

    //Tools Class

    class Frustum;
    class BoundingBox;
    class Fast2DSurface;
    class DeferredRendering;

}


#endif /* _FWD_H_ */