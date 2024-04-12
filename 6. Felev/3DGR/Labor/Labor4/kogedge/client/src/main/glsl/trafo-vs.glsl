#version 300 es

in vec4 vertexPosition;
in vec2 vertexTexCoord;
in vec3 vertexNormal;

out vec2 tex;
out vec4 modelPosition;
out vec4 worldPosition;
out vec4 worldNormal;


uniform struct{
  mat4 modelMatrix;
  mat4 modelMatrixInverse;
} gameObject;

uniform struct{
  mat4 viewProjMatrix;
  vec3 position;
} camera;

void main(void) {
  gl_Position = vertexPosition * gameObject.modelMatrix * camera.viewProjMatrix;
  tex = vertexTexCoord;
  modelPosition = vertexPosition;
  worldPosition = vertexPosition * gameObject.modelMatrix;
  worldNormal = gameObject.modelMatrixInverse * vec4(vertexNormal, 0);
}