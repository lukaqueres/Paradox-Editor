using Editor.Visualizer;
using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Editor
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

            VisualizerApi.ShowMessageBox();
        }

        private async void upload_save_Click(object sender, RoutedEventArgs e)
        {
			OpenFileDialog fileDialog = new OpenFileDialog();
			fileDialog.DefaultExt = ".txt"; // Required file extension 
            // fileDialog.Filter = "Text documents (.txt)|*.txt"; // Optional file extensions

            if (fileDialog.ShowDialog() == true)
			{
				// System.IO.StreamReader sr = new System.IO.StreamReader(fileDialog.FileName);
				string content = await ReadTextAsync(fileDialog.FileName);
				MessageBox.Show(content);
				// sr.Close();
			}
		}


		async Task<string> ReadTextAsync(string filePath)
		{
			using var sourceStream =
				new FileStream(
					filePath,
					FileMode.Open, FileAccess.Read, FileShare.Read,
					bufferSize: 4096, useAsync: true);

			var sb = new StringBuilder();

			byte[] buffer = new byte[0x1000];
			int numRead;
			while ((numRead = await sourceStream.ReadAsync(buffer, 0, buffer.Length)) != 0)
			{
				string text = Encoding.ASCII.GetString(buffer, 0, numRead);
				sb.Append(text);
			}

			return sb.ToString();
		}
	}
}
