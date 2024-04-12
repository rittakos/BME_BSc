import org.w3c.dom.HTMLCanvasElement
import org.khronos.webgl.WebGLRenderingContext as GL //# GL# we need this for the constants declared ˙HUN˙ a constansok miatt kell
import kotlin.js.Date
import kotlin.collections.ArrayList
import kotlin.math.cos
import kotlin.math.sin
import vision.gears.webglmath.UniformProvider
import vision.gears.webglmath.Vec1
import vision.gears.webglmath.Vec2
import vision.gears.webglmath.Vec3
import vision.gears.webglmath.Mat4
//import com.sun.prism.Material

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
  val bulletMaterial = Material(texturedProgram)
  val bummMaterial = Material(texturedProgram)
  //--------

  
  //Meshes
  val asteroidQuad = Mesh(asteroidMaterial, texturedQuadGeometry)
  val landerQuad = Mesh(landerMaterial, texturedQuadGeometry)
  val bulletQuad = Mesh(bulletMaterial, texturedQuadGeometry)
  val bummQuad = Mesh(bummMaterial, texturedQuadGeometry)
  //-------
  
  fun rotateVector(vector: Vec2, rotation: Float): Vec2
  {
    val result = Vec2(  cos(rotation) * vector.x - sin(rotation) * vector.y, 
                        sin(rotation) * vector.x + cos(rotation) * vector.y)
    return result.normalize()
  }   

  //GameObjects
  val gameObjects: ArrayList<GameObject>

  val avatar = object: GameObject(landerQuad){
    val rotation = 0.1f;
    val velocity = 500.0f;
    var direction = Vec2(0.0f, 1.0f)
    var coolDown = 0.0f;
    override fun move(dt: Float, t : Float,
                      keysPressed : Set <String>, gameObjects : List<GameObject>): Boolean{

      coolDown = coolDown - dt
      if("LEFT" in keysPressed)
      {
        roll += rotation
        direction = rotateVector(direction, rotation)
      }
      if("RIGHT" in keysPressed)
      {
        roll -= rotation
        direction = rotateVector(direction, -1.0f * rotation)
      }
      if("UP" in keysPressed)
      {
        position += direction * velocity * dt
        camera.position += direction * velocity * dt
      }
      if("DOWN" in keysPressed)
      {
        position -= direction * velocity * dt
        camera.position -= direction * velocity * dt
      }
      if("SPACE" in keysPressed && coolDown <= 0.0f)
      {
        coolDown = 0.007f
        shot(Bullet(bulletQuad, position.clone() + direction * 1.5f, direction.clone()))
      }
      
      return true
    }
  }

  //--------
  
  //Camera
  val camera: OrthoCamera
  //--------

  fun initMaterials()
  {
    asteroidMaterial["colorTexture"]?.set(
    Texture2D(gl, "media/asteroid.png"))
    asteroidMaterial["texOffset"]?.set(0.1f, 0.4f)

    landerMaterial["colorTexture"]?.set(
    Texture2D(gl, "media/rocket.png"))
    landerMaterial["texOffset"]?.set(0.1f, 0.4f)

    bulletMaterial["colorTexture"]?.set(
    Texture2D(gl, "media/plasma.png"))
    bulletMaterial["texOffset"]?.set(0.1f, 0.4f)

    bummMaterial["colorTexture"]?.set(
    Texture2D(gl, "media/bumm.png"))
    bummMaterial["texOffset"]?.set(0.1f, 0.4f)
  }

  fun initGameObjets()
  {
    gameObjects.add(avatar)

    gameObjects.add(Asteroid(asteroidQuad, Vec2(5.0f, 5.0f), 1.5f))
    gameObjects.add(Asteroid(asteroidQuad, Vec2(15.0f, 15.0f), 1.5f))
    gameObjects.add(Asteroid(asteroidQuad, Vec2(10.0f, -15.0f), 3.5f))
    gameObjects.add(Asteroid(asteroidQuad, Vec2(1.0f, 5.0f), 0.1f))
    gameObjects.add(Asteroid(asteroidQuad, Vec2(-5.0f, -5.0f), 0.5f))
    gameObjects.add(Asteroid(asteroidQuad, Vec2(-15.0f, -15.0f), 2.5f))
    gameObjects.add(Asteroid(asteroidQuad, Vec2(25.0f, 15.0f), 10.5f))
    gameObjects.add(Asteroid(asteroidQuad, Vec2(15.0f, 25.0f), 0.5f))
    gameObjects.add(Asteroid(asteroidQuad, Vec2(15.0f, -255.0f), 10.5f))
    gameObjects.add(Asteroid(asteroidQuad, Vec2(-25.0f, 15.0f), 0.5f))
  }

  //Constructor
  init{
    initMaterials()

    addComponentsAndGatherUniforms(*Program.all)
    camera = OrthoCamera(*Program.all)

    gameObjects = arrayListOf<GameObject>()
    initGameObjets()
  }
  //--------

  //Functions

  fun shot(bullet: GameObject){
    gameObjects.add(bullet)
  }

  fun resize(gl : WebGL2RenderingContext, canvas : HTMLCanvasElement) {
    gl.viewport(0, 0, canvas.width, canvas.height)//#viewport# tell the rasterizer which part of the canvas to draw to ˙HUN˙ a raszterizáló ide rajzoljon
    camera.setAspectRatio(canvas.width.toFloat() / canvas.height.toFloat())
  }

  fun collisions(objects: ArrayList<GameObject>){
    val destroyedGameObjects = arrayListOf<GameObject>()
    for(i: Int in 0..objects.size-1)
    {
      for(j : Int in i+1..objects.size-1)
      {
        if(objects.get(i).collide(objects.get(j)))
        {
           destroyedGameObjects.add(objects.get(i))
           destroyedGameObjects.add(objects.get(j))
           gameObjects.add(Bumm(bummQuad, objects.get(j).position))
        }
      }
    }
    destroyedGameObjects.forEach{objects.remove(it)}
  }

  @Suppress("UNUSED_PARAMETER")
  fun update(gl : WebGL2RenderingContext, keysPressed : Set<String>) {
    val timeAtThisFrame = Date().getTime() / 1.0f
    val dt = (timeAtThisFrame - timeAtLastFrame).toFloat() / 100000.0f
    time.set( (timeAtThisFrame - timeAtFirstFrame).toFloat() / 100000.0f )
    timeAtLastFrame = timeAtThisFrame

    //println(dt)

    gl.clearColor(0.3f, 0.0f, 0.3f, 1.0f)//## red, green, blue, alpha in [0, 1]
    gl.clearDepth(1.0f)//## will be useful in 3D ˙HUN˙ 3D-ben lesz hasznos
    gl.clear(GL.COLOR_BUFFER_BIT or GL.DEPTH_BUFFER_BIT)//#or# bitwise OR of flags

    
    gl.enable(GL.BLEND)
    gl.blendFunc( GL.SRC_ALPHA, GL.ONE_MINUS_SRC_ALPHA)
    

    val destroyedGameObjects = arrayListOf<GameObject>()
    gameObjects.forEach { if(!it.move(dt, timeAtThisFrame.toFloat(), keysPressed, gameObjects)){destroyedGameObjects.add(it)} }
    destroyedGameObjects.forEach{gameObjects.remove(it)}
    destroyedGameObjects.clear()
    
    collisions(gameObjects)

    gameObjects.forEach{it.update()}
    gameObjects.forEach { it.draw(camera) }
    
    camera.updateViewProjMatrix()
  }
  //-------
} 