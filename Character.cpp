#include "Character.h"


glm::vec3 Character::translateVector(glm::vec3 direction) {
	GLfloat x = finalPositions[0].x;
	GLfloat y = finalPositions[0].y;
	glm::vec3 translate = glm::rotate(glm::mat4(1.f), glm::radians(angle), glm::vec3(0.f, 0.f, 1.f)) * glm::vec4(direction, 1.f);
	translate.x = glm::clamp(x + translate.x, -1.f, 1.f) - x;
	translate.y = glm::clamp(y + translate.y, -1.f, 0.f) - y;
	return translate;
}

void Character::pressed(unsigned char key)
{
	GLfloat x = finalPositions[0].x;
	GLfloat y = finalPositions[0].y;
	if (!isAuto) {
		switch (key)
		{
		case 'W':
		case 'w':
			translateOrigin(translateVector(glm::vec3(0.f, 0.01f, 0.f)));
			break;
		case 'A':
		case 'a':
			translateOrigin(-x, -y);
			angle += diffAngle;
			rotateOrigin(glm::radians(diffAngle), glm::vec3(0.f, 0.f, 1.f));
			translateOrigin(x, y);
			break;
		case 'S':
		case 's':
			translateOrigin(translateVector(glm::vec3(0.f, -0.01f, 0.f)));
			break;
		case 'D':
		case 'd':
			translateOrigin(-x, -y);
			angle -= diffAngle;
			rotateOrigin(glm::radians(-diffAngle), glm::vec3(0.f, 0.f, 1.f));
			translateOrigin(x, y);
			break;
		}
	}
}

void Character::drawShader(glm::mat4 projectionMatrix, glm::mat4 modelViewMatrix) {
	ctm = projectionMatrix * modelViewMatrix;
	glBindVertexArray(VAO);
	glUniformMatrix4fv(ctmLocation, 1, GL_FALSE, &ctm[0][0]);

	if (isLineRemoval) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glUniform4f(colorLocation, backgroundColor[0], backgroundColor[1], backgroundColor[2], backgroundColor[3]);
		//glDrawArrays(GL_TRIANGLES, 0, getVertexCount());

		glDrawElements(GL_TRIANGLES, getIndexCount(), GL_UNSIGNED_INT, 0);

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glUniform4f(colorLocation, modelColor[0], modelColor[1], modelColor[2], modelColor[3]);
		//glDrawArrays(GL_TRIANGLES, 0, getVertexCount());

		glDrawElements(GL_TRIANGLES, getIndexCount(), GL_UNSIGNED_INT, 0);

	}
	else {
		//glDrawArrays(GL_TRIANGLES, 0, getVertexCount());
		glDrawElements(GL_TRIANGLES, getIndexCount(), GL_UNSIGNED_INT, 0);
	}

	glBindVertexArray(0);


}


void Character::moveObject()
{

}