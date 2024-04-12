#version 300 es

precision highp float;

in vec4 texCoord;
in vec4 rayDir;
out vec4 fragmentColor;


uniform struct {
    Framebuffer rawTexture; 
} material;

void main(void) 
{
    fragmentColor = texture(material.rawTexture., texCoord.xy);
}