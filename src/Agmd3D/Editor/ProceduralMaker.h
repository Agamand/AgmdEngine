#ifndef _PROCEDURALMAKER_H_
#define _PROCEDURALMAKER_H_

#include <Utilities/Singleton.h>
#include <Core/Model/Model.h>
enum ObjectType
{
	MODEL_CUBE,
	MODEL_SPHERE,
	MODEL_ICOSAHEDRE
};

enum StepCube
{
	CUBE_X = 1,
	CUBE_Y,
	CUBE_Z
};


enum StepIcoshedre
{
	 ICOSAHEDRE_RADIUS=1,
};

class ProceduralMaker
{
public:
	ProceduralMaker();



	void nextStep();

	void OnClick(int click, vec2 pos, bool up);
	void OnMove(vec2 pos);
	void OnKey(a_char key,bool up);

private:
	a_uint32 m_currentSteps;
	a_uint32 m_currentProcedure;
};









#endif /* _PROCEDURALMAKER_H_ */