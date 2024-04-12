using Dictionary.Model;
using Dictionary.Services;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

namespace Dictionary
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        //the list of the translation languages
        public ObservableCollection<string> languages { get; set; } = new ObservableCollection<string>();
        //the list of the potentian from languages
        public ObservableCollection<string> from { get; set; } = new ObservableCollection<string>();
        //the list of the potentian to languages
        public ObservableCollection<string> to { get; set; } = new ObservableCollection<string>();

        //the list of the synonym languages
        public ObservableCollection<string> synonymLanguages { get; set; } = new ObservableCollection<string>();

        //the list of the results, based on the previous events
        public ObservableCollection<ResultWord> result { get; set; } = new ObservableCollection<ResultWord>();

        //the current translation language
        Language currentLanguage;
        //the current synonym language
        string synonymLanguage;

        public MainPage()
        {
            loadLanguages(); //load the languages
            this.InitializeComponent();
            DataContext = this;
        }

        private async void loadLanguages() //load the languages
        {
            var serviceDic = new DictionaryService();
            List<string> l = await serviceDic.getLanguages(); //list of the translation languages
            from.Clear();
            to.Clear();
            foreach (string s in l)
            {
                if(!from.Contains(s.Split("-")[0]))
                    from.Add(s.Split("-")[0]);
                if (!to.Contains(s.Split("-")[1]))
                    to.Add(s.Split("-")[1]);
                languages.Add(s);
            }

            var serviceSym = new SynonymService();
            l = serviceSym.getLanguages(); //list of the synonym languages
            synonymLanguages.Clear();
            foreach (string s in l)
            {
                synonymLanguages.Add(s);
            }
        }

        private async void translate(string word) //function for the translation
        {
            //if the currentLanguage does not exist do nothing
            if (currentLanguage == null || currentLanguage.from == null || currentLanguage.to == null)
                return;
            result.Clear();
            var service = new DictionaryService();
            Word r = await service.getMeaning(word, currentLanguage.toString()); //the meanings
            foreach (var d in r.def)
                foreach(var t in d.tr)
                    result.Add(new ResultWord{text = t.text, pos = "(" + t.pos + ")"});
        }

        private async void synonyme(string word) //function for the synonym search
        {
            var service = new SynonymService();
            Synonym s =await service.getSynonyms(word, synonymLanguage); //the synonyms
            result.Clear();
            if (s.response == null) // if the response is not valid do nothing
                return;
            foreach (var r in s.response)
            {
                string cat = r.list.category;
                foreach(string w in r.list.synonyms.Split("|"))
                {
                    result.Add(new ResultWord { text = w, pos = cat });
                }
            }
        }

        private void TranslateButton_Click(object sender, RoutedEventArgs e) //event handling
        {
            translate(WordTextBox.Text);   
        }

        private void SynonymeButton_Click(object sender, RoutedEventArgs e) //event handling
        {
            synonyme(WordTextBox.Text);
        }

        private void selectionFromChanged(object sender, SelectionChangedEventArgs e) //event handling
        {
            if (currentLanguage == null)
                currentLanguage = new Language();
            currentLanguage.from = (string)(cmbfrom.SelectedItem);

            to.Clear();
            //set the possible language dor the choosen to language
            foreach(string l in languages)
            {
                if (l.Split("-")[0] == currentLanguage.from)
                    to.Add(l.Split("-")[1]);
            }
        }

        private void selectionToChanged(object sender, SelectionChangedEventArgs e) //event handling
        {
            if (currentLanguage == null)
                currentLanguage = new Language();
            currentLanguage.to = (string)(cmbto.SelectedItem);
        }

        private void selectionSynChanged(object sender, SelectionChangedEventArgs e) //event handling
        {
            synonymLanguage = (string)cmbsyn.SelectedItem;
        }
    }
}
