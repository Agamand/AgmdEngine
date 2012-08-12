#ifndef MODEL_H
#define MODEL_H

#include <Config/Fwd.h>
#include <Core/Resource.h>
#include <Core/Buffer.h>
#include <Core/Declaration.h>
#include <Core/Texture.h>
#include <Core/Enums.h>
#include <Utilities/SmartPtr.h>
#include <Maths/Vector2.h>
#include <Maths/Vector3.h>


namespace Agmd
{

	enum GenerateType
	{
		G_NONE = 0x0,
		G_NORMAL = 0x1,
		G_TANGENT = 0x2,
		G_ALL = G_NORMAL | G_TANGENT
	};

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
        };
        typedef unsigned short TIndex;

        Model(TVertex* vertices, unsigned long verticesCount, TIndex* indices, unsigned long indicesCount, const std::string& texture, TPrimitiveType type = PT_TRIANGLELIST);

        virtual void Render() const;

		void Rotate(float angle, vec3 vector);
		void SetRotation(mat4 mat);
		
		void Move(vec3 move);
		void Move(float move_x, float move_y, float move_z);

		void MoveTo(vec3 pos);
		void MoveTo(float pos_x, float pos_y, float pos_z);

		mat4 getTranslate() {return m_pos;}
		mat4 getRotate() {return m_rot;}


    protected:

		Model();

		void Generate(GenerateType type, TVertex* vertices, unsigned long verticesCount, TIndex* indices, unsigned long indicesCount);

        DeclarationPtr  m_Declaration;
        Buffer<TVertex> m_VertexBuffer;
        Buffer<TIndex>  m_IndexBuffer;
        Texture         m_Texture;
		mat4			m_pos;
		mat4			m_rot;
		TPrimitiveType m_PrimitiveType;
    };

    typedef SmartPtr<Model, ResourceCOM> TModelPtr;

}


#endif // MODEL_H