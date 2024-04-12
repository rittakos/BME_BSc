import vision.gears.webglmath.UniformProvider
import vision.gears.webglmath.Vec2
import vision.gears.webglmath.Vec3

open class Asteroid(
    val asteroidMesh : UniformProvider,
    var pos : Vec2,
    var rot: Float) : GameObject(asteroidMesh, pos){

    var rotation = rot;
    override fun move(dt: Float, t : Float,
                      keysPressed : Set <String>, gameObjects : List<GameObject>): Boolean{
      if(rotation > 0.0f){
        roll += rotation
        rotation -= 0.0001f
      }
      return true
    }
}