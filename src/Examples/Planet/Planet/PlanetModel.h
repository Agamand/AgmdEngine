#ifndef _PLANETMODEL_H_
#define _PLANETMODEL_H_

#include <Core/SceneObject/Model.h>
#include <Core/Texture/Texture.h>
#include <Core/Shader/ShaderProgram.h>

using namespace Agmd;




class PlanetModel :public Model
{
public:
	PlanetModel(int layer, int x, int y);
	PlanetModel(mat4 matrix);
	static void CreateFaceMetaSphere(a_vector<Model::TVertex>& vertices, a_vector<Model::TIndex>& indices,int layer,mat4 matrix = mat4(1));
	static void CreatePlane(int size, int offset_index, a_vector<Model::TVertex>& vertices, a_vector<Model::TIndex>& index,mat4 matrix);
	void generateTexture(Texture& height, Texture& normal, mat4& postion_matrix);
	void initNoise();
	float m_persistance;
	float m_octave;
	float m_frequency;
	int m_normal_mapping;
private:
	Texture m_noiseTable;
	
	ShaderProgram m_ground_program;
};

#endif /* _PLANETMODEL_H_ */