import vision.gears.webglmath.UniformProvider
import vision.gears.webglmath.Vec2
import vision.gears.webglmath.Vec3


open class Bullet(
    val bulletMesh : UniformProvider,
    val pos : Vec2,
    var direction : Vec2) : GameObject(bulletMesh, pos){

    var velocity = 1000.0f
    var life = 100
    val slowing = velocity / life
    override fun move(dt: Float, t : Float, keysPressed : Set <String>, gameObjects : List<GameObject>): Boolean{
        if(life <= 0)
            return false
        position += direction * velocity * dt
        velocity -= slowing
        --life
        return true
    }
}