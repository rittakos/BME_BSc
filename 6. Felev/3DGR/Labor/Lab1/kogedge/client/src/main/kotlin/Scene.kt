import org.w3c.dom.HTMLCanvasElement
import org.khronos.webgl.WebGLRenderingContext as GL //# GL# we need this for the constants declared ˙HUN˙ a constansok miatt kell
import org.khronos.webgl.Float32Array
import vision.gears.webglmath.Mat4
import vision.gears.webglmath.Vec2
import kotlin.js.Date

class Scene (
  val gl : WebGL2RenderingContext){

  val vsIdle = Shader(gl, GL.VERTEX_SHADER, "idle-vs.glsl")
  val vsTrafo = Shader(gl, GL.VERTEX_SHADER, "trafo-vs.glsl")
  val fsSolid = Shader(gl, GL.FRAGMENT_SHADER, "solid-fs.glsl")
  val fsGarish = Shader(gl, GL.FRAGMENT_SHADER, "garish-fs.glsl")
  val solidProgram = Program(gl, vsIdle, fsSolid)
  val garishProgram = Program(gl, vsTrafo, fsGarish)

  val quadGeometry = TexturedQuadGeometry(gl)
  val triangleGeometry = TexturedTriangleGeometry(gl)
  val asteroidTexture = Texture2D(gl, "media/asteroid.png") 

  val modelMatrix = Mat4()
  val timeAtFirstFrame = Date().getTime()
  var timeAtLastFrame =  timeAtFirstFrame
  val velocity = 0.5f

  var visible = true

  var width = 1000
  var height = 600

  fun resize(gl : WebGL2RenderingContext, canvas : HTMLCanvasElement) {
    width = canvas.width
    height = canvas.height
    gl.viewport(0, 0, canvas.width, canvas.height)//#viewport# tell the rasterizer which part of the canvas to draw to ˙HUN˙ a raszterizáló ide rajzoljon
  }

  fun setPosition(x: Int, y: Int)
  {
    val pos = Vec2((x.toFloat()) / (width / 2), (-1 * y.toFloat()) / (height / 2))
    //val pos = Vec2(1.0f, 0.0f)
    //direction = destination - position
    modelMatrix.set(1.0f, 0.0f, 0.0f, 0.0f,
                    0.0f, 1.0f, 0.0f, 0.0f,
                    0.0f, 0.0f, 1.0f, 0.0f,
                    0.0f, 0.0f, 0.0f, 1.0f)
    modelMatrix.translate(pos)
  }

  

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
      modelMatrix.translate(velocity * dt)
    }
    if("LEFT" in keysPressed)
    {
      modelMatrix.translate(-1 * velocity * dt)
    }
    if("S" in keysPressed)
    {
      visible = !visible
    }
    if("C" in keysPressed)
    {
      triangleGeometry.changeColor(-0.01f)
    }
    if("V" in keysPressed)
    {
      triangleGeometry.changeColor(0.01f)
    }

    // gl.uniformMatrix4fv(
    //   gl.getUniformLocation(garishProgram.glProgram, "gameObject.modelMatrix"), false,
    //     Float32Array( arrayOf<Float>(
    //       1.0f, 0.0f, 0.0f, 0.1f,
    //       0.0f, 1.0f, 0.0f, 0.2f,
    //       0.0f, 0.0f, 1.0f, 0.0f,
    //       0.0f, 0.0f, 0.0f, 1.0f )))

    gl.uniformMatrix4fv(
      gl.getUniformLocation(garishProgram.glProgram, "gameObject.modelMatrix"), false, modelMatrix.storage)


    gl.uniform1i(gl.getUniformLocation(garishProgram.glProgram, "material.colorTexture"), 0)
    gl.activeTexture(GL.TEXTURE0)
    gl.bindTexture(GL.TEXTURE_2D, asteroidTexture.glTexture)


    //gl.useProgram(solidProgram.glProgram)
    //quadGeometry.draw()
    gl.useProgram(garishProgram.glProgram)

    gl.enable(GL.BLEND)
    gl.blendFunc( GL.SRC_ALPHA, GL.ONE_MINUS_SRC_ALPHA)


    if(visible)
    {
      triangleGeometry.draw()
    }
  }
}