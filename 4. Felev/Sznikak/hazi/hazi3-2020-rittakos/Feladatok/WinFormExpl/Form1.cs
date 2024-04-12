using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;
using System.IO;

namespace WinFormExpl
{
    public partial class Form1 : Form
    {
        private FileInfo loadedFile;
        int counter;
        readonly int counterInitialValue;
        public Form1()
        {
            InitializeComponent();
            counterInitialValue = 4 * 10;
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            InputDialog inputDialog = new InputDialog();
            listView1.Items.Clear();

            if (inputDialog.ShowDialog() == DialogResult.OK)
            {
                string result = inputDialog.Path;
                DirectoryInfo info = new DirectoryInfo(result);
                try
                {
                    foreach (FileInfo fi in info.GetFiles())
                    {
                        listView1.Items.Add(new ListViewItem(new string[] { fi.Name,
                        fi.Length.ToString(), fi.FullName}));
                    }


                }
                catch { }
                //MessageBox.Show(result);
            }
        }

        private void listView1_DoubleClick(object sender, EventArgs e)
        {
            if (listView1.SelectedItems.Count != 1) return;

            reloadTimer.Start();
            counter = counterInitialValue;
            loadedFile = new FileInfo(listView1.SelectedItems[0].SubItems[2].Text);

            tContent.Text = File.ReadAllText(loadedFile.FullName);
        }

        private void listView1_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (listView1.SelectedItems.Count != 1) return;
            FileInfo info = new FileInfo(listView1.SelectedItems[0].SubItems[2].Text);
            lName.Text = info.Name;
            lCreated.Text = info.CreationTime.ToString();
        }

        private void reloadTimer_Tick(object sender, EventArgs e)
        {
            --counter;
            detailsPanel.Invalidate();

            if(counter <= 0)
            {
                counter = counterInitialValue;
                tContent.Text = File.ReadAllText(loadedFile.FullName);
            }
        }

        private void detailsPanel_Paint(object sender, PaintEventArgs e)
        {
            if (loadedFile != null)
                e.Graphics.FillRectangle(new SolidBrush(Color.Green), new Rectangle(0, 0, 3 * counter, 5));
        }
    }
}
