#version 330 core
in vec3 wFragPos;
in vec3 tFragPos;
in vec3 cFragPos; //Camera FragPos -> frag position from the point of view of the camera
//Normal is in world view
in vec3 normal;
in mat3 tangentFrame;


out vec4 FragColor;

void main(){

	FragColor = vec4(1.0,0.0,0.0,1.0);
}