#version 300 es

precision highp float;

in vec2 tex;
in vec4 worldNormal;
in vec4 worldPosition;
out vec4 fragmentColor;

uniform struct {
	//sampler2D colorTexture;
    samplerCube envmapTexture;
} material;

uniform struct{
  mat4 viewProjMatrix;
  vec3 position;
} camera;


void main(void) {
    vec3 x = worldPosition.xyz / worldPosition.w;
    vec3 viewDir = normalize(camera.position  - x);
    //vec3 viewDir = normalize(vec3(1.0f, 0.0f, 0.0f)  - x);
    vec3 normal = normalize(worldNormal.xyz);

    fragmentColor = texture( material.envmapTexture, reflect(-viewDir, normal));

    //fragmentColor = vec4(abs(normal), 1);//texture(material.colorTexture, tex);
}
