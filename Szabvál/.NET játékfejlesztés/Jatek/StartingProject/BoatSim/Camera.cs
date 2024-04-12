﻿using Microsoft.Xna.Framework;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BoatSim
{
    class Camera
    {
        public Vector3 Position = new Vector3(5, 2, 3);
        public Vector3 Direction = new Vector3(-5, -2, -3);
        public Vector3 Up = Vector3.Up;
        public float AspectRatio = 1;
        public Matrix View => Matrix.CreateLookAt(Position, Position + Direction, Up);
        public Matrix Projection => Matrix.CreatePerspectiveFieldOfView(1, AspectRatio, 1, 1010);
        public static readonly Camera Main = new Camera();
    }
}
