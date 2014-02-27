vec3 getColor(float a)
{
	float PI = 3.14159265359;
	return vec3(clamp(cos(4*PI/3*a-4/3*PI),0,1),clamp(cos(4*PI/3*a-2*PI/3),0,1),clamp(cos(4*PI/3*a),0,1));
}