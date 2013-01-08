#ifndef FWD_H
#define FWD_H


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

    struct Transform;

    //GUI Class

    class GUIMgr;
    class EventMgr;
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


#endif // FWD_H