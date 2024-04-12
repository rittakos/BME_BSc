using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BoatSim
{
    class Boat
    {
        Model model;
        Matrix localTransform = Matrix.CreateScale(0.3f) * Matrix.CreateTranslation(0, -0.1f, 0);
        public Matrix WorldTransform = Matrix.Identity;
        public Boat(GraphicsDevice dev, Model model)
        {
            this.model = model;
        }
        float rot;
        public void Draw(Camera cam)
        {
            int idx = 0;
            foreach (var mesh in model.Meshes)
            {
                if(idx++ > 3)
                    break;
                if (idx == 4)
                    rot -= 0.2f;
                float d = 0.37f;
                var propRot = idx == 4 ? (Matrix.CreateTranslation(0, d, 0) * Matrix.CreateRotationZ(rot) * Matrix.CreateTranslation(0, d, 0)) : Matrix.Identity;
                
                foreach (BasicEffect effect in mesh.Effects)
                {
                    effect.EnableDefaultLighting();
                    effect.PreferPerPixelLighting = true;
                    effect.World = propRot * localTransform * WorldTransform;
                    effect.View = cam.View;
                    effect.Projection = cam.Projection;
                }
                mesh.Draw();
            }

            //model.Draw(localTransform * WorldTransform, cam.View, cam.Projection);
        }
    }
}
