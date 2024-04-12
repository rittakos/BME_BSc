namespace MultiThreadedApp
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.pTarget = new System.Windows.Forms.Panel();
            this.bBike1 = new System.Windows.Forms.Button();
            this.bStart = new System.Windows.Forms.Button();
            this.bBike3 = new System.Windows.Forms.Button();
            this.bBike2 = new System.Windows.Forms.Button();
            this.bStep1 = new System.Windows.Forms.Button();
            this.pStart = new System.Windows.Forms.Panel();
            this.pRest = new System.Windows.Forms.Panel();
            this.bStep2 = new System.Windows.Forms.Button();
            this.bPixels = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // pTarget
            // 
            this.pTarget.BackColor = System.Drawing.Color.LightSteelBlue;
            this.pTarget.Location = new System.Drawing.Point(613, 12);
            this.pTarget.Name = "pTarget";
            this.pTarget.Size = new System.Drawing.Size(164, 249);
            this.pTarget.TabIndex = 0;
            // 
            // bBike1
            // 
            this.bBike1.Font = new System.Drawing.Font("Webdings", 32F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(2)));
            this.bBike1.Location = new System.Drawing.Point(27, 101);
            this.bBike1.Name = "bBike1";
            this.bBike1.Size = new System.Drawing.Size(114, 64);
            this.bBike1.TabIndex = 1;
            this.bBike1.Text = "b";
            this.bBike1.UseVisualStyleBackColor = true;
            this.bBike1.Click += new System.EventHandler(this.bike_Click);
            // 
            // bStart
            // 
            this.bStart.Location = new System.Drawing.Point(27, 286);
            this.bStart.Name = "bStart";
            this.bStart.Size = new System.Drawing.Size(114, 40);
            this.bStart.TabIndex = 2;
            this.bStart.Text = "Start";
            this.bStart.UseVisualStyleBackColor = true;
            this.bStart.Click += new System.EventHandler(this.bStart_Click);
            // 
            // bBike3
            // 
            this.bBike3.Font = new System.Drawing.Font("Webdings", 32F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(2)));
            this.bBike3.Location = new System.Drawing.Point(27, 171);
            this.bBike3.Name = "bBike3";
            this.bBike3.Size = new System.Drawing.Size(114, 63);
            this.bBike3.TabIndex = 3;
            this.bBike3.Text = "b";
            this.bBike3.UseVisualStyleBackColor = true;
            this.bBike3.Click += new System.EventHandler(this.bike_Click);
            // 
            // bBike2
            // 
            this.bBike2.Font = new System.Drawing.Font("Webdings", 32F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(2)));
            this.bBike2.Location = new System.Drawing.Point(27, 32);
            this.bBike2.Name = "bBike2";
            this.bBike2.Size = new System.Drawing.Size(114, 63);
            this.bBike2.TabIndex = 4;
            this.bBike2.Text = "b";
            this.bBike2.UseVisualStyleBackColor = true;
            this.bBike2.Click += new System.EventHandler(this.bike_Click);
            // 
            // bStep1
            // 
            this.bStep1.Location = new System.Drawing.Point(215, 286);
            this.bStep1.Name = "bStep1";
            this.bStep1.Size = new System.Drawing.Size(93, 40);
            this.bStep1.TabIndex = 5;
            this.bStep1.Text = "Step1";
            this.bStep1.UseVisualStyleBackColor = true;
            this.bStep1.Click += new System.EventHandler(this.bStep1_Click);
            // 
            // pStart
            // 
            this.pStart.BackColor = System.Drawing.Color.SlateGray;
            this.pStart.Location = new System.Drawing.Point(189, 12);
            this.pStart.Name = "pStart";
            this.pStart.Size = new System.Drawing.Size(146, 249);
            this.pStart.TabIndex = 6;
            // 
            // pRest
            // 
            this.pRest.BackColor = System.Drawing.Color.SteelBlue;
            this.pRest.Location = new System.Drawing.Point(395, 12);
            this.pRest.Name = "pRest";
            this.pRest.Size = new System.Drawing.Size(164, 249);
            this.pRest.TabIndex = 7;
            // 
            // bStep2
            // 
            this.bStep2.Location = new System.Drawing.Point(419, 286);
            this.bStep2.Name = "bStep2";
            this.bStep2.Size = new System.Drawing.Size(108, 40);
            this.bStep2.TabIndex = 8;
            this.bStep2.Text = "Step2";
            this.bStep2.UseVisualStyleBackColor = true;
            this.bStep2.Click += new System.EventHandler(this.bStep2_Click);
            // 
            // bPixels
            // 
            this.bPixels.Location = new System.Drawing.Point(649, 286);
            this.bPixels.Name = "bPixels";
            this.bPixels.Size = new System.Drawing.Size(94, 40);
            this.bPixels.TabIndex = 10;
            this.bPixels.UseVisualStyleBackColor = true;
            this.bPixels.Click += new System.EventHandler(this.bPixels_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 344);
            this.Controls.Add(this.bPixels);
            this.Controls.Add(this.bStep2);
            this.Controls.Add(this.bStep1);
            this.Controls.Add(this.bBike2);
            this.Controls.Add(this.bBike3);
            this.Controls.Add(this.bStart);
            this.Controls.Add(this.bBike1);
            this.Controls.Add(this.pTarget);
            this.Controls.Add(this.pStart);
            this.Controls.Add(this.pRest);
            this.Name = "Form1";
            this.Text = "Tour de France";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel pTarget;
        private System.Windows.Forms.Button bBike1;
        private System.Windows.Forms.Button bStart;
        private System.Windows.Forms.Button bBike3;
        private System.Windows.Forms.Button bBike2;
        private System.Windows.Forms.Button bStep1;
        private System.Windows.Forms.Panel pStart;
        private System.Windows.Forms.Panel pRest;
        private System.Windows.Forms.Button bStep2;
        private System.Windows.Forms.Button bPixels;
    }
}

