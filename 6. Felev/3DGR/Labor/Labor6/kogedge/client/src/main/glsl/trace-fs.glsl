#version 300 es

precision highp float;

out vec4 fragmentColor;

uniform struct{
  samplerCube environment;
  sampler2D noiseTexture;

} material;

uniform struct {
  mat4 rayDirMatrix;
  vec3 position;
} camera;

in vec3 rayDir;

float f(vec3 p){
  return p.y - texture(material.noiseTexture, p.xz * 0.01).r;
  //return p.y - noise(p * 50.0f);
}

vec3 fGrad(vec3 p){
  return vec3(
    f(p + vec3(+0.05, 0.0, 0.0) ) -
    f(p + vec3(-0.05, 0.0, 0.0) ) ,
    f(p + vec3(0.0, +0.05, 0.0) ) -
    f(p + vec3(0.0, -0.05, 0.0) ) , 
    f(p + vec3(0.0, 0.0, +0.05) ) -
    f(p + vec3(0.0, 0.0, -0.05) ) 
    );
  //return vec3(0.0f, 1.0f, 0.0f) - noiseGrad(p * 50.0f);
}

float noise(vec3 r) {
  uvec3 s = uvec3(
    0x1D4E1D4E,
    0x58F958F9,
    0x129F129F);
  float f = 0.0;
  for(int i=0; i<16; i++) {
    vec3 sf =
    vec3(s & uvec3(0xFFFF))
  / 65536.0 - vec3(0.5, 0.5, 0.5);
    
    f += sin(dot(sf, r));
    s = s >> 1;
  }
  return f / 32.0 + 0.5;
}


vec3 noiseGrad(vec3 r) {
  uvec3 s = uvec3(
    0x1D4E1D4E,
    0x58F958F9,
    0x129F129F);
  vec3 f = vec3(0, 0, 0);
  for(int i=0; i<16; i++) {
    vec3 sf =
    vec3(s & uvec3(0xFFFF))
  / 65536.0 - vec3(0.5, 0.5, 0.5);
    
    f += cos(dot(sf, r)) * sf;
    s = s >> 1;
  }
  return f;
}


void main(void) {
  vec3 d = normalize(rayDir.xyz);
  float t1 = -1.0f;
  float t2 = -1.0f;
  t1 = -1.0f * camera.position.y / d.y;
  t2 = (1.0f - camera.position.y) / d.y;
  float tstart = max(min(t1, t2), 0.0);
  float tend = max(t1, t2);


  bool found = false;
  vec3 p, color;

  if(tstart < tend) {
      p = camera.position + d * tstart;
      // vec3 step = d * min((tend - tstart)/2, 0.01);
      // for(int i = 0; i < 16; ++i)
      // {
      //   step *= 0.5f;
      //   if(f(p) > 0.0f)
      //     p += step;
      //   else
      //     p -= step;
      // }
      vec3 step = d * min((tend - tstart)/580.0, 0.01);
      for(int i = 0; i < 128; ++i)
      {
        if(f(p) > 0.0f)
        {
          found = true;
          break;
        }
        p = p + step;
        step *= 1.02;
      }
  }


  vec3 normal = normalize(fGrad(p));
  
  if(!found)
    fragmentColor = texture(material.environment, normalize(rayDir));
  else
    fragmentColor = vec4(normal.x, normal.y, normal.z, 1.0f);//vec4(p.y, p.y, p.y, 1.0f);


  //fragmentColor = texture(material.environment, normalize(rayDir));
}
