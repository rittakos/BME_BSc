using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;

namespace BoatSim
{
	/// <summary>
	/// This is the main type for your game.
	/// </summary>
	public class Game1 : Game
	{
		GraphicsDeviceManager graphics;
		SpriteBatch spriteBatch;
        BasicGeometry cube;
        Sky sky;
        Boat boat;
        Island island;
        Water water;
        private float rot = 1.2f;

        public Game1( )
		{
			graphics = new GraphicsDeviceManager( this );
			Content.RootDirectory = "Content";
		}

		/// <summary>
		/// Allows the game to perform any initialization it needs to before starting to run.
		/// This is where it can query for any required services and load any non-graphic
		/// related content.  Calling base.Initialize will enumerate through any components
		/// and initialize them as well.
		/// </summary>
		protected override void Initialize( )
		{
            // TODO: Add your initialization logic here

            IsMouseVisible = true;

            Window.AllowUserResizing = true;
            this.Window.ClientSizeChanged += (s, e) => 
            {
                this.graphics.PreferredBackBufferWidth = this.Window.ClientBounds.Width;
                this.graphics.PreferredBackBufferHeight = this.Window.ClientBounds.Height;
                graphics.ApplyChanges();
            };

            base.Initialize( );
		}

		/// <summary>
		/// LoadContent will be called once per game and is the place to load
		/// all of your content.
		/// </summary>
		protected override void LoadContent( )
		{
			// Create a new SpriteBatch, which can be used to draw textures.
			spriteBatch = new SpriteBatch( GraphicsDevice );


            cube = BasicGeometry.CreateCube(GraphicsDevice);
            sky = new Sky(GraphicsDevice, Content.Load<Texture2D>("skyhalf"));
            boat = new Boat(GraphicsDevice, Content.Load<Model>("boat"));
            island = new Island(GraphicsDevice, Content.Load<Texture2D>("islandColor"), Content.Load<Texture2D>("islandHeight"));
            water = new Water(GraphicsDevice, null);
        }

		/// <summary>
		/// UnloadContent will be called once per game and is the place to unload
		/// game-specific content.
		/// </summary>
		protected override void UnloadContent( )
		{
			// TODO: Unload any non ContentManager content here
		}

		/// <summary>
		/// Allows the game to run logic such as updating the world,
		/// checking for collisions, gathering input, and playing audio.
		/// </summary>
		/// <param name="gameTime">Provides a snapshot of timing values.</param>
		protected override void Update( GameTime gameTime )
		{
			if ( GamePad.GetState( PlayerIndex.One ).Buttons.Back == ButtonState.Pressed || Keyboard.GetState( ).IsKeyDown( Keys.Escape ) )
				Exit( );

			// TODO: Add your update logic here

			base.Update( gameTime );
		}

		/// <summary>
		/// This is called when the game should draw itself.
		/// </summary>
		/// <param name="gameTime">Provides a snapshot of timing values.</param>
		protected override void Draw( GameTime gameTime )
		{
			GraphicsDevice.Clear( Color.FromNonPremultiplied(new Vector4(0.2f, 0.4f, 0.6f, 1)));
            //GraphicsDevice.Clear(Color.Purple);

            //Camera.Main.AspectRatio = GraphicsDevice.Viewport.AspectRatio;
            //cube.Draw(Matrix.Identity, Camera.Main.View, Camera.Main.Projection);

            Camera.Main.AspectRatio = GraphicsDevice.Viewport.AspectRatio;
            Camera.Main.Position = Vector3.Transform(new Vector3(3, 1, 0), Matrix.CreateRotationY(rot += 0.01f));
            Camera.Main.Direction = -Vector3.Normalize(Camera.Main.Position);

            boat.Draw(Camera.Main);
            sky.Draw(Camera.Main);
            foreach (var m in new Matrix[]{
                Matrix.CreateScale( 50, 10, 50 )* Matrix.CreateTranslation( 100, -0.5f, 0 ),
                Matrix.CreateScale( 100, 20, 100 ) * Matrix.CreateTranslation( -50, -1, 70 ),
                Matrix.CreateScale( 70, 15, 70 ) * Matrix.CreateTranslation( -50, -0.75f, -70 )})
            {
                island.Draw(m, Camera.Main);
            }
            water.Draw(Camera.Main);
            //cube.Draw(Matrix.Identity, Camera.Main.View, Camera.Main.Projection);

            //GraphicsDevice.Clear(Color.Purple);
            base.Draw( gameTime );
		}
	}
}
