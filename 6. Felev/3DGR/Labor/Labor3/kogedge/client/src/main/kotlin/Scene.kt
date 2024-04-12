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

  val envTexture = TextureCube(gl, 
  "media/sky/posx512.jpg",
  "media/sky/negx512.jpg",
  "media/sky/posy512.jpg",
  "media/sky/negy512.jpg",
  "media/sky/posz512.jpg",
  "media/sky/negz512.jpg"
  )


  val quadGeometry = TexturedQuadGeometry(gl)

  val material1 = Material(texturedProgram)
  val material2 = Material(texturedProgram)
  val backgroundMaterial = Material(boxProgram)

  val gameObjects = ArrayList<GameObject>()
  init{
    material1["colorTexture"]?.set(
    Texture2D(gl, "media/slowpoke/YadonDh.png"))
    material1["texOffset"]?.set(0.1f, 0.4f)

    material2["colorTexture"]?.set(
    Texture2D(gl, "media/slowpoke/YadonEyeDh.png"))
    material2["texOffset"]?.set(0.1f, 0.4f)

    backgroundMaterial["envTexture"]?.set(envTexture)

    val materials = arrayOf(material1, material2)

    //LABTODO: add object from JSON
    gameObjects.add(GameObject(MultiMesh(materials, load(gl, "media/slowpoke/Slowpoke.json"))))
    //LABTODO: add background object
    gameObjects.add(GameObject(Mesh(backgroundMaterial, quadGeometry), Vec3(0.0f, 0.0f, 0.99999f)))
  }

  val camera = PerspectiveCamera(*Program.all)

  val timeAtFirstFrame = Date().getTime()
  var timeAtLastFrame =  timeAtFirstFrame

  init{
    //LABTODO: depth test
    gl.enable(GL.DEPTH_TEST)
    addComponentsAndGatherUniforms(*Program.all)
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
  
    gameObjects.forEach { it.update() }
    gameObjects.forEach { it.draw( camera ) }
  }
}
