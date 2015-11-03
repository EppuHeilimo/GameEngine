#include "ParticleSystem.h"


ParticleSystem::ParticleSystem() : ShaderProgram(vertexfileLocation(), geometryFileLocation(), 1)
{
	bindAttributes();
	getAllUniformLocations();
	iCurReadBuffer = 0;
	textureid = loader.loadTexture("./res/mud2.png");
	init = false;
}


ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::getAllUniformLocations(){

	location_timePassed = getUniformLocation("fTimePassed");
	location_genPosition = getUniformLocation("vGenPosition");
	location_genVelocityMin = getUniformLocation("vGenVelocityMin");
	location_genVelocityRange = getUniformLocation("vGenVelocityRange");
	location_genColor = getUniformLocation("vGenColor");
	location_genGravityVector = getUniformLocation("vGenGravityVector");
	location_genLifeMin = getUniformLocation("fGenLifeMin");
	location_genLifeRange = getUniformLocation("fGenLifeRange");
	location_genSize = getUniformLocation("fGenSize");
	location_numToGenerate = getUniformLocation("iNumToGenerate");
	location_randomSeed = getUniformLocation("vRandomSeed");
}

void ParticleSystem::bindAttributes(){
	bindAttribute(0, "position");
}

std::string ParticleSystem::vertexfileLocation(){
	return "./res/particleUpdateVertex.txt";
}

std::string ParticleSystem::geometryFileLocation(){
	return "./res/particleUpdateGeoShader.txt";
}

void ParticleSystem::RenderParticles(glm::mat4& projection, Camera cam, float delta){
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureid);
	
	renderer.setMatrices(projection, cam);
	updateParticles(delta);
	renderer.render(uiVAO, iCurReadBuffer, iNumParticles);
	renderComplete();
	
}

void ParticleSystem::renderComplete(){
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(4);
	glDisableVertexAttribArray(5);
	glBindVertexArray(0);
}

bool ParticleSystem::initializeParticles(){
	int PARTICLE_TYPE_GENERATOR = 0;
	int MAX_PARTICLES_ON_SCENE = 40;
	if (init) return false;
	const char* sVaryings[6] =
	{
		"vPositionOut",
		"vVelocityOut",
		"vColorOut",
		"fLifeTimeOut",
		"fSizeOut",
		"iTypeOut",
	};
	for (int i = 0; i < 6; i++){
		glTransformFeedbackVaryings(getProgramID(), 6, sVaryings, GL_INTERLEAVED_ATTRIBS);
		glLinkProgram(getProgramID());
		CheckShaderError(getProgramID(), GL_LINK_STATUS, true, "Shaderprogram failed to link!");
	}

	glGenTransformFeedbacks(1, &uiTransformFeedbackBuffer);
	glGenQueries(1, &uiQuery);

	glGenBuffers(2, uiParticleBuffer);
	glGenVertexArrays(2, uiVAO);

	Particle partInitialization;
	partInitialization.type = PARTICLE_TYPE_GENERATOR;

	for (int i = 0; i < 2; i++)
	{
		glBindVertexArray(uiVAO[i]);
		glBindBuffer(GL_ARRAY_BUFFER, uiParticleBuffer[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Particle)*MAX_PARTICLES_ON_SCENE, NULL, GL_DYNAMIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Particle), &partInitialization);

		for (int j = 0; j < 6; j++)
			glEnableVertexAttribArray(i);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (const GLvoid*)0); // Position
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (const GLvoid*)12); // Velocity
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (const GLvoid*)24); // Color
		glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), (const GLvoid*)36); // Lifetime
		glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), (const GLvoid*)40); // Size
		glVertexAttribPointer(5, 1, GL_INT, GL_FALSE, sizeof(Particle), (const GLvoid*)44); // Type
	}
	iCurReadBuffer = 0;
	iNumParticles = 1;

	init = true;

	return true;


}

void ParticleSystem::SetGeneratorProperties(glm::vec3 a_vGenPosition, glm::vec3 a_vGenVelocityMin, glm::vec3 a_vGenVelocityMax, glm::vec3 a_vGenGravityVector, glm::vec3 a_vGenColor, float a_fGenLifeMin, float a_fGenLifeMax, float a_fGenSize, float fEvery, int a_iNumToGenerate)
{
	genPosition = a_vGenPosition;
	genVelocityMin = a_vGenVelocityMin;
	genVelocityRange = a_vGenVelocityMax - a_vGenVelocityMin;

	genGravity = a_vGenGravityVector;
	genColor = a_vGenColor;
	genSize = a_fGenSize;

	genLifeMin = a_fGenLifeMin;
	genLifeRange = a_fGenLifeMax - a_fGenLifeMin;

	fNextGenerationTime = fEvery;
	fElapsedTime = 0.8f;

	numToGen = a_iNumToGenerate;
}

void ParticleSystem::updateParticles(float timePassed){
	if (init) return;

	loadFloat(location_timePassed, timePassed);
	loadVector3f(location_genPosition, genPosition);
	loadVector3f(location_genVelocityMin, genVelocityMin);
	loadVector3f(location_genVelocityRange, genVelocityRange);
	loadVector3f(location_genColor, genColor);
	loadVector3f(location_genGravityVector, genGravity);
	loadFloat(location_genLifeMin, genLifeMin);
	loadFloat(location_genLifeRange, genLifeRange);
	loadFloat(location_genSize, genSize);
	loadFloat(location_numToGenerate, 0);

	fElapsedTime += timePassed;

	if (fElapsedTime > fNextGenerationTime)
	{
		srand(time(NULL));
		loadFloat(location_numToGenerate, numToGen);
		fElapsedTime -= fNextGenerationTime;
		glm::vec3 vRandomSeed = glm::vec3(grandf(-10.0f, 20.0f), grandf(-10.0f, 20.0f), grandf(-10.0f, 20.0f));
		loadVector3f(location_randomSeed, vRandomSeed);
	}

	glEnable(GL_RASTERIZER_DISCARD);
	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, uiTransformFeedbackBuffer);

	glBindVertexArray(uiVAO[iCurReadBuffer]);
	glEnableVertexAttribArray(1); // Re-enable velocity

	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, uiParticleBuffer[1 - iCurReadBuffer]);

	glBeginQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN, uiQuery);
	glBeginTransformFeedback(GL_POINTS);

	glDrawArrays(GL_POINTS, 0, iNumParticles);

	glEndTransformFeedback();

	glEndQuery(GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN);
	glGetQueryObjectiv(uiQuery, GL_QUERY_RESULT, &iNumParticles);

	iCurReadBuffer = 1 - iCurReadBuffer;

	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);
}

float ParticleSystem::grandf(float fMin, float fAdd)
{
	float fRandom = float(rand() % (RAND_MAX + 1)) / float(RAND_MAX);
	return fMin + fAdd*fRandom;
}


int ParticleSystem::getNumParticles(){
	return iNumParticles;
}
