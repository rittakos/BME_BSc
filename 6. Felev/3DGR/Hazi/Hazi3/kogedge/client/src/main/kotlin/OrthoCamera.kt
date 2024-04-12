import vision.gears.webglmath.UniformProvider
import vision.gears.webglmath.Vec2
import vision.gears.webglmath.Mat4

class OrthoCamera(vararg programs : Program) : UniformProvider("camera") {

  val position = Vec2(0.0f, 0.0f) 
  val roll = 0.0f 
  val windowSize = Vec2(20.0f, 20.0f) 
    
  val viewProjMatrix by Mat4()
  init{
    updateViewProjMatrix()
    addComponentsAndGatherUniforms(*programs)
  }

  fun updateViewProjMatrix() { 
    viewProjMatrix.set(). 
      scale(0.05f, 0.05f). 
      scale(windowSize). 
      rotate(roll). 
      translate(position). 
      invert()
  }

  fun setAspectRatio(ar : Float) { 
    windowSize.x = windowSize.y * ar
    updateViewProjMatrix()
  } 
}