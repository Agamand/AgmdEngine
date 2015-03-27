#ifndef _PLANETMODEL_H_
#define _PLANETMODEL_H_

#include <Core/Model/Model.h>
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
    void generateTexture(const Texture& height, const Texture& normal, const mat4& postion_matrix);
    void generateTexture(const Texture& diffuse,const Texture& heightmap, const Texture& gradient);
    void initNoise();
    float m_persistance;
    float m_octave;
    float m_frequency;
    float m_amplitude;
    float m_lacunarity;
    int m_normal_mapping;
    float kr;
    float eSun;
    float km;
    float g;
    float m_offset;
    vec3 rgb;
private:
    Texture m_noiseTable;
    
    ShaderProgram m_ground_program;
    ShaderProgram m_diffuse_program;
    

};

#endif /* _PLANETMODEL_H_ */