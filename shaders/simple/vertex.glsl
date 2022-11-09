#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aTangent;
layout (location = 3) in vec3 aBitangent;
layout (location = 4) in vec2 aTexCoords;

uniform mat4 uViewMatrix;
uniform mat4 uProjectionMatrix;
uniform mat4 uModel;

out vec3 wFragPos;
out vec3 tFragPos;
out vec3 cFragPos; //Camera FragPos -> frag position from the point of view of the camera
//Normal is in world view
out vec3 normal;
out mat3 tangentFrame;
out vec2 texcoords;


void main(){
	wFragPos = vec3(uModel * vec4(aPosition,1.0));
	cFragPos = vec3(uViewMatrix * vec4(wFragPos,1.0));
	//I really like it ngl
	mat3 normalMatrix = transpose(inverse(mat3(uModel)));
	vec3 t = normalize(normalMatrix * aTangent);
	vec3 n = normalize(normalMatrix * aNormal);
	vec3 b = normalize(cross(n,t));
	tangentFrame = mat3(t,b,n);
	tFragPos = tangentFrame * wFragPos;
	normal = n;
	texcoords = aTexCoords;
	

	gl_Position = uProjectionMatrix * uViewMatrix * vec4(wFragPos,1.0);
}