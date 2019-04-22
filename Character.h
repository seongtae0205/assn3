#pragma once
#include "Object.h"

#define GLM_ENABLE_EXPERIMENTAL
#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <math.h>
#include "Object.h"
#include "glm/glm.hpp"

using namespace glm;
using namespace std;

extern GLint vertexLocation;
extern GLint ctmLocation;

extern GLuint verticesVBO;
extern GLuint indiciesVBO;

extern glm::mat4 ctm;


class Character : public Object
{
private:
	bool isAuto;


protected:
	virtual void drawShader(glm::mat4 projectionMatrix, glm::mat4 modelViewMatrix);
	virtual void moveObject();

public:
	Character() { 
		setOriginalMatrix(
			glm::scale(glm::vec3(1/1000.f, 1/1000.f, 1/1000.f)));
	}
	Character(glm::vec3 position, bool isAuto = true) : Object(position, "Chiko"), isAuto(isAuto)
	{
		setOriginalMatrix(
			glm::scale(glm::vec3(1 / 1000.f, 1 / 1000.f, 1 / 1000.f)));

		if (isAuto) {
			setOriginalMatrix(glm::translate(glm::mat4(1.f), position)
				* glm::rotate((float)M_PI_2, glm::vec3(1.f, 0.f, 0.f))
				* getOriginalMatrix());
		}
		else {
			setOriginalMatrix(glm::translate(glm::mat4(1.f),position)
				* glm::rotate((float)M_PI_2, glm::vec3(1.f, 0.f, 0.f))
				* glm::rotate((float)M_PI, glm::vec3(0.f, 1.f, 0.f))
				* getOriginalMatrix());
		}

	}
	void pressed(unsigned char key);
	virtual ~Character() {}
};

