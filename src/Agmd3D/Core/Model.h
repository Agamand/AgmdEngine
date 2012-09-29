#ifndef MODEL_H
#define MODEL_H

#include <Config/Fwd.h>
#include <Core/Resource.h>
#include <Core/Buffer/Buffer.h>
#include <Core/Declaration.h>
#include <Core/Texture.h>
#include <Core/Enums.h>
#include <Utilities/SmartPtr.h>
#include <Vector2.h>
#include <Vector3.h>
#include <Matrix4.h>

using namespace AgmdMaths;

namespace Agmd
{

	enum GenerateType
	{
		G_NONE = 0x0,
		G_NORMAL = 0x1,
		G_TANGENT = 0x2,
		G_ALL = G_NORMAL | G_TANGENT
	};

	struct AGMD_EXPORT TextureUnit
	{
		TextureUnit() :
		use(false)
		{}

		TextureUnit(Texture _tex) : 
		tex(_tex),
		use(true)
		{}

		Texture tex;
		bool use;
	};

	enum RenderFlags
	{
		RENDERFLAGS_NULL		= 0x00,
		RENDERFLAGS_UNLIT		= 0x01,
		RENDERFLAGS_UNFOGGED	= 0x02,
		RENDERFLAGS_TWOSIDED	= 0x04,
		RENDERFLAGS_BILLBOARD	= 0x08,
		RENDERFLAGS_ZBUFFERED	= 0x10
	};

	struct ModelRenderPass {
		uint32 indexStart, indexCount, vertexStart, vertexEnd;
		TextureUnit m_Textures[MAX_TEXTUREUNIT];
		int tex;
		bool useTex2, useEnvMap, trans;
		float p;
	
		int16 texanim, color, opacity, blendmode;

		// Geoset ID
		int geoset;

		// texture wrapping
		bool swrap, twrap;

		bool init(Model *m);
		void deinit();

		bool operator< (const ModelRenderPass &m) const
		{
			// This is the old sort order method which I'm pretty sure is wrong - need to try something else.
			// Althogh transparent part should be displayed later, but don't know how to sort it
			// And it will sort by geoset id now.
			return geoset < m.geoset;
		}
	};

	struct AGMD_EXPORT SPosition
	{
		SPosition(vec3 _position = vec3(0.0f), mat4 _rotation = mat4(1.0f)) :
		m_position(_position),
		m_rotation(_rotation)
		{}



		mat4 ModelMatrix() const { return translate(m_rotation,m_position); }

		vec3 m_position;
		mat4 m_rotation;
	};

	typedef SPosition* SPositionPtr;
	typedef std::vector<ModelRenderPass> MRPvector;

    class AGMD_EXPORT Model : public Resource
    {
    public :
        struct TVertex
        {
            vec3     position;
            vec3     normal;
            uint32   color;
            vec2     texCoords;
			vec4	 tangent;
			vec4     boneWeight;
			vec4     boneIndices;
			float    boneCount;
        };

		struct Joint
		{
			std::string     m_Name;
			int32           m_ParentID;
			vec3			m_Pos;
			quat			m_Orient;
		};
		
		typedef std::vector<Joint> JointVector;
		typedef std::vector<mat4> Mat4Vector;
        typedef unsigned short TIndex;

        Model(TVertex* vertices, unsigned long verticesCount, TIndex* indices, unsigned long indicesCount, ModelRenderPass* renderpass = NULL, uint32 passCount = 1, TPrimitiveType type = PT_TRIANGLELIST);

        virtual void Render() const;

		void Rotate(float angle, vec3 vector);
		void SetRotation(mat4 mat);
		
		void Move(vec3 move);
		void Move(float move_x, float move_y, float move_z);

		void MoveTo(vec3 pos);
		void MoveTo(float pos_x, float pos_y, float pos_z);

		vec3 getTranslate() {return m_position.m_position;}
		mat4 getRotate() {return m_position.m_rotation;}

		SPositionPtr getPosition() { return &m_position;}

		void SetTextureUnit(Texture tex, uint32 unit, uint32 renderpass = 0);
		void DisableTextureUnit(uint32 unit, uint32 renderpass = 0); 


    protected:

		Model();

		void Generate(GenerateType type, TVertex* vertices, unsigned long verticesCount, TIndex* indices, unsigned long indicesCount);

        DeclarationPtr  m_Declaration;
        Buffer<TVertex> m_VertexBuffer;
        Buffer<TIndex>  m_IndexBuffer;
		MRPvector       m_RenderPass;
        //TextureUnit m_Textures[MAX_TEXTUREUNIT];
		SPosition		m_position;
		TPrimitiveType  m_PrimitiveType;
		JointVector     m_vJoints;
		Mat4Vector		m_vmBindPose;
		Mat4Vector		m_vmInversedBindPose;
		bool			m_bHasBone;
    };

    typedef SmartPtr<Model, ResourceCOM> TModelPtr;

}


#endif // MODEL_H