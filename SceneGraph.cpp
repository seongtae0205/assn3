#include "SceneGraph.h"

vector<Object*> allNodes = vector<Object*>();

ScoreBox userScore = ScoreBox(- 0.9f, 0.9f);
ScoreBox comScore  = ScoreBox(0.9f, 0.9f);
void addGameScore(bool addUserScore);
Sphere ball(0.2f, 2, addGameScore);

void addGameScore(bool addUserScore) {
    if (addUserScore) {
        userScore.addScore();
    } else {
        comScore.addScore();
    }
    ball.resetPosition();
}


Background background(WIDTH, DEPTH, HEIGHT);
Character player = Character(glm::vec3(0.f, -DEPTH * 0.35f, 0.f), false);
Character com = Character(glm::vec3(0.f, DEPTH * 0.35f, 0.f), true);

void SceneGraph::init() {
    root = new Object();

	player.loadOBJ("resource/Chikorita_OBJ.obj");
	com.loadOBJ("resource/Chikorita_OBJ.obj");

	vertexLocation = glGetAttribLocation(myProgramObj, "vPosition");
	ctmLocation = glGetUniformLocation(myProgramObj, "ctm");
	colorLocation = glGetUniformLocation(myProgramObj, "vColor");
    // add 순서 중요 collision check 순서에 영향 - 순서는 reverse 순이다.

	//순서를 바꾸면 이상해짐
	root->addChild(&background);
	root->addChild(&com);
	root->addChild(&player);
	root->addChild(&ball);
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
	player.pressed(key);
	//ball.pressed(key);
}

void SceneGraph::DisplayFunc()
{
	root->draw(projectionMatrix, modelViewMatrix);
    userScore.draw();
    comScore.draw();
}

void SceneGraph::IdleFunc()
{
    if (userScore.getScore() == endScore || comScore.getScore() == endScore) {
        root->reset();
        userScore.reset();
        comScore.reset();
    }
    else
        root->move();
}

void SceneGraph::reset()
{
    root->reset();
}
