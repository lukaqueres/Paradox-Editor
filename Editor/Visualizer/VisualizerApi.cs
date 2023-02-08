using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace Editor.Visualizer
{
    public class VisualizerApi
    {
        [DllImport("VisualizerDLL.dll")]
        public static extern void ShowMessageBox();
    }
}
