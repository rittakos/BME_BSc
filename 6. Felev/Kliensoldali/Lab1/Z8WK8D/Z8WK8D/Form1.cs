using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Z8WK8D
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            this.DataBindings.Add("Text", textBox1, "Text");

            this.DataBindings.Add("Width", trackBar1, "Value");
            textBox1.DataBindings.Add("Text", trackBar1, "Value");



            List<Pokemon> list = new List<Pokemon>();
            list.Add(new Pokemon { Name = "Pikachu", Weight = 13.2 });
            list.Add(new Pokemon { Name = "Mew", Weight = 8.8 });
            list.Add(new Pokemon { Name = "Charmander", Weight = 18.7 });
            list.Add(new Pokemon { Name = "Z8WK8D", Weight = 60 });
            //listBox1.DataSource = list;
            //listBox1.DisplayMember = "Name";
            pokemonBindingSource.DataSource = list;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            var list = (List<Pokemon>)pokemonBindingSource.DataSource;
            foreach (var pokemon in list)
            {
                pokemon.Weight++;
            }

        }

        private void button2_Click(object sender, EventArgs e)
        {
            ((Pokemon)pokemonBindingSource.Current).Weight *= 2;
        }
    }
}
