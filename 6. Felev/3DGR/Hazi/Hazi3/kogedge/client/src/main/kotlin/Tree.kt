import vision.gears.webglmath.UniformProvider
import vision.gears.webglmath.Vec3
import vision.gears.webglmath.Mat4
import vision.gears.webglmath.Vec3Array
import kotlin.math.abs

open class Tree(
    val gl : UniformProvider,
    var p : Vec3 = Vec3(),
    var r : Float = 0.0f,
    val s : Vec3 = Vec3.ones.clone()): GameObject(gl, p, r, s), Collidable{

    override fun move(dt: Float, t : Float, keysPressed : Set <String>, gameObjects : List<GameObject>): Boolean{
        return true
    }

    override fun collideWith(other: Car){
        if(abs(other.getPosition().x - this.position.x) < 10.0f
            && abs(other.getPosition().z - this.position.z) < 10.0f) 
        {
            other.getCurrentForce().x = -other.getCurrentForce().x * 100.0f//= other.getCurrentForce()// - 2.0f * other.getCurrentForce()
            other.getCurrentForce().z = -other.getCurrentForce().z * 200.0f
        }
    }
}