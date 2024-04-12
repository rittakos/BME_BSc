#version 300 es

in vec4 vertexPosition; //#vec4# A four-element vector [x,y,z,w].; We leave z and w alone.; They will be useful later for 3D graphics and transformations. #vertexPosition# attribute fetched from vertex buffer according to input layout spec
in vec2 vertexTexCoord;

out vec2 tex;

uniform struct{
  mat4 modelMatrix; 
  vec2 moveOffset;
} gameObject;


void main(void) {
  gl_Position = vertexPosition * gameObject.modelMatrix; //#gl_Position# built-in output, required
  tex = vertexTexCoord * 0.125 + gameObject.moveOffset;
}