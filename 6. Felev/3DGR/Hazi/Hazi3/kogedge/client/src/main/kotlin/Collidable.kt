import vision.gears.webglmath.Vec3

interface Collidable
{
    //open fun getCurrentForce(): Vec3
    open fun collideWith(other: Car)
    //open fun getPosition() : Vec3

    //open fun setOnSurface(onSurface: Boolean)
}