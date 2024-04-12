using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Input;
using Xamarin.Forms;
using Z8WK8D.Services;

namespace Z8WK8D.ViewModels
{
    public class AddItemViewModel : ViewModelBase
    {
        private string title;
        public string Title
        {
            get { return title; }
            set
            {
                title = value;
                OnPropertyChanged();
            }
        }
        private string description;
        public string Description
        {
            get { return description; }
            set
            {
                description = value;
                OnPropertyChanged();
            }
        }
        private bool done;
        public bool Done
        {
            get { return done; }
            set
            {
                done = value;
                OnPropertyChanged();
            }
        }
        public ICommand SaveItemCommand { get; }
        public AddItemViewModel(INavigation navigation) : base(navigation)
        {
            SaveItemCommand = new Command(AddItemCommandExecute);
        }
        private async void AddItemCommandExecute()
        {
            TodoService.Instance.AddItem(Title, Description, Done);
            await Navigation.PopAsync(true);
        }
    }
}
