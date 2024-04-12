import org.w3c.dom.HTMLCanvasElement
import org.khronos.webgl.WebGLRenderingContext as GL //# GL# we need this for the constants declared ˙HUN˙ a constansok miatt kell
import org.khronos.webgl.Float32Array
import vision.gears.webglmath.Mat4
import vision.gears.webglmath.Vec2
import kotlin.js.Date

class Scene (
  val gl : WebGL2RenderingContext){

  val vsTrafo = Shader(gl, GL.VERTEX_SHADER, "trafo-vs.glsl")
  val fsGarish = Shader(gl, GL.FRAGMENT_SHADER, "garish-fs.glsl")
  val garishProgram = Program(gl, vsTrafo, fsGarish)

  val quadGeometry = TexturedQuadGeometry(gl)
  val bodyTexture = Texture2D(gl, "media/platformer_sprites_base.png") 

  var modelMatrix = Mat4()
  var moveOffset = Vec2()
  val timeAtFirstFrame = Date().getTime()
  var timeAtLastFrame =  timeAtFirstFrame

  var velocity = 3.0f
  

  var width = 1000
  var height = 600

  fun resize(gl : WebGL2RenderingContext, canvas : HTMLCanvasElement) {
    width = canvas.width
    height = canvas.height
    gl.viewport(0, 0, canvas.width, canvas.height)//#viewport# tell the rasterizer which part of the canvas to draw to ˙HUN˙ a raszterizáló ide rajzoljon
  }

  var wait = 0

  @Suppress("UNUSED_PARAMETER")
  fun update(gl : WebGL2RenderingContext, keysPressed : Set<String>) {
    gl.clearColor(0.3f, 0.0f, 0.0f, 1.0f)//## red, green, blue, alpha in [0, 1]
    gl.clearDepth(1.0f)//## will be useful in 3D ˙HUN˙ 3D-ben lesz hasznos
    gl.clear(GL.COLOR_BUFFER_BIT or GL.DEPTH_BUFFER_BIT)//#or# bitwise OR of flags


    val timeAtThisFrame = Date().getTime() 
    val dt = (timeAtThisFrame - timeAtLastFrame).toFloat() / 1000.0f
    val t = (timeAtThisFrame - timeAtFirstFrame).toFloat() / 1000.0f    
    timeAtLastFrame = timeAtThisFrame
    
    if("RIGHT" in keysPressed)
    {
      if(wait >= 5)
      {
        modelMatrix.translate(velocity * dt)
        moveOffset = moveOffset + Vec2(0.125f, 0.0f)
        wait = 0
      }
      ++wait
    }
    if("LEFT" in keysPressed)
    {
      if(wait >= 5)
      {
        modelMatrix.translate(-velocity * dt)
        moveOffset = moveOffset + Vec2(-0.125f, 0.0f)
        wait = 0
      }
      ++wait
    }
    if("R" in keysPressed)
    {
      modelMatrix = Mat4()
      moveOffset = Vec2()
      velocity = 2.5f
    }
    if("W" in keysPressed)
    {
      modelMatrix = Mat4()
      moveOffset = Vec2(0.0f, 0.875f)
      velocity = 1.0f
    }

    gl.uniformMatrix4fv(
      gl.getUniformLocation(garishProgram.glProgram, "gameObject.modelMatrix"), false, modelMatrix.storage)

    
    gl.uniform2fv(
      gl.getUniformLocation(garishProgram.glProgram, "gameObject.moveOffset"), moveOffset.storage)


    gl.uniform1i(gl.getUniformLocation(garishProgram.glProgram, "material.colorTexture"), 0)
    gl.activeTexture(GL.TEXTURE0)
    gl.bindTexture(GL.TEXTURE_2D, bodyTexture.glTexture)

    gl.useProgram(garishProgram.glProgram)

    gl.enable(GL.BLEND)
    gl.blendFunc( GL.SRC_ALPHA, GL.ONE_MINUS_SRC_ALPHA)

    quadGeometry.draw()
  }
}

