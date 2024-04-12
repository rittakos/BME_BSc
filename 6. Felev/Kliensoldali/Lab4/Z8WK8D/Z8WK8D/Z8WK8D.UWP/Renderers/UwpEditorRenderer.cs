using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Xamarin.Forms;
using Xamarin.Forms.Platform.UWP;
using Z8WK8D.Renderers;
using Z8WK8D.UWP.Renderers;

[assembly: ExportRenderer(typeof(CustomEditor), typeof(UwpEditorRenderer))]
namespace Z8WK8D.UWP.Renderers //névteret javítani
{
    public class UwpEditorRenderer : EditorRenderer
    {
        protected override void OnElementChanged(ElementChangedEventArgs<Editor> e)
        {
            base.OnElementChanged(e);
            if (Control != null)
            {
                Control.BorderThickness = new Windows.UI.Xaml.Thickness(1);
            }
        }
    }
}