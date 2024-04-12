import vision.gears.webglmath.Geometry
import vision.gears.webglmath.UniformProvider

class MultiMesh(
  materials : Array<Material>,
  geometries : Array<Geometry>
  ) : UniformProvider("multiMesh") {

  init {
    if(materials.size != geometries.size){
      throw Error("MultiMesh has ${geometries.size} geometries, but ${materials.size} materials were provided.")
    }
    val submeshes = Array<Mesh>(geometries.size) {
      i -> Mesh(materials[i], geometries[i])
    }
    addComponentsAndGatherUniforms(*submeshes)    
  }
}
