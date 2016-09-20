#include "PlanetAtmosphereNode.h"

#include <Core/Model/GeometryFactory.h>
#include <Core/Driver.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Planet.h"

PlanetAtmosphereNode::PlanetAtmosphereNode(Planet* controller) : MeshNode(GeometryFactory::createSphere(1, 50, 50, (float)M_PI * 2)), m_controller(controller)
{
    m_groundProgram[0].LoadFromFile("shader/planet/ground_from_space.glsl");
    m_groundProgram[1].LoadFromFile("shader/planet/ground_from_atmo.glsl");
    m_skyProgram[0].LoadFromFile("shader/planet/sky_from_space.glsl");
    m_skyProgram[1].LoadFromFile("shader/planet/sky_from_atmo.glsl");
}

#define OUTER_INNER_OFFSET 1.025f

void PlanetAtmosphereNode::render(TRenderPass pass) const
{
    Driver& driver = Driver::Get();
    int use;
    PlanetModel* model = m_controller->m_model;
    driver.SetCullFace(1);
    driver.Enable(TRenderParameter::RENDER_ALPHABLEND, true);
    if (m_controller->m_cam_dist > m_controller->m_size * OUTER_INNER_OFFSET)
    {
        driver.Enable(TRenderParameter::RENDER_ZWRITE, false);
        driver.SetupAlphaBlending(BLEND_SRCALPHA, BLEND_INVSRCALPHA);
        use = 0;
    }
    else use = 1;


    float outer = m_controller->m_size * OUTER_INNER_OFFSET, inner = m_controller->m_size;
    driver.SetCurrentProgram(m_skyProgram[use].GetShaderProgram());
    m_skyProgram[use].SetParameter("v3CameraPos", m_controller->m_cam_position);
    m_skyProgram[use].SetParameter("v3LightPos", m_controller->lightDir);
    m_skyProgram[use].SetParameter("v3InvWavelength", vec3(1.0 / pow(model->rgb.r, 4.0f), 1.0 / pow(model->rgb.g, 4.0f), 1.0 / pow(model->rgb.b, 4.0f)));

    m_skyProgram[use].SetParameter("fCameraHeight", length(m_controller->m_cam_position));
    m_skyProgram[use].SetParameter("fCameraHeight2", length(m_controller->m_cam_position) * length(m_controller->m_cam_position));

    m_skyProgram[use].SetParameter("fInnerRadius", inner);
    m_skyProgram[use].SetParameter("fInnerRadius2", inner * inner);
    m_skyProgram[use].SetParameter("fOuterRadius", outer);
    m_skyProgram[use].SetParameter("fOuterRadius2", outer * outer);
    m_skyProgram[use].SetParameter("fKrESun", model->kr * model->eSun);
    m_skyProgram[use].SetParameter("fKmESun", model->km * model->eSun);
    m_skyProgram[use].SetParameter("fKr4PI", model->kr * 4.0f * 3.141592653f);
    m_skyProgram[use].SetParameter("fKm4PI", model->km * 4.0f * 3.141592653f);
    m_skyProgram[use].SetParameter("fScale", 1.0f / (outer - inner));
    m_skyProgram[use].SetParameter("fScaleDepth", 0.25f);
    m_skyProgram[use].SetParameter("fScaleOverScaleDepth", 4.0f / (outer - inner));
    m_skyProgram[use].SetParameter("g", model->g);
    m_skyProgram[use].SetParameter("g2", model->g * model->g);
    draw();
    driver.SetCullFace(2);/*
    driver.Enable(TRenderParameter::RENDER_ZWRITE,false);
    driver.Enable(TRenderParameter::RENDER_ALPHABLEND,true);
    driver.Enable(TRenderParameter::RENDER_ZTEST,true);
    driver.SetupAlphaBlending(BLEND_ONE, BLEND_SRCCOLOR);
    driver.SetCurrentProgram(m_groundProgram[use].GetShaderProgram());
    m_groundProgram[use].SetParameter("v3CameraPos",m_controller->m_cam_position);
    m_groundProgram[use].SetParameter("v3LightPos",m_controller->lightDir);
    m_groundProgram[use].SetParameter("v3InvWavelength",vec3(1.0 / pow(model->rgb.r, 4.0f), 1.0 / pow(model->rgb.g, 4.0f), 1.0 / pow(model->rgb.b, 4.0f)));

    m_groundProgram[use].SetParameter("fCameraHeight",length(m_controller->m_cam_position));
    m_groundProgram[use].SetParameter("fCameraHeight2",length(m_controller->m_cam_position)*length(m_controller->m_cam_position));

    m_groundProgram[use].SetParameter("fInnerRadius",inner);
    m_groundProgram[use].SetParameter("fInnerRadius2",inner*inner);
    m_groundProgram[use].SetParameter("fOuterRadius",outer);
    m_groundProgram[use].SetParameter("fOuterRadius2",outer*outer);
    m_groundProgram[use].SetParameter("fKrESun", model->kr * model->eSun);
    m_groundProgram[use].SetParameter("fKmESun", model->km * model->eSun);
    m_groundProgram[use].SetParameter("fKr4PI",model->kr * 4.0f * 3.141592653f);
    m_groundProgram[use].SetParameter("fKm4PI",model->km * 4.0f * 3.141592653f);
    m_groundProgram[use].SetParameter("fScale", 1.0f / (outer - inner));
    m_groundProgram[use].SetParameter("fScaleDepth",0.25f);
    m_groundProgram[use].SetParameter("fScaleOverScaleDepth", 4.0f / (outer - inner));
    m_groundProgram[use].SetParameter("g",model->g);
    m_groundProgram[use].SetParameter("g2",model->g*model->g);
    draw();*/
    driver.SetCurrentProgram(NULL);
    driver.Enable(TRenderParameter::RENDER_ALPHABLEND, false);
    driver.Enable(TRenderParameter::RENDER_ZWRITE, true);
    driver.Enable(TRenderParameter::RENDER_ZTEST, true);
}

void PlanetAtmosphereNode::findVisible(Camera* cam, RenderQueue& display, a_vector<LightNode*>& light)
{
    if (!m_controller->m_use_atmosphere || !cam->isInFrustrum(m_globalBounds))
        return;

    PlanetModel* model = m_controller->m_model;
    //    m_controller->m_cam_position = cam->getPosition();

    vec4 my(0, 0, 0, 1);
    my = m_transform->modelMatrix() * my;
    m_controller->m_cam_position = m_controller->m_cam_position - vec3(my);
    m_controller->m_cam_dist = length(m_controller->m_cam_position);
    display.push_back(this, TRenderType::TYPE_BLEND);

    SceneNode::findVisible(cam, display, light);
}
