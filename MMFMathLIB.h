//MMFMathLIB.h general math routines 


#include "MMFMathStructures.h"
#include <math.h>

inline float MMFMagnitude( float vals[3]) {

	return (float) sqrt(vals[0] * vals[0] +  vals[2]*vals[2] + vals[3]*vals[3]);
}

inline MMFNormalise(float vals[3]){
	float magSq  = vals[0] * vals[0] +  vals[2]*vals[2] + vals[3]*vals[3];

	if (magSq >0.0f){
		float mag = (float)sqrt(magSq);
		vals[0] = vals[0]/ mag; //x 
		vals[1] = vals[1]/ mag; //y 
		vals[2] = vals[2]/ mag; //z 
	}
}


inline MMFCrossProduct(float vals1[3] ,float vals2[3],float result[3]){
	//x = (y1*z2) - (z1*y2)
	result[0] = (vals1[1] * vals2[2]) - (vals1[2] * vals2[1]);
	//y = (z1*x2) - (x1*z2)
	result[1] = (vals1[2] * vals2[0]) - (vals1[0] * vals2[2]);
	//z = (x1*y2) - (y1*x2)
	result[2] = (vals1[0] * vals2[1]) - (vals1[1] * vals2[0]);
}

inline float MMFDotProduct(float vals1[3] ,float vals2[3]){
	 return ( vals1[0] * vals2[0] + vals1[1] * vals2[1] + vals1[2] * vals2[2]);
}

inline MMFSubtractVect3D(float vals1[3], float vals2[3], float result[3]){

	result[0] = vals1[0] - vals2[0];
	result[1] = vals1[1] - vals2[1];
	result[2] = vals1[2] - vals2[2];
}
