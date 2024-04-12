using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BoatSim
{
    class Island
    {
        VertexBuffer vertexBuffer;
        IndexBuffer indexBuffer;
        BasicEffect effect;
        public Island(GraphicsDevice dev, Texture2D tex, Texture2D heightMapTex)
        {

            //vertexbuffer
            int w = heightMapTex.Width;
            int h = heightMapTex.Height;
            uint[] hm = new uint[w * h];
            var vbData = new VertexPositionTexture[hm.Length];

            heightMapTex.GetData(hm);

            for (int i = 0; i < hm.Length; i++)
            {
                float height = (hm[i] & 255) / 255.0f;
                int x = i % w;
                int y = i / w;
                var pos = new Vector3(x / (float)(w - 1), height, y / (float)(h - 1));
                vbData[i] = new VertexPositionTexture(pos, new Vector2(pos.X, pos.Z));
            }

            vertexBuffer = new VertexBuffer(dev, VertexPositionTexture.VertexDeclaration, vbData.Length, BufferUsage.WriteOnly);
            vertexBuffer.SetData(vbData);


            //indexbuffer
            var indices = new ushort[(h - 1) * (w * 2 + 1)];
            int idx = 0;
            int dir = 1;

            for (int j = 1; j < w; j++)
            {
                int i = dir > 0 ? 0 : w - 1;
                for (; i >= 0 && i < w; i += dir)
                {
                    indices[idx++] = (ushort)(j * w + i);
                    indices[idx++] = (ushort)((j - 1) * w + i);
                }

                indices[idx++] = (ushort)((j) * w + i - dir);
                dir = -dir;
            }

            indexBuffer = new IndexBuffer(dev, typeof(ushort), indices.Length, BufferUsage.WriteOnly);
            indexBuffer.SetData(indices);


            //effect
            effect = new BasicEffect(dev);
            effect.Texture = tex;
            effect.TextureEnabled = true;
        }        public void Draw(Matrix world, Camera cam)
        {
            var dev = vertexBuffer.GraphicsDevice;
            dev.SetVertexBuffer(vertexBuffer);
            dev.Indices = indexBuffer;
            effect.World = world;
            effect.View = cam.View;
            effect.Projection = cam.Projection;
            effect.CurrentTechnique.Passes[0].Apply();
            dev.DrawIndexedPrimitives(PrimitiveType.TriangleStrip, 0, 0, indexBuffer.IndexCount - 2);
        }    }
}
