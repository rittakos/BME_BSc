#version 300 es

precision highp float;

in vec2 tex;
in vec4 worldNormal;
in vec4 worldPosition;
out vec4 fragmentColor;

uniform struct {
	sampler2D colorTexture;
} material;

uniform struct {
  vec4 position;
  vec3 powerDensity;
} lights[8];

vec3 shade(vec3 normal, vec3 lightDir, vec3 powerDensity, vec3 materialColor) 
{
    float cosa = dot(normal, lightDir);
    if(cosa < 0.0f)
    {
        cosa = 0.0f;
    }
    
    vec3 v = materialColor * cosa;
    return powerDensity * materialColor * cosa;
    //return vec3(powerDensity.x * v.x, powerDensity.y * v.y, powerDensity.z * v.z);
             
    //return dot(powerDensity, materialColor) * (lightDir * n);
}


void main(void) 
{
    vec3 x = worldPosition.xyz / worldPosition.w;
    //vec3 viewDir = normalize(camera.position  - x);
    vec3 normal = normalize(worldNormal.xyz);
    vec3 lightDir = vec3(0.0f, 1.0f, 0.0f);
    
    float cosValue = dot(lightDir, normal);
    
    vec4 text = texture(material.colorTexture, tex);
    //fragmentColor = vec4(text.xyz * cosValue, text.w);
    fragmentColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);

    for(int i = 0; i < lights.length(); ++i)
    {
        vec3 lightDir = lights[i].position.xyz;
        vec3 powerDensity = lights[i].powerDensity;

        //vec3 s = shade(normal, normal, normal, normal);
        vec3 s = shade(normal, lightDir, powerDensity, texture(material.colorTexture, tex).rgb);

        fragmentColor.rgb += s;
    }
    //fragmentColor = texture(material.colorTexture, tex);
}