/*
============================================================================
Demo - A test application !

Author : 
Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
Jean-Vincent Lamberti (https://github.com/Kinroux)

https://github.com/Agamand/AgmdEngine
status : in pause
============================================================================
*/

#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <Core/Loader.h>
#include <Core/SceneObject/Model.h>
#include <Core/Enums.h>
#include <istream>

using namespace Agmd;

struct Sphere
{
    /*0x00*/ vec3 min;
    /*0x0C*/ vec3 max;
    /*0x18*/float radius;
};

struct M2RenderFlags
{
    a_uint16 flags;
    a_uint16 blendmode;
};

#define    TEXTURE_MAX    32
struct M2ModelTextureDef {
    a_uint32 type;
    a_uint32 flags;
    a_uint32 nameLen;
    a_uint32 nameOfs;
};

struct M2SkinHeader {
  a_uint32 Padding;        // Just some Padding.
  a_uint32 nIndices;        
  a_uint32 ofsIndices;        // Indices used in this View.
  a_uint32 nTriangles;        
  a_uint32 ofsTriangles;        // The triangles made with them.
  a_uint32 nProperties;        
  a_uint32 ofsProperties;        // Properties of the vertices.
  a_uint32 nSubmeshes;        
  a_uint32 ofsSubmeshes;        // Submeshes (Geosets) of this View.
  a_uint32 nTextureUnits;    
  a_uint32 ofsTextureUnits;    // Texture Units.
  a_uint32 LOD;            // LOD distance or something else
};

struct M2ModelHeader {
    a_int8 id[4];
    a_uint8 version[4];
    a_uint32 nameLength;
    a_uint32 nameOfs;
    a_uint32 GlobalModelFlags; // 1: tilt x, 2: tilt y, 4:, 8: add another field in header, 16: ; (no other flags as of 3.1.1);

    a_uint32 nGlobalSequences; // AnimationRelated
    a_uint32 ofsGlobalSequences; // A list of timestamps.
    a_uint32 nAnimations; // AnimationRelated
    a_uint32 ofsAnimations; // Information about the animations in the model.
    a_uint32 nAnimationLookup; // AnimationRelated
    a_uint32 ofsAnimationLookup; // Mapping of global IDs to the entries in the Animation sequences block.
    //uint32 nD;
    //uint32 ofsD;
    a_uint32 nBones; // BonesAndLookups
    a_uint32 ofsBones; // Information about the bones in this model.
    a_uint32 nKeyBoneLookup; // BonesAndLookups
    a_uint32 ofsKeyBoneLookup; // Lookup table for key skeletal bones.

    a_uint32 nVertices; // GeometryAndRendering
    a_uint32 ofsVertices; // Vertices of the model.
    a_uint32 nViews; // GeometryAndRendering
    //uint32 ofsViews; // Views (LOD) are now in .skins.

    a_uint32 nColors; // ColorsAndTransparency
    a_uint32 ofsColors; // Color definitions.

    a_uint32 nTextures; // TextureAndTheifAnimation
    a_uint32 ofsTextures; // Textures of this model.

    a_uint32 nTransparency; // H,  ColorsAndTransparency
    a_uint32 ofsTransparency; // Transparency of textures.
    //uint32 nI;   // always unused ?
    //uint32 ofsI;
    a_uint32 nTexAnims;    // J, TextureAndTheifAnimation
    a_uint32 ofsTexAnims;
    a_uint32 nTexReplace; // TextureAndTheifAnimation
    a_uint32 ofsTexReplace; // Replaceable Textures.

    a_uint32 nTexFlags; // Render Flags
    a_uint32 ofsTexFlags; // Blending modes / render flags.
    a_uint32 nBoneLookup; // BonesAndLookups
    a_uint32 ofsBoneLookup; // A bone lookup table.

    a_uint32 nTexLookup; // TextureAndTheifAnimation
    a_uint32 ofsTexLookup; // The same for textures.

    a_uint32 nTexUnitLookup;        // L, TextureAndTheifAnimation, seems gone after Cataclysm
    a_uint32 ofsTexUnitLookup; // And texture units. Somewhere they have to be too.
    a_uint32 nTransparencyLookup; // M, ColorsAndTransparency
    a_uint32 ofsTransparencyLookup; // Everything needs its lookup. Here are the transparencies.
    a_uint32 nTexAnimLookup; // TextureAndTheifAnimation
    a_uint32 ofsTexAnimLookup; // Wait. Do we have animated Textures? Wasn't ofsTexAnims deleted? oO

    Sphere collisionSphere;
    Sphere boundSphere;

    a_uint32 nBoundingTriangles; // Miscellaneous
    a_uint32 ofsBoundingTriangles;
    a_uint32 nBoundingVertices; // Miscellaneous
    a_uint32 ofsBoundingVertices;
    a_uint32 nBoundingNormals; // Miscellaneous
    a_uint32 ofsBoundingNormals;

    a_uint32 nAttachments; // O, Miscellaneous
    a_uint32 ofsAttachments; // Attachments are for weapons etc.
    a_uint32 nAttachLookup; // P, Miscellaneous
    a_uint32 ofsAttachLookup; // Of course with a lookup.
    a_uint32 nEvents; // 
    a_uint32 ofsEvents; // Used for playing sounds when dying and a lot else.
    a_uint32 nLights; // R
    a_uint32 ofsLights; // Lights are mainly used in loginscreens but in wands and some doodads too.
    a_uint32 nCameras; // S, Miscellaneous
    a_uint32 ofsCameras; // The cameras are present in most models for having a model in the Character-Tab.
    a_uint32 nCameraLookup; // Miscellaneous
    a_uint32 ofsCameraLookup; // And lookup-time again, unit16
    a_uint32 nRibbonEmitters; // U, Effects
    a_uint32 ofsRibbonEmitters; // Things swirling around. See the CoT-entrance for light-trails.
    a_uint32 nParticleEmitters; // V, Effects
    a_uint32 ofsParticleEmitters; // Spells and weapons, doodads and loginscreens use them. Blood dripping of a blade? Particles.
};

struct M2ModelVertex {
    vec3 pos;
    a_uint8 weights[4];
    a_uint8 bones[4];
    vec3 normal;
    vec2 texcoords;
    a_uint32 unk1, unk2;
};

class M2Loader : public Loader<Model>
{
public :

    M2Loader();
    ~M2Loader();

    virtual Model* LoadFromFile(const std::string& filename);
    virtual void SaveToFile(const Model* object, const std::string& filename);
        
private :
    static void OnError();
};



#endif //OBJLOADER_H