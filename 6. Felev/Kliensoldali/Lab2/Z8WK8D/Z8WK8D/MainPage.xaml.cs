using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Popups;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;
using Z8WK8D.Model;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

namespace Z8WK8D
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        public Person NewPerson { get; set; }
        public ObservableCollection<Person> People { get; set; }


        public MainPage()
        {
            this.InitializeComponent();

            NewPerson = new Person()
            {
                Name = "Eric Cartman",
                Age = 8
            };

            People = new ObservableCollection<Person>()
            {
                new Person() { Name = "Peter Griffin", Age = 40 },
                new Person() { Name = "Homer Simpson", Age = 42 }
            };


            //DataContext = NewPerson;
            DataContext = this;

        }

        private void PeopleListView_ItemClick(object sender, ItemClickEventArgs e)
        {
            var person = (Person)e.ClickedItem;
            new MessageDialog($"Név: {person.Name}, Életkor: {person.Age}").ShowAsync();
        }

        private void RecordButton_Click(object sender, RoutedEventArgs e)
        {
            //RecordTextBlock.Text = "Recording...";
            People.Add(new Person {Name = NewPerson.Name, Age = NewPerson.Age });
        }

        private void DecreaseButton_Click(object sender, RoutedEventArgs e)
        {
            --NewPerson.Age;
        }

        private void IncreaseButton_Click(object sender, RoutedEventArgs e)
        {
            ++NewPerson.Age;
        }
    }
}
