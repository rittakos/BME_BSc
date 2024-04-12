import vision.gears.webglmath.UniformProvider
import vision.gears.webglmath.Vec3
import vision.gears.webglmath.Mat4
import vision.gears.webglmath.Vec3Array


open class GameObject(
  mesh : UniformProvider,
  var position : Vec3 = Vec3.zeros.clone(),
  var roll : Float = 0.0f,
  val scale : Vec3 = Vec3.ones.clone(),
  var rotationAxis: Vec3 = Vec3(1.0f, 0.0f, 0.0f)
   ) : UniformProvider("gameObject"), Collidable {

  val modelMatrix by Mat4()
  val rotationMatrix by Mat4()

  var pitch = 0.0f
  var yaw = 0.0f

  init { 
    addComponentsAndGatherUniforms(mesh)
  }

  fun update() {
    rotationMatrix.set(). 
      rotate(roll).
      rotate(pitch, 1.0f, 0.0f, 0.0f).
      rotate(yaw, 0.0f, 1.0f, 0.0f)
    // viewProjMatrix.set(rotationMatrix).
    //   translate(position).
    //   invert()

    modelMatrix.set(rotationMatrix).
  	 	scale(scale).
  	  translate(position)
  	// modelMatrix.set().
  	// 	scale(scale).
  	// 	rotate(roll, rotationAxis).
  	// 	translate(position)
  }

  open fun move(
      dt : Float = 0.016666f,
      t : Float = 0.0f,
      keysPressed : Set<String> = emptySet<String>(),
      gameObjects : List<GameObject> = emptyList<GameObject>() ) : Boolean {
    return true;
  }

  override open fun collideWith(other: Car){
      
  }
}


