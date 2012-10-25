#ifndef PLAYER_H
#define PLAYER_H



#include <AgmdDefines.h>

using namespace Agmd;

class Player
{
public:




	void SetPosition(vec3 pos);
	void SetPosition(float x, float y, float z);
	vec3 GetPosition();


private:

	float m_fRotation;
	float m_fRotationSpeed;

	vec3 m_vPosition;
	vec3 m_vSpeed;
	

	Model* m_mModel;
	Camera* m_cCam;

};



#endif //PLAYER_H