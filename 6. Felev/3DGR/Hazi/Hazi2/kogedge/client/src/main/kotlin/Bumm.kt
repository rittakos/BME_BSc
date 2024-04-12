import vision.gears.webglmath.UniformProvider
import vision.gears.webglmath.Vec2
import vision.gears.webglmath.Vec3

open class Bumm(
    val asteroidMesh : UniformProvider,
    var pos : Vec2) : GameObject(asteroidMesh, pos){

    var v = Vec2(0.5f, 0.5f)
    var life = 10
    val slowing = Vec2(0.1f, 0.1f)
    
    override fun move(dt: Float, t : Float,
                      keysPressed : Set <String>, gameObjects : List<GameObject>): Boolean{
        if(life <= 0)
            return false
        scale += slowing
        --life
        return true
    }
}