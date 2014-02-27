__kernel void _mat4prod(__global float * m1,__global float * m2,__global float *r)
{
	int i = get_global_id(0);
	int j = get_global_id(1);
	
	int k;
	float _value = 0;
	for(k = 0; k < 4; k++)
		_value += m1[i+4*k]*m2[k+j*4];
		
	r[i+j*4] = _value;		
}
