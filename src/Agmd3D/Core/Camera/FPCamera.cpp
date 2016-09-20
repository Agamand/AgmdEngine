// /*
// ============================================================================
// Agmd3D - 3D Engine
// Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
// https://github.com/Agamand/AgmdEngine
// ============================================================================
// */
// 
// #define _USE_MATH_DEFINES
// #include <Core\Camera\FPCamera.h>
// #include <math.h>
// #include <glm/gtc/quaternion.hpp>
// #include <glm/gtx/quaternion.hpp>
// 
// namespace Agmd
// {
//     FPCamera::FPCamera(mat4& projection, vec3& pos) :
//     _phi(0),
//     _theta(0),
//     Camera(projection,pos)
//     {
//         updateVector();
//         m_rotation = quat();
//     }
// 
//     FPCamera::~FPCamera()
//     {}
// 
//     void FPCamera::updateVector()
//     {
//         
//         
//         if (_phi > 89)
//             _phi = 89;
//         else if (_phi < -89)
//             _phi = -89;
//         float r_temp = cos(_phi*((float)M_PI)/180);
//             
//         vec3 _up = vec3(sin(_phi*M_PI/180)*cos(_theta*M_PI/180),r_temp,sin(_phi*M_PI/180)*sin(_theta*M_PI/180));
//         _forward =  glm::vec3(r_temp*cos(_theta*M_PI/180),sin(_phi*M_PI/180),r_temp*sin(_theta*M_PI/180));
//         _left = glm::cross(_up,_forward);
//         glm::normalize(_left);
// 
//        _target = _position + _forward;
//        move = vec3(0.0f);
// 
//        if(moveFlags & MOVE_FORWARD)
//            move += _forward;
// 
//        if(moveFlags & MOVE_BACK)
//            move -= _forward;
// 
//        if(moveFlags & MOVE_LEFT)
//            move += _left;
// 
//        if(moveFlags & MOVE_RIGHT)
//            move -= _left;
// 
//        if(moveFlags & MOVE_UP)
//            move += vec3(0.0f,0.0f,1.0f);
// 
//        if(moveFlags & MOVE_DOWN)
//            move -= vec3(0.0f,0.0f,1.0f);
//     }
//     void FPCamera::onMouseMotion(int x, int y)
//     {
//         _theta += x*m_sensivity;
//         _phi += y*m_sensivity;
// 
//         //m_view = m_view*toMat4(rot);
//         updateVector();
//     }
// 
//     void FPCamera::onKeyboard( a_char key, bool up )
//     {
//         a_uint32 tempFlags = MOVE_NONE;
//         switch(key)
//         {
//         case 'Z':
//             tempFlags = MOVE_FORWARD;
//             break;
//         case 'S':
//             tempFlags = MOVE_BACK;
//             break;
//         case 'Q':
//             tempFlags = MOVE_LEFT;
//             break;
//         case 'D':
//             tempFlags = MOVE_RIGHT;
//             break;
//         case 'E':
//             //tempFlags = MOVE_UP;
//             break;
//         case 'A':
//             //tempFlags = MOVE_DOWN;
//             break;
//         }
// 
//         if(!up)
//             moveFlags |= tempFlags;
//         else moveFlags &= ~tempFlags;
//         updateVector();
//     }
// 
//     void FPCamera::onMouseWheel(float delta)
//     {
// 
//     }
//     
// 
//     void FPCamera::onUpdate(a_uint64 time_diff)
//     {
//         _position += move*(m_speed*time_diff)/1000.0f;
//         _target = _position + _forward;
//         //m_view *=m_view *translate(mat4(), move*(m_speed*time_diff)/1000.0f);
//         updateBuffer(look());
//     }
// 
//     mat4 FPCamera::look()
//     {
//         //m_view = m_view*Camera::look();
//         return Camera::look();
//     }
// 
// }
