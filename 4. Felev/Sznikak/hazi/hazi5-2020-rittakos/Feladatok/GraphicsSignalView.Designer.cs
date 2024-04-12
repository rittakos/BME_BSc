namespace Signals
{
    partial class GraphicsSignalView
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

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.bEnlarge = new System.Windows.Forms.Button();
            this.bReduct = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // bEnlarge
            // 
            this.bEnlarge.Font = new System.Drawing.Font("Microsoft Sans Serif", 16F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.bEnlarge.Location = new System.Drawing.Point(14, 3);
            this.bEnlarge.Name = "bEnlarge";
            this.bEnlarge.Size = new System.Drawing.Size(47, 46);
            this.bEnlarge.TabIndex = 0;
            this.bEnlarge.Text = "+";
            this.bEnlarge.UseVisualStyleBackColor = true;
            this.bEnlarge.Click += new System.EventHandler(this.bEnlarge_Click);
            // 
            // bReduct
            // 
            this.bReduct.Font = new System.Drawing.Font("Microsoft Sans Serif", 16F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.bReduct.Location = new System.Drawing.Point(83, 3);
            this.bReduct.Name = "bReduct";
            this.bReduct.Size = new System.Drawing.Size(47, 46);
            this.bReduct.TabIndex = 1;
            this.bReduct.Text = "-";
            this.bReduct.UseVisualStyleBackColor = true;
            this.bReduct.Click += new System.EventHandler(this.bReduct_Click);
            // 
            // GraphicsSignalView
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.bReduct);
            this.Controls.Add(this.bEnlarge);
            this.Name = "GraphicsSignalView";
            this.Size = new System.Drawing.Size(304, 150);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button bEnlarge;
        private System.Windows.Forms.Button bReduct;
    }
}
