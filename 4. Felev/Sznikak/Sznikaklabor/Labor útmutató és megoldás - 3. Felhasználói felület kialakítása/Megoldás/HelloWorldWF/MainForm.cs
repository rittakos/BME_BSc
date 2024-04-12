using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace HelloWorldWF
{
	public partial class MainForm : Form
	{
		public MainForm()
		{
			InitializeComponent();
		}

		private void button1_Click(object sender, EventArgs e)
		{
			tbDemoText.Text = "Hello";
		}

		private void exitToolStripMenuItem_Click(object sender, EventArgs e)
		{
			Close();
		}

		private void MainForm_Load(object sender, EventArgs e)
		{
			TreeNode root = treeView1.Nodes.Add("Local Disk (C:)");
			root.Tag = new DirectoryInfo("c:\\");
			root.Nodes.Add("");

		}

		private void treeView1_BeforeExpand(object sender, TreeViewCancelEventArgs e)
		{
			DirectoryInfo parentDI = (DirectoryInfo)(e.Node.Tag);
			e.Node.Nodes.Clear();
			try
			{
				foreach (DirectoryInfo di in parentDI.GetDirectories())
				{
					TreeNode node = new TreeNode(di.Name);
					node.Tag = di;
					node.Nodes.Add("");
					e.Node.Nodes.Add(node);
				}
			}
			catch { }

		}

		private void treeView1_AfterSelect(object sender, TreeViewEventArgs e)
		{
			DirectoryInfo parentDI = (DirectoryInfo)(e.Node.Tag);
			listView1.Items.Clear();
			tbDemoText.Text = parentDI.FullName;
			try
			{
				foreach (FileInfo fi in parentDI.GetFiles())
				{
					listView1.Items.Add(new ListViewItem(new string[] { fi.Name,
						fi.Length.ToString(), fi.LastWriteTime.ToString(), fi.FullName }));
				}


			}
			catch { }

			tbDemoText.Text = parentDI.FullName;
		}

		private void listView1_DoubleClick(object sender, EventArgs e)
		{
			if (listView1.SelectedItems.Count != 1) return;
			string fullName = listView1.SelectedItems[0].SubItems[3].Text;
			if (fullName != null) Process.Start(fullName);
		}

		private void tbDemoText_TextChanged(object sender, EventArgs e)
		{

		}

		private void MainForm_DoubleClick(object sender, EventArgs e)
		{
			if (listView1.SelectedItems.Count != 1)
				return;
			string fullName = listView1.SelectedItems[0].SubItems[3].Text;
			if (fullName != null)
				Process.Start(fullName);
		}
	}
}
