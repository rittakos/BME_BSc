import vision.gears.webglmath.UniformProvider
import vision.gears.webglmath.Vec3
import vision.gears.webglmath.Mat4
import vision.gears.webglmath.Vec3Array

open class Hole(
    val gl : UniformProvider,
    var p : Vec3 = Vec3(),
    var r : Float = 0.0f,
    val s : Vec3 = Vec3.ones.clone()): GameObject(gl, p, r, s), Collidable{

    override fun move(dt: Float, t : Float, keysPressed : Set <String>, gameObjects : List<GameObject>): Boolean{
        return true
    }

    override fun collideWith(other: Car){
        if((other.getPosition() - this.position + Vec3(3.0f, 3.0f)).length() < 10.0f && other.onSurface && other.carPosition.y > this.position.y) 
        {
            other.setOnSurface(false)
            other.setFalling(true)
        }
    }
}