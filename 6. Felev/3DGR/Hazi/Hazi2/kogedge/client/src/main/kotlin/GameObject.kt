import vision.gears.webglmath.UniformProvider
import vision.gears.webglmath.Vec2
import vision.gears.webglmath.Vec3
import vision.gears.webglmath.Mat4
import kotlin.math.exp
import kotlin.math.PI
import kotlin.math.floor

open class GameObject(
  val mesh : UniformProvider,
  val position : Vec2 = Vec2.zeros.clone(),
  var roll : Float = 0.0f,
  val scale : Vec2 = Vec2.ones.clone()
   ) : UniformProvider("gameObject"){

  val modelMatrix by Mat4()

  init { 
    addComponentsAndGatherUniforms(mesh)
  }

  fun update() {
    modelMatrix.set().rotate(roll).scale(scale).translate(position)
  }

  open fun collide(collideWith: GameObject) : Boolean{
    //println((position - collideWith.position).length())
    if((position - collideWith.position).length() < 1.0f)
      return true
    return false
  }

  open fun move(dt: Float = 0.0166666f, t : Float = 0.0f,
                    keysPressed : Set <String> = emptySet<String>(), 
                    gameObjects : List<GameObject> = emptyList<GameObject>()): Boolean{
    return true
  }

}
