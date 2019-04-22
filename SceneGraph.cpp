#include "SceneGraph.h"


Sphere ball(0.2f, 2);
Background background(4, 8, 4);

void SceneGraph::init() {
    root = new Object();

	vertexLocation = glGetAttribLocation(myProgramObj, "vPosition");
	ctmLocation = glGetUniformLocation(myProgramObj, "ctm");

    // add 순서 중요 collision check 순서에 영향 - 순서는 reverse 순이다.
	root->addChild(&ball);
	root->addChild(&background);

	//Init Buffer
	glGenBuffers(1, &verticesVBO);
	glBindBuffer(GL_ARRAY_BUFFER, verticesVBO);
	glBufferData(GL_ARRAY_BUFFER, this->getRoot()->totalVerticesSize(), NULL, GL_STATIC_DRAW);

	glGenBuffers(1, &indiciesVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indiciesVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->getRoot()->totalIndicesSize(), NULL, GL_STATIC_DRAW);

	unsigned vertexOffset = 0;
	unsigned indexOffset = 0;
	root->init(&vertexOffset, &indexOffset);
}

void SceneGraph::KeyboardFunc(unsigned char key, int x, int y)
{

}

void SceneGraph::DisplayFunc()
{
    root->draw(projectionMatrix, modelViewMatrix);
}

void SceneGraph::IdleFunc()
{
	root->move();
}
