using Cookbook.Models;
using Cookbook.Services;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Template10.Mvvm;
using Windows.UI.Xaml.Navigation;

namespace Cookbook.ViewModels
{
    public class DetailsPageViewModel : ViewModelBase
    {

        private string _newComment;
        public string NewComment
        {
            get { return _newComment; }
            set { Set(ref _newComment, value); }
        }

        private string _name;
        public string Name
        {
            get { return _name; }
            set { Set(ref _name, value); }
        }

        public DetailsPageViewModel()
        {
            SendCommentCommand = new DelegateCommand(SendComment);
        }
        public DelegateCommand SendCommentCommand { get; }
        private async void SendComment()
        {
            //var service = new CookbookService();
            //service.PostCommentAsync(new Dictionary<string, string>{ { "dsf", "fsdf" } });
        }

        private Recipe _recipe;
        public Recipe Recipe
        {
            get { return _recipe; }
            set { Set(ref _recipe, value); }
        }

        public override async Task OnNavigatedToAsync(
            object parameter, NavigationMode mode, IDictionary<string, object> state)
        {
            var recipeId = (int)parameter;
            var service = new CookbookService();
            Recipe = await service.GetRecipeAsync(recipeId);
            await base.OnNavigatedToAsync(parameter, mode, state);
        }
    }
}
