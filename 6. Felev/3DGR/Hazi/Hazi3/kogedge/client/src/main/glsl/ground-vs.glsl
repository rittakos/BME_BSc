#version 300 es

in vec4 vertexPosition;
in vec4 vertexTexCoord;
uniform struct{
	mat4 modelMatrix;
} gameObject;

uniform struct{
	mat4 viewProjMatrix;
} camera;

out vec4 tex;

void main(void) {
  gl_Position = vertexPosition * gameObject.modelMatrix * camera.viewProjMatrix;
  tex = vertexTexCoord;
}