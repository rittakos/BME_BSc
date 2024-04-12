#version 300 es

in vec4 vertexPosition;

uniform struct{
    mat4 rayDirMatrix;
} camera;

out vec4 rayDir;

void main(void) {
  gl_Position = vec4(vertexPosition.x, vertexPosition.y, 0.999999f, 1);
  rayDir = vertexPosition * camera.rayDirMatrix;
}