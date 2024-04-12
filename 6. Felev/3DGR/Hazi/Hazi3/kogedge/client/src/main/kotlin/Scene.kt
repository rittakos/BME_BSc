import org.w3c.dom.HTMLCanvasElement
import org.khronos.webgl.WebGLRenderingContext as GL
import org.khronos.webgl.Float32Array
import vision.gears.webglmath.UniformProvider
import vision.gears.webglmath.Vec3
import vision.gears.webglmath.Mat4
import org.w3c.dom.events.MouseEvent
import kotlin.js.Date

class Scene (
  val gl : WebGL2RenderingContext) : UniformProvider("scene") {

  val vsTrafo = Shader(gl, GL.VERTEX_SHADER, "trafo-vs.glsl")
  val fsTextured = Shader(gl, GL.FRAGMENT_SHADER, "textured-fs.glsl")  
  val texturedProgram = Program(gl, vsTrafo, fsTextured)

  val vsBox = Shader(gl, GL.VERTEX_SHADER, "box-vs.glsl")
  val fsBox = Shader(gl, GL.FRAGMENT_SHADER, "box-fs.glsl")  
  val boxProgram = Program(gl, vsBox, fsBox)

  val vsInfPlane = Shader(gl, GL.VERTEX_SHADER, "trafo-vs.glsl")
  val fsInfPlane = Shader(gl, GL.FRAGMENT_SHADER, "textured-fs.glsl")
  val infinitePlaneProgram = Program(gl, vsInfPlane, fsInfPlane)

  val vsGround = Shader(gl, GL.VERTEX_SHADER, "ground-vs.glsl")
  val fsGround = Shader(gl, GL.FRAGMENT_SHADER, "ground-fs.glsl")
  val groundProgram = Program(gl, vsGround, fsGround)

  val envTexture = TextureCube(gl, 
  "media/sky/posx512.jpg",
  "media/sky/negx512.jpg",
  "media/sky/posy512.jpg",
  "media/sky/negy512.jpg",
  "media/sky/posz512.jpg",
  "media/sky/negz512.jpg")


  val quadGeometry = TexturedQuadGeometry(gl)
  val infinitePlaneGeometry = TexturedInfinitePlaneGeometry(gl)

  class Ground(
        m: UniformProvider,
        val p : Vec3 = Vec3.zeros.clone(),
        var r : Float = 0.0f,
        val s : Vec3 = Vec3.ones.clone()):GameObject(m, p, r, s), Collidable
    {
        override fun collideWith(other: Car)
        {
          //println("collide ground")
          if(other.getPosition().y - this.position.y < 5.5f && other.getPosition().y - this.position.y > 4.0f) 
          {
            other.setFalling(false)
            other.setOnSurface(true)
            other.getCurrentForce().y= 0.0f
          }else
          {
            other.setOnSurface(false)
            other.setFalling(true)
          }
        }
    }

  //val carMaterial = Material(texturedProgram)
  //val wheelMaterial = Material(simpleProgram)
  val treeMaterial = Material(texturedProgram)
  val groundMaterial = Material(groundProgram)
  val backgroundMaterial = Material(boxProgram)
  val holeMaterial = Material(texturedProgram)

  val car : Car

  val gameObjects = ArrayList<GameObject>()
  init{
    // carMaterial["colorTexture"]?.set(
    // Texture2D(gl, "media/json/chevy/chevy.png"))
    // carMaterial["texOffset"]?.set(0.1f, 0.4f)

    holeMaterial["colorTexture"]?.set(
    Texture2D(gl, "media/hole.png"))
    holeMaterial["texOffset"]?.set(0.1f, 0.4f)

    treeMaterial["colorTexture"]?.set(
    Texture2D(gl, "media/json/tree.png"))
    treeMaterial["texOffset"]?.set(0.1f, 0.4f)

    groundMaterial["colorTexture"]?.set(
    Texture2D(gl, "media/road.jpg"))
    groundMaterial["texOffset"]?.set(0.1f, 0.4f)

    // wheelMaterial["colorTexture"]?.set(
    // Texture2D(gl, "media/json/tree.png"))
    // wheelMaterial["texOffset"]?.set(0.1f, 0.4f)

    backgroundMaterial["envTexture"]?.set(envTexture)

    car = Car(gl, Vec3(0.0f, 10.0f, 0.0f))

    gameObjects.add(Ground(Mesh(groundMaterial, infinitePlaneGeometry)))
    
    gameObjects.add(Tree(MultiMesh(arrayOf(treeMaterial), load(gl, "media/json/tree.json")), Vec3(50.0f, 0.0f, 0.0f)))
    gameObjects.add(Tree(MultiMesh(arrayOf(treeMaterial), load(gl, "media/json/tree.json")), Vec3(-50.0f, 0.0f, 0.0f)))
    gameObjects.add(Tree(MultiMesh(arrayOf(treeMaterial), load(gl, "media/json/tree.json")), Vec3(50.0f, 0.0f, 100.0f)))
    gameObjects.add(Tree(MultiMesh(arrayOf(treeMaterial), load(gl, "media/json/tree.json")), Vec3(-50.0f, 0.0f, 100.0f)))
    gameObjects.add(Tree(MultiMesh(arrayOf(treeMaterial), load(gl, "media/json/tree.json")), Vec3(50.0f, 0.0f, 200.0f)))
    gameObjects.add(Tree(MultiMesh(arrayOf(treeMaterial), load(gl, "media/json/tree.json")), Vec3(-50.0f, 0.0f, 200.0f)))

    gameObjects.add(Hole(Mesh(holeMaterial, quadGeometry), Vec3(-20.0f, 0.1f, 0.0f), 0.0f, Vec3(2.5f, 2.5f, 2.5f)))
    gameObjects.add(Hole(Mesh(holeMaterial, quadGeometry), Vec3(0.0f, 0.1f, 200.0f), 0.0f, Vec3(2.5f, 2.5f, 2.5f)))
    //gameObjects.add(GameObject(Mesh(backgroundMaterial, quadGeometry), Vec3(0.0f, 0.0f, 0.99999f)))
  }

  val camera = PerspectiveCamera(*Program.all)

  val timeAtFirstFrame = Date().getTime()
  var timeAtLastFrame =  timeAtFirstFrame

  init{
    //LABTODO: depth test
    gl.enable(GL.DEPTH_TEST)
    addComponentsAndGatherUniforms(*Program.all)
    camera.yaw = 3.1415f
  }

  fun mouseDown(){
    camera.mouseDown()
  }

  fun mouseMove(event: MouseEvent){
    camera.mouseMove(event)
  }

  fun mouseUp(){
    camera.mouseUp()
  }

  fun resize(gl : WebGL2RenderingContext, canvas : HTMLCanvasElement) {
    gl.viewport(0, 0, canvas.width, canvas.height)
    camera.setAspectRatio(canvas.width.toFloat() / canvas.height.toFloat())
  }

  @Suppress("UNUSED_PARAMETER")
  fun update(gl : WebGL2RenderingContext, keysPressed : Set<String>) {

    val timeAtThisFrame = Date().getTime() 
    val dt = (timeAtThisFrame - timeAtLastFrame).toFloat() / 1000.0f
    val t  = (timeAtThisFrame - timeAtFirstFrame).toFloat() / 1000.0f    
    timeAtLastFrame = timeAtThisFrame

    //LABTODO: move camera
    camera.move(dt, keysPressed)

    // clear the screen
    gl.clearColor(0.3f, 0.0f, 0.3f, 1.0f)
    gl.clearDepth(1.0f)
    gl.clear(GL.COLOR_BUFFER_BIT or GL.DEPTH_BUFFER_BIT)

    gl.enable(GL.BLEND)
    gl.blendFunc( GL.SRC_ALPHA, GL.ONE_MINUS_SRC_ALPHA)

    gameObjects.forEach { it.move(t, dt, keysPressed, gameObjects) }
    car.move(t, dt, keysPressed, gameObjects)
    car.update()
    car.draw(camera)
    camera.position += car.ds//getPosition()
    gameObjects.forEach { it.update() }
    gameObjects.forEach { it.draw( camera ) }
  }
}
