//MMFMathStructures.h

#ifndef MMFMATHSTRUCTURES_H
#define MMFMATHSTRUCTURES_H
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct MMFPoint3Di{
	int m_vals[3];
};

struct MMFVertice3Df{
	float m_vals[3];
};

struct MMFVector3Di{
	int m_vals[3];
};

struct MMFVector3Df{
	float m_vals[3];
	MMFVector3Df(){
		m_vals[0] = 0;
		m_vals[1] = 0;
		m_vals[2] = 0;
	}


};

struct MMFPoly3i{
	int a,b,c,matID;

	MMFPoly3i(){
    matID = 0;
	}

};

struct MMFTextCoords2f{

	float u, v;
};

struct MMFColour3Uc{
	unsigned char r, g, b;
};


#endif// define MMFMATHSTRUCTURES_H