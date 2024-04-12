import org.w3c.dom.HTMLCanvasElement
import org.khronos.webgl.WebGLRenderingContext as GL
import org.khronos.webgl.Float32Array
import vision.gears.webglmath.UniformProvider
import vision.gears.webglmath.Vec3
import vision.gears.webglmath.Vec4
import vision.gears.webglmath.Mat4
import kotlin.math.cos
import kotlin.math.sin
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

  val fsEnvMapped = Shader(gl, GL.FRAGMENT_SHADER, "envmapped-fs.glsl")
  val envmappedProgram = Program(gl, vsTrafo, fsEnvMapped)

  val fsMaxblinn = Shader(gl, GL.FRAGMENT_SHADER, "maxblinn-fs.glsl")
  val maxblinnProgram = Program(gl, vsTrafo, fsMaxblinn)

  val vsQuad = Shader(gl, GL.VERTEX_SHADER, "quad-vs.glsl")
  //val fsPostProc = Shader(gl, GL.FRAGMENT_SHADER, "postproc-fs.glsl")
  //val postProcProgram = Program(gl, vsQuad, fsPostProc)

  val envTexture = TextureCube(gl, 
  "media/sky/posx512.jpg",
  "media/sky/negx512.jpg",
  "media/sky/posy512.jpg",
  "media/sky/negy512.jpg",
  "media/sky/posz512.jpg",
  "media/sky/negz512.jpg"
  )

  val skyCubeTexture =
  TextureCube(gl, 
    "media/sky/posx512.jpg", "media/sky/negx512.jpg",
    "media/sky/posy512.jpg", "media/sky/negy512.jpg",
    "media/sky/posz512.jpg", "media/sky/negz512.jpg"
    )

  lateinit var defaultFramebuffer : DefaultFramebuffer  
  lateinit var postProcFramebuffer : Framebuffer



  val quadGeometry = TexturedQuadGeometry(gl)
  val flipQuadGeometry = FlipQuadGeometry(gl)

  val material1 = Material(maxblinnProgram)
  val material2 = Material(maxblinnProgram)
  val backgroundMaterial = Material(boxProgram)
  val envmappedMaterial = Material(envmappedProgram)
  //val postProcMaterial = Material(postProcProgram)

  val lights = Array<Light>(3) { Light(it, *Program.all) }


  val gameObjects = ArrayList<GameObject>()
  init{
    material1["colorTexture"]?.set(
    Texture2D(gl, "media/slowpoke/YadonDh.png"))
    material1["texOffset"]?.set(0.1f, 0.4f)

    material2["colorTexture"]?.set(
    Texture2D(gl, "media/slowpoke/YadonEyeDh.png"))
    material2["texOffset"]?.set(0.1f, 0.4f)

    backgroundMaterial["envTexture"]?.set(envTexture)
    envmappedMaterial["envmapTexture"]?.set(skyCubeTexture)
    

    lights[0].position.set(1.0f, 1.0f, 1.0f, 0.0f).normalize();
    lights[0].powerDensity.set(1.0f, 1.0f, 0.0f);

    lights[1].position.set(-1.0f, 1.0f, 1.0f, 0.0f).normalize();
    lights[1].powerDensity.set(1.0f, 0.0f, 1.0f);

    lights[2].position.set(0.0f, 1.0f, 0.0f, 0.0f).normalize();
    lights[2].powerDensity.set(1.0f, 1.0f, 1.0f);


    //LABTODO: add object from JSON
    gameObjects.add(GameObject(MultiMesh(arrayOf(material1, material2), load(gl, "media/slowpoke/Slowpoke.json"))))
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

    defaultFramebuffer = DefaultFramebuffer(canvas.width, canvas.height)
    postProcFramebuffer = Framebuffer(gl, 1, canvas.width, canvas.height)
    //postProcMaterial["rawTexture"]?.set(postProcFramebuffer.targets[0] )
  }

  @Suppress("UNUSED_PARAMETER")
  fun update(gl : WebGL2RenderingContext, keysPressed : Set<String>) {

    val timeAtThisFrame = Date().getTime() 
    val dt = (timeAtThisFrame - timeAtLastFrame).toFloat() / 1000.0f
    val t  = (timeAtThisFrame - timeAtFirstFrame).toFloat() / 1000.0f    
    timeAtLastFrame = timeAtThisFrame

    //LABTODO: move camera
    camera.move(dt, keysPressed)

    // gl.uniform3fv(
    //   gl.getUniformLocation(envmappedProgram.glProgram, "camera.position"), camera.position.storage)

    val x = lights[2].position.x*cos(0.01f)-lights[2].position.y*sin(0.01f)
    val y = lights[2].position.x*sin(0.01f)+lights[2].position.y*cos(0.01f)
    lights[2].position = Vec4(x, y, 0.0f, 0.0f)

    // clear the screen
    gl.clearColor(0.3f, 0.0f, 0.3f, 1.0f)
    gl.clearDepth(1.0f)
    gl.clear(GL.COLOR_BUFFER_BIT or GL.DEPTH_BUFFER_BIT)

    gl.enable(GL.BLEND)
    gl.blendFunc( GL.SRC_ALPHA, GL.ONE_MINUS_SRC_ALPHA)

    gameObjects.forEach { it.move(t, dt, keysPressed, gameObjects) }
  
    gameObjects.forEach { it.update() }
    gameObjects.forEach { it.draw( camera, *lights) }
  }
}
