import org.w3c.dom.HTMLCanvasElement
import org.khronos.webgl.WebGLRenderingContext as GL //# GL# we need this for the constants declared ˙HUN˙ a constansok miatt kell
import kotlin.js.Date
import kotlin.collections.ArrayList
import vision.gears.webglmath.UniformProvider
import vision.gears.webglmath.Vec1
import vision.gears.webglmath.Vec2
import vision.gears.webglmath.Vec3
import vision.gears.webglmath.Mat4

class Scene (
  val gl : WebGL2RenderingContext) : UniformProvider("scene") {

  

  //Time Variables
  val timeAtFirstFrame = Date().getTime()
  var timeAtLastFrame =  timeAtFirstFrame
  val time by Vec1()
  //--------

  //Shaders
  val vsTrafo = Shader(gl, GL.VERTEX_SHADER, "trafo-vs.glsl")
  val fsSolid = Shader(gl, GL.FRAGMENT_SHADER, "solid-fs.glsl")
  //--------

  //Model Matrix
  var modelMatrix = Mat4()
  //--------

  //Programs
  val texturedProgram = Program(gl, vsTrafo, fsSolid)
  //--------

  //Geometries
  val texturedQuadGeometry = TexturedQuadGeometry(gl)
  //--------

  //Materials
  val landerMaterial = Material(texturedProgram)
  val asteroidMaterial = Material(texturedProgram)
  //--------

  
  //Meshes
  val asteroidQuad = Mesh(asteroidMaterial, texturedQuadGeometry)
  val landerQuad = Mesh(landerMaterial, texturedQuadGeometry)
  //-------
  

  //GameObjects
  val gameObjects: ArrayList<GameObject>

  val slowMover = object: GameObject(landerQuad){
    val velocity = Vec2(0.01f, 0.01f)
    override fun move(dt: Float, t : Float,
                      keysPressed : Set <String>, gameObjects : List<GameObject>): Boolean{
      position += velocity
      camera.position += velocity
      return true
    }
  }

  val fastMover = object: GameObject(asteroidQuad){
    val velocity = Vec2(0.05f, 0.05f)
    override fun move(dt: Float, t : Float,
                      keysPressed : Set <String>, gameObjects : List<GameObject>): Boolean{
      position += velocity
      return true
    }
  }

  val spinner = object: GameObject(asteroidQuad){
    val rotation = 0.5f;
    override fun move(dt: Float, t : Float,
                      keysPressed : Set <String>, gameObjects : List<GameObject>): Boolean{
      roll += rotation
      return true
    }
  }

  val spinnable = object: GameObject(landerQuad){
    val rotation = 0.5f;
    override fun move(dt: Float, t : Float,
                      keysPressed : Set <String>, gameObjects : List<GameObject>): Boolean{
      if("LEFT" in keysPressed)
        roll += rotation
      if("RIGHT" in keysPressed)
        roll -= rotation
      return true
    }
  }

  val destroyingMover = object: GameObject(landerQuad){
    val velocity = Vec2(0.03f, 0.0f)
    override fun move(dt: Float, t : Float,
                      keysPressed : Set <String>, gameObjects : List<GameObject>): Boolean{
      position += velocity
      if(position.x > 0) {return false}
      return true
    }
  }
  //--------
  
  //Camera
  val camera: OrthoCamera
  //--------

  //Constructor
  init{
    asteroidMaterial["colorTexture"]?.set(
    Texture2D(gl, "media/asteroid.png"))
    asteroidMaterial["texOffset"]?.set(0.1f, 0.4f)

    landerMaterial["colorTexture"]?.set(
    Texture2D(gl, "media/lander.png"))
    landerMaterial["texOffset"]?.set(0.1f, 0.4f)

    addComponentsAndGatherUniforms(*Program.all)
    camera = OrthoCamera(*Program.all)

    gameObjects = arrayListOf<GameObject>()
    gameObjects.add(GameObject(asteroidQuad, Vec2(5.0f, -5.0f), 0.5f, Vec2(1.0f, 1.0f)))
    gameObjects.add(GameObject(landerQuad, Vec2(-5.0f, -5.0f), 1.5f, Vec2(0.3f, 0.3f)))

    fastMover.position.set(-5.0f, 0.0f)
    //fastMover.scale.set(Vec2(0.2f, 0.2f))

    slowMover.position.set(-5.0f, 3.0f)
    //slowMover.scale.set(Vec2(0.2f, 0.2f))

    spinner.position.set(-5.0f, 0.0f)
    //spinner.scale.set(Vec2(0.2f, 0.2f))

    spinnable.position.set(0.0f, 0.0f)
    //spinnable.scale.set(Vec2(0.2f, 0.2f))

    destroyingMover.position.set(-5.0f, -3.0f)

    gameObjects.add(fastMover)
    gameObjects.add(slowMover)
    gameObjects.add(spinner)
    gameObjects.add(spinnable)
    gameObjects.add(destroyingMover)
  }
  //--------

  //Functions

  fun resize(gl : WebGL2RenderingContext, canvas : HTMLCanvasElement) {
    gl.viewport(0, 0, canvas.width, canvas.height)//#viewport# tell the rasterizer which part of the canvas to draw to ˙HUN˙ a raszterizáló ide rajzoljon
    camera.setAspectRatio(canvas.width.toFloat() / canvas.height.toFloat())
  }

  @Suppress("UNUSED_PARAMETER")
  fun update(gl : WebGL2RenderingContext, keysPressed : Set<String>) {
    val timeAtThisFrame = Date().getTime() / 1.0f
    val dt = (timeAtThisFrame - timeAtLastFrame).toFloat() / 100000.0f
    time.set( (timeAtThisFrame - timeAtFirstFrame).toFloat() / 100000.0f )
    timeAtLastFrame = timeAtThisFrame
    
    gl.clearColor(0.3f, 0.0f, 0.3f, 1.0f)//## red, green, blue, alpha in [0, 1]
    gl.clearDepth(1.0f)//## will be useful in 3D ˙HUN˙ 3D-ben lesz hasznos
    gl.clear(GL.COLOR_BUFFER_BIT or GL.DEPTH_BUFFER_BIT)//#or# bitwise OR of flags
    
    //modelMatrix = Mat4()
    
    
    //gl.uniformMatrix4fv(
    //  gl.getUniformLocation(texturedProgram.glProgram, "gameObject.modelMatrix"), false, camera.viewProjMatrix.storage)
      
    //gl.uniform1i(gl.getUniformLocation(garishProgram.glProgram, "material.colorTexture"), 0)
    //gl.activeTexture(GL.TEXTURE0)
    //gl.bindTexture(GL.TEXTURE_2D, bodyTexture.glTexture)
    
    //gl.useProgram(texturedProgram.glProgram)
    
    gl.enable(GL.BLEND)
    gl.blendFunc( GL.SRC_ALPHA, GL.ONE_MINUS_SRC_ALPHA)
    
    //asteroidMaterial.draw()
    //texturedQuadGeometry.draw()
    // asteroidQuad.draw()
    
    // modelMatrix.translate(Vec2(0.5f, -0.5f));
    
    // gl.uniformMatrix4fv(
    //   gl.getUniformLocation(texturedProgram.glProgram, "gameObject.modelMatrix"), false, modelMatrix.storage)
    
    //landerQuad.draw()
    //landerMaterial.draw()
    //texturedQuadGeometry.draw()

    val destroyedGameObjects = arrayListOf<GameObject>()

    gameObjects.forEach { if(!it.move(timeAtThisFrame.toFloat(), dt, keysPressed, gameObjects)){destroyedGameObjects.add(it)} }
    destroyedGameObjects.forEach{gameObjects.remove(it)}
    gameObjects.forEach{it.update()}
    gameObjects.forEach { it.draw(camera) }
    
    camera.updateViewProjMatrix()
  }
  //-------
} 