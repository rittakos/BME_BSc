using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Input;
using Xamarin.Forms;
using Z8WK8D.Models;
using Z8WK8D.Services;

namespace Z8WK8D.ViewModels
{
    public class MainViewModel : ViewModelBase
    {
        public List<TodoItem> Items => TodoService.Instance.GetAll();
        public ICommand AddItemCommand { get; }
        public MainViewModel(INavigation navigation) : base(navigation)
        {
            AddItemCommand = new Command(AddItemCommandExecute);
        }
        private async void AddItemCommandExecute()
        {
            await Navigation.PushAsync(new AddItemPage(), true);
        }
        public override void OnAppearing()
        {
            base.OnAppearing();
            OnPropertyChanged(nameof(Items));
        }
    }

}
