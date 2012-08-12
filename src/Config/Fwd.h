#ifndef FWD_H
#define FWD_H


namespace Agmd
{
    class Plane;
    class Rectangle;
    class Exception;
    class MemoryManager;
    class Logger;
    class Color;
    class File;
    class MediaManager;
    class Renderer;
    class Resource;
    class ResourceManager;
    class BaseBuffer;
    class Declaration;
    class Resource;
    class Model;
    class AgmdApp;
    class TextureBase;
    class Texture;
    class Image;
    class FontManager;
    class GraphicString;
    class BaseShader;
    class Shader;
	class BaseShaderProgram;
	class ShaderProgram;
    class Plugin;
	class FrameBuffer;
	class RenderBuffer;
    struct DeclarationElement;
    struct AssertException;
    struct BadDelete;
    struct LoadingFailed;
    struct OutOfMemory;
    struct BadConversion;
    template <class> class Buffer;
    template <class> class Loader;
    template <class, template <class> class> class SmartPtr;

}


#endif // FWD_H