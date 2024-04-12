﻿using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BoatSim
{
    class Sky
    {
        BasicGeometry model;
        public Sky(GraphicsDevice dev, Texture2D tex)
        {
            model = BasicGeometry.CreateHalfSphere(dev, 15, 7,
                v => new VertexPositionTexture(v.Position,
                new Vector2(v.TextureCoordinate.X, 1 - v.TextureCoordinate.Y)));
            model.Effect.Texture = tex;
            model.Effect.LightingEnabled = false;
            model.Effect.TextureEnabled = true;
        }
        public void Draw(Camera cam)
        {
            model.Draw(Matrix.CreateScale(1000) * Matrix.CreateTranslation(cam.Position), cam.View, cam.Projection);
        }
    }
}
