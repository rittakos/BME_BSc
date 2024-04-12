using System;
using System.Collections.Generic;
using System.Text;

namespace ModernLangToolsApp
{ 
    class JediCouncil
    {
        //CouncilChangedDelegate tipusu event
        public event CouncilChangedDelegate CouncilChanged;

        private List<Jedi> members = new List<Jedi>();

        public int Count
        {
            get { return members.Count; }
        }

        public int CountIf(Filter filter)
        {
            int sum = 0;
            foreach (Jedi j in members)
                if (filter(j))
                    ++sum;

            return sum;
        }

        public void Add(Jedi newJedi)
        {
            members.Add(newJedi);
            if (CouncilChanged != null)
                CouncilChanged("New member added to the council.");
        }

        public void Remove()
        {
            members.RemoveAt(members.Count - 1);
            if (CouncilChanged != null)
            {
                if (members.Count > 0)
                    CouncilChanged("One member died.");
                else
                    CouncilChanged("There is no council.");
            }
        }

        private bool Beginner(Jedi jedi)
        {
            if (jedi.MidiChlorianCount < 300)
                return true;
            return false;
        }

        public List<Jedi> GetBeginners()
        {
            return members.FindAll(Beginner);
        }
    }
}
