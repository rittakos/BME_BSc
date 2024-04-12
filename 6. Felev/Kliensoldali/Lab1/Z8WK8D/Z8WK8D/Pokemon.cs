using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Z8WK8D
{
    class Pokemon: INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;
        private double weight;
        public double Weight
        {
            get { return weight; }
            set
            {
                weight = value;
                if (PropertyChanged != null)
                    PropertyChanged(this,
                    new PropertyChangedEventArgs("Weight"));
            }
        }

        public string Name { get; set; }
    }
}
