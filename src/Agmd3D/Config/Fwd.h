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
    class Driver;
    class Resource;
    class ResourceManager;
    class Declaration;
    class AgmdApplication;
    class TextureBase;
    class Texture;
    class Image;
    class FontManager;
    class GraphicString;
    class Scene;
    class Material;
    class Statistics;
    struct DeclarationElement;
    template <class>
    class Loader;


    //Shader Class

    class BaseShader;
    class Shader;
    class BaseShaderProgram;
    class ShaderProgram;
    class ShaderPipeline;

    //Buffer Class

    class BaseBuffer;
    template <class>
    class Buffer;
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
    class Bounding;
    class BoundingBox;
    class BoundingSphere;
    class Fast2DSurface;

    //Scene Class

    class SceneMgr;
    class SceneNode;
    class DisplayNode;
    class LightNode;
    class MeshNode;
    class CameraNode;

    //Controller Class

    class Controller;
    class InputController;
    class FirstPersonController;
    class ThirdPersonController;
}


#endif /* _FWD_H_ */
