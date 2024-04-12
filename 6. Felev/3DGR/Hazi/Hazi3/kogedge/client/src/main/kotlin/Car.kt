import vision.gears.webglmath.UniformProvider
import vision.gears.webglmath.Vec2
import vision.gears.webglmath.Vec3
import vision.gears.webglmath.Drawable
import org.khronos.webgl.WebGLRenderingContext as GL



open class Car(
    val gl : WebGL2RenderingContext,
    var carPosition : Vec3 = Vec3(),
    var r : Float = 0.0f,
    val s : Vec3 = Vec3.ones.clone(),
    var force: Vec3 = Vec3()){

    var direction = Vec3(0.0f, 0.0f, 1.0f)
    
    val g = Vec3(0.0f, -10.0f, 0.0f) //gravity
    val sumMass = 1200.0f
    val wheelR = 1.0f
    var v = Vec3()
    
    inner class FrontWheel(
    m: UniformProvider,
    val l : Vec3,
    val p : Vec3 = Vec3.zeros.clone(),
    var r : Float = 0.0f,
    val s : Vec3 = Vec3.ones.clone()) :GameObject(m, p, r, s)
    {
        val m = 50.0f
        override fun move(dt: Float, t : Float, keysPressed : Set <String>, gameObjects : List<GameObject>): Boolean{
            yaw = 0.0f
            
            if("LEFT" in keysPressed)
                yaw += 0.5f
            if("RIGHT" in keysPressed)
                yaw -= 0.5f
            //carYaw = yaw
            position = carPosition + l
            pitch += 1.0f * ds.z / wheelR
            return true
        }
    }
    
    inner class BackWheel(
        m: UniformProvider,
        val l : Vec3,
        val p : Vec3 = Vec3.zeros.clone(),
        var r : Float = 0.0f,
        val s : Vec3 = Vec3.ones.clone()):GameObject(m, p, r, s)
    {
        val m = 50.0f
        override fun move(dt: Float, t : Float, keysPressed : Set <String>, gameObjects : List<GameObject>): Boolean{
            position = carPosition + l
            //yaw = carYaw
            rotationAxis = Vec3(1.0f, 0.0f, 0.0f)
            pitch += 1.0f * ds.z / wheelR
            return true
        }
    }
    
    inner class Body(
        m: UniformProvider,
        val p : Vec3 = Vec3.zeros.clone(),
        var r : Float = 0.0f,
        val s : Vec3 = Vec3.ones.clone()):GameObject(m, p, r, s)
    {
        val m = 1000.0f
        override fun move(dt: Float, t : Float, keysPressed : Set <String>, gameObjects : List<GameObject>): Boolean{ 
            position = carPosition
            //yaw = carYaw
            //carPosition = position
            //v = ds * dt
            //println(v)
            return true
        }
    }

    var carPitch = 0.0f
    var carYaw = 0.0f

    val vsTrafo = Shader(gl, GL.VERTEX_SHADER, "trafo-vs.glsl")
    val fsTextured = Shader(gl, GL.FRAGMENT_SHADER, "textured-fs.glsl")  
    val texturedProgram = Program(gl, vsTrafo, fsTextured)
    
    val carMaterial = Material(texturedProgram)
    val parts = ArrayList<GameObject>()

    var onSurface = false
    var falling = true
    var lastJumped = 0.0f
    var ds : Vec3 = Vec3()

    fun setOnSurface(onSurface: Boolean)
    {
        this.onSurface = onSurface
    }

    fun setFalling(falling: Boolean)
    {
        this.falling = falling
    }

    init{
        force = Vec3(0.0f, -12000.0f, 0.0f)

        carMaterial["colorTexture"]?.set(
        Texture2D(gl, "media/json/chevy/chevy.png"))
        carMaterial["texOffset"]?.set(0.1f, 0.4f)

        parts.add(Body(MultiMesh(arrayOf(carMaterial), load(gl, "media/json/chevy/chassis.json")), carPosition))
        parts.add(BackWheel(MultiMesh(arrayOf(carMaterial), load(gl, "media/json/chevy/wheel.json")), Vec3(-7.5f, -3.0f, -11.0f), carPosition + Vec3(-7.5f, -3.0f, -11.0f)))
        parts.add(BackWheel(MultiMesh(arrayOf(carMaterial), load(gl, "media/json/chevy/wheel.json")), Vec3(7.5f, -3.0f, -11.0f), carPosition + Vec3(7.5f, -3.0f, -11.0f)))
        parts.add(FrontWheel(MultiMesh(arrayOf(carMaterial), load(gl, "media/json/chevy/wheel.json")), Vec3(-7.5f, -3.0f, 14.0f), carPosition + Vec3(-7.5f, -3.0f, 14.0f)))
        parts.add(FrontWheel(MultiMesh(arrayOf(carMaterial), load(gl, "media/json/chevy/wheel.json")), Vec3(7.5f, -3.0f, 14.0f), carPosition + Vec3(7.5f, -3.0f, 14.0f)))
    }
    
    fun getPosition() : Vec3
    {
        return carPosition
    }

    val jumpForce = 500000.0f

    fun move(t: Float, dt : Float, keysPressed : Set <String>, gameObjects : List<GameObject>): Boolean
    {
        force = Vec3(0.0f, -12000.0f, 0.0f)
        //println(t)
        //println(onSurface)
        if(!falling)
        {
            if("UP" in keysPressed)
                force = force + Vec3(0.0f, 0.0f, 100000.0f)
            // if("DOWN" in keysPressed)
            //     force = force + Vec3(0.0f, 0.0f, -100000.0f)
            if("LEFT" in keysPressed)
                force = force + Vec3(50000.0f, 0.0f, 0.0f)
            if("RIGHT" in keysPressed)
                force = force + Vec3(-50000.0f, 0.0f, 0.0f)
            if("SHIFT" in keysPressed)
            {
                v = v - Vec3(v.x, 0.0f, v.z) * 0.1f
            }
            if("SPACE" in keysPressed && (t - lastJumped) > 1.0f)
            {
                //println("jump")
                onSurface = false
                lastJumped = t
                carPosition.y = 5.6f
                force = force + Vec3(0.0f, jumpForce, 0.0f)
            }
        }

        gameObjects.forEach {
            it.collideWith(this)
        }

        (force.z < -0.001f)
            force.z = force.z + 10.0f
        (force.z > 0.001f)
            force.z = force.z - 10.0f

        if(force.y > 0)
            force.y = force.y - 100.0f
        if(force.y < 0.001f && force.y > -0.001f && !onSurface)
            force.y = -10.0f * sumMass

        if(onSurface)
        {
            force.y = 0.0f
            v.y = 0.0f
            carPosition.y = 5.5f
        }

        v = v - Vec3(v.x, 0.0f, v.z) * 0.05f

        //ds = ((force / (2 * sumMass)) * t * t) - ((force / (2 * sumMass)) * (t - dt) * (t - dt))
        var x = force / (2 * sumMass) * dt * dt
        ds = (v + v + x / dt) * dt / 2.0f
        //println(dt)
        //println(force.y)
        //println(ds.y)
        carPosition = carPosition + ds
        v = v + x / dt

        //println(force.y)
        var res = true
        parts.forEach { if(it.move(dt, t, keysPressed, gameObjects) == false) res = false}
        return res
    }

    fun update()
    {
        parts.forEach { it.update() }
    }

    fun draw(uniformProviders : PerspectiveCamera)
    {
        parts.forEach { it.draw( uniformProviders ) }
    }

    fun getCurrentForce() : Vec3{
        return force
    }
}