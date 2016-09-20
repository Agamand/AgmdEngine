#include "PlanetTreeNode.h"
#include "Planet.h"
#include <Core/Model/Material.h>
#include <Core/Driver.h>
#include <Core/Tools/Fast2DSurface.h>
#include <Core/Tools/BoundingBox.h>

ivec2 order[] =
{
    ivec2(1, 1),
    ivec2(1, -1),
    ivec2(-1, 1),
    ivec2(-1, -1)
};

quat getRotationFor(int divisor, int face)
{
    return quat(glm::rotate(mat4(1), order[face].x * 45.f, vec3(1, 0, 0)));
}

vec3 getTranslation(int divisor, int face)
{
    return vec3(order[face].x * 0.25f, order[face].y * 0.25f, 0);
}

PlanetTreeNode::PlanetTreeNode(PlanetModel* model, Planet* controller, int face, const mat4& matrix /*= mat4(1)*/, Transform* transform /*= NULL*/, int lod /*= 0*/) :
    MeshNode(model, transform), m_lod(lod), m_controller(controller), m_positionMatrix(matrix),
    m_face(face), m_textureInit(false), m_needGenerate(false)
{
    if (m_controller->m_material)
        m_material = m_controller->m_material;


    std::memset(m_faces, 0, sizeof(m_faces));
    m_divisor = 1;
    for (int i = 0; i < lod; i++)
        m_divisor *= 2;

    vec4 points[] = {vec4(-0.5f, -0.5f, 0, 1),vec4(0.5f, -0.5f, 0, 1),vec4(-0.5f, 0.5f, 0, 1),vec4(0.5f, 0.5f, 0, 1)};

    for (a_uint8 i = 0; i < 4; i++)
    {
        points[i] = m_positionMatrix * points[i];
        points[i] = vec4(normalize(vec3(points[i])), 1);
    }

    vec3 _min, _max = _min = vec3(points[0]);
    _min.x = min(_min.x,points[0].x*(1+0.1f));
    _min.y = min(_min.y,points[0].y*(1+0.1f));
    _min.z = min(_min.z,points[0].z*(1+0.1f));
    _max.x = max(_max.x,points[0].x*(1+0.1f));
    _max.y = max(_max.y,points[0].y*(1+0.1f));
    _max.z = max(_max.z,points[0].z*(1+0.1f));

    for (a_uint8 i = 1; i < 4; i++)
    {
        _min.x = min(_min.x,points[i].x);
        _min.y = min(_min.y,points[i].y);
        _min.z = min(_min.z,points[i].z);
        _max.x = max(_max.x,points[i].x);
        _max.y = max(_max.y,points[i].y);
        _max.z = max(_max.z,points[i].z);

        _min.x = min(_min.x,points[i].x*(1+0.1f));
        _min.y = min(_min.y,points[i].y*(1+0.1f));
        _min.z = min(_min.z,points[i].z*(1+0.1f));
        _max.x = max(_max.x,points[i].x*(1+0.1f));
        _max.y = max(_max.y,points[i].y*(1+0.1f));
        _max.z = max(_max.z,points[i].z*(1+0.1f));
    }
    m_baseBounds = BoundingSphere(_min, _max);
    update(NULL, false, true);
}


PlanetTreeNode::~PlanetTreeNode()
{
    for (a_uint8 i = 0; i < MAX_FACE; i++)
        if (m_faces[i])
            delete m_faces[i];
}


void PlanetTreeNode::findVisible(Camera* cam, RenderQueue& display,a_vector<LightNode*>& light)
{
    if (!cam->isInFrustrum(m_globalBounds))
        return;
    float trigger = CONST_DISTANCE * 2 * m_controller->m_size / m_divisor;
    vec4 point(0, 0, 0, 1);
    mat4 view = cam->getView();
    point = m_positionMatrix * point;
    vec3 real_point = normalize(vec3(point));
    vec4 points[] = {vec4(0, 0, 0, 1),vec4(-0.5f, -0.5f, 0, 1),vec4(0.5f, -0.5f, 0, 1),vec4(-0.5f, 0.5f, 0, 1),vec4(0.5f, 0.5f, 0, 1)};
    point = m_positionMatrix * point;
    float distance = -1;
    bool isVisible = true;
    vec3 camDirection = vec3(0, 0, 1);
    for (a_uint8 i = 0; i < 5; i++)
    {
        points[i] = m_positionMatrix * points[i];
        vec3 real_point = normalize(vec3(points[i]));
        if (!isVisible)
        {
            vec3 normal = mat3(view * m_transform->modelMatrix()) * real_point;
            float product = dot(camDirection, normal);
            isVisible = product > 0;
        }


        points[i] = view * m_transform->modelMatrix() * vec4(real_point, 1.0f);

        float len = length(vec3(points[i]));
        if (len < distance || distance < 0.0f)
            distance = len;
    }
    float trigger2 = 0;//length(points[0]-points[1]);
    if (!isVisible)
        return;

    if (m_lod >= MAX_LOD)
    {
        if (!m_textureInit || m_needGenerate)
            generateTexture();
        DisplayNode::findVisible(cam, display, light);
        return;
    }

    float offset = distance;
    trigger = trigger > trigger2 ? trigger : trigger2;
    if (offset > trigger)
    {
        if (!m_textureInit || m_needGenerate)
            generateTexture();
        DisplayNode::findVisible(cam, display, light);
        for (int i = 0; i < MAX_FACE; i++)
        {
            if (m_faces[i])
                delete m_faces[i];
            m_faces[i] = NULL;
        }
    }
    else
    {
        bool first_init = false;
        for (a_uint8 i = 0; i < MAX_FACE; i++)
        {
            if (!m_faces[i])
            {
                first_init = true;
                Transform* t = new Transform();
                t->update(m_transform);
                m_faces[i] = new PlanetTreeNode(m_controller->m_model, m_controller, m_face, m_positionMatrix * translate(mat4(1.0f), getTranslation(m_divisor, i)) * scale(mat4(1), vec3(0.5f)), t, m_lod + 1);
                m_faces[i]->update(m_transform, false, true);
            }
            if (!first_init)
                m_faces[i]->findVisible(cam, display, light);
            else
            {
                if (!m_textureInit || m_needGenerate)
                    generateTexture();
                DisplayNode::findVisible(cam, display, light);
            }
        }
    }
}


#define OUTER_INNER_OFFSET 1.025f

void PlanetTreeNode::render(TRenderPass pass) const
{
    //HACK FOR TEST

    //PlanetTreeNode* node = const_cast<PlanetTreeNode*>(this);
    //node->generateTexture();


    if (!m_material || !m_material->Enable(pass))
        return;
    PlanetModel* model = m_controller->m_model;
    Driver& driver = Driver::Get();
    float outer = m_controller->m_size * OUTER_INNER_OFFSET, inner = m_controller->m_size;
    m_material->setParameter("u_divisor", (float)m_divisor);
    m_material->setParameter("u_offset", (float)m_controller->m_model->m_offset);
    m_material->setParameter("u_position_matrix", m_positionMatrix);
    m_material->setParameter("u_face", m_face);
    m_material->setParameter("u_normal_mapping", m_controller->m_model->m_normal_mapping);
    m_material->setParameter("v3LightPos", m_controller->lightDir);
    m_material->setParameter("u_use_atmosphere", m_controller->m_use_atmosphere ? 1 : 0);
    m_material->setParameter("v3CameraPos", m_controller->m_cam_position);
    m_material->setParameter("u_octave", (int)model->m_octave);
    m_material->setParameter("u_frequency", model->m_frequency);
    m_material->setParameter("u_amplitude", model->m_amplitude);
    m_material->setParameter("u_lacunarity", model->m_lacunarity);

    //m_material->setParameter("u_octave",(int)model->m_octave);
    if (m_controller->m_use_atmosphere)
    {
        m_material->setParameter("v3InvWavelength", vec3(1.0 / pow(model->rgb.r, 4.0f), 1.0 / pow(model->rgb.g, 4.0f), 1.0 / pow(model->rgb.b, 4.0f)));

        m_material->setParameter("fCameraHeight", length(m_controller->m_cam_position));
        m_material->setParameter("fCameraHeight2", length(m_controller->m_cam_position) * length(m_controller->m_cam_position));

        m_material->setParameter("fInnerRadius", inner);
        m_material->setParameter("fInnerRadius2", inner * inner);
        m_material->setParameter("fOuterRadius", outer);
        m_material->setParameter("fOuterRadius2", outer * outer);
        m_material->setParameter("fKrESun", model->kr * model->eSun);
        m_material->setParameter("fKmESun", model->km * model->eSun);
        m_material->setParameter("fKr4PI", model->kr * 4.0f * 3.141592653f);
        m_material->setParameter("fKm4PI", model->km * 4.0f * 3.141592653f);
        m_material->setParameter("fScale", 1.0f / (outer - inner));
        m_material->setParameter("fScaleDepth", 0.25f);
        m_material->setParameter("fScaleOverScaleDepth", 4.0f / (outer - inner));
        m_material->setParameter("g", model->g);
        m_material->setParameter("g2", model->g * model->g);
        m_material->setParameter("isInAtmosphere", (m_controller->m_cam_dist > m_controller->m_size * OUTER_INNER_OFFSET) ? 0 : 1);
    }
    driver.SetTexture(0, m_heightTexture.GetTexture());
    //driver.SetTexture(2,m_normalTexture.GetTexture());
    draw();
    m_material->Disable();
}

bool PlanetTreeNode::update(Transform* transform, bool updateChildren, bool transformChanged)
{
    float trigger = 4 * m_controller->m_size / m_divisor / 2;
    bool transformUpdate = DisplayNode::update(transform, updateChildren, transformChanged);
    for (int i = 0; i < MAX_FACE; i++)
    {
        if (m_faces[i])
            m_faces[i]->update(m_transform, updateChildren, transformUpdate);
    }
    return transformUpdate;

    /*vec4 point(0,0,0,1); //center
    vec4 points[] = {vec4(0,0,0,1),vec4(-0.5f,-0.5f,0,1),vec4(0.5f,-0.5f,0,1),vec4(-0.5f,0.5f,0,1),vec4(0.5f,0.5f,0,1)};
    mat4 view = Camera::GetCurrent(CAMERA_3D)->GetView();
    point = m_positionMatrix*point;
    float distance = trigger+1;;
    for(a_uint8 i = 0; i < 5; i++)
    {
        points[i] = m_positionMatrix*points[i];
        vec3 real_point = normalize(vec3(points[i]));
        points[i] = view*m_transform->ModelMatrix()*vec4(real_point,1.0f);
        float len = length(vec3(points[i]));
        if(len < distance)
            distance = len;
    }
    float tr2 = length(points[0]-points[1]);
    if(m_lod >= MAX_LOD)
        return;
    
    float offset = distance;
    //trigger = trigger > tr2 ? trigger :  tr2;
    if(offset <= trigger || true)
        for(int i = 0; i < MAX_FACE; i++)
        {
            if(m_faces[i])
                m_faces[i]->Update(m_transform,updateChildren);
        }*/
}

#define TEX_SIZE 256

void PlanetTreeNode::generateTexture()
{
    return;
    if (!m_textureInit)
    {
        m_heightTexture.Create(ivec2(TEX_SIZE), PXF_A8R8G8B8, TEXTURE_2D, TEX_WRAP_CLAMP | TEX_USE_FILTER);
        m_normalTexture.Create(ivec2(TEX_SIZE), PXF_A8R8G8B8, TEXTURE_2D, TEX_WRAP_CLAMP | TEX_USE_FILTER);
    }
    m_controller->m_model->generateTexture(m_heightTexture, m_normalTexture, m_positionMatrix);
    m_textureInit = true;
    m_needGenerate = false;
}
