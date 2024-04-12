using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Xamarin.Forms;
using Z8WK8D.ViewModels;

namespace Z8WK8D
{
    public partial class MainPage : ContentPage
    {
        public MainPage()
        {
            InitializeComponent();
            this.BindingContext = new MainViewModel(Navigation);
        }

        protected override void OnAppearing()
        {
            base.OnAppearing();
            (this.BindingContext as MainViewModel).OnAppearing();
        }

    }
}
