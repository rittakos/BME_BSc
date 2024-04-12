#include <map>
#include <string>
#include <iostream>
#include <vector>
#include<fstream>
#include <set>
#include <algorithm>

void Feladat1()
{
    std::map<std::string, int> m;
    std::string s;
    while (std::cin >> s)
        ++m[s];

    std::map<int, std::vector<std::string>> m2;
    for (auto i : m)
    {
        int key = i.second;
        m2[key].push_back(i.first);
    }

    for (auto p : m2)
    {
        std::cout << p.first << " ";
        for(auto s : p.second)
            std::cout << s << " ";
        std::cout << std::endl;
    }
}

void Feladat2()
{
    //Time es Date structokat hasonlit ossze a < operatoruk segitsegevel
    //ugy, hogy a {} segitsegevel vannak ertekkel letrehozva, a vegen kiirja az
    //osszehasonlitas eredmenyet
}

void Feladat3()
{
    std::ifstream input;
    input.open("santa.txt");

    std::set<std::pair<int, int>> beenHere;

    char command;
    std::pair<int, int> coord = { 0, 0 };

    beenHere.insert(coord);
    int numOfDiferentHouses = 1;

    while (input >> command)
    {
        switch(command)
        {
            case '^':
                ++coord.second;
                break;
            case 'v':
                --coord.second;
                break;
            case '>':
                ++coord.first;
                break;
            case '<':
                --coord.first;
                break;
        }
        if (beenHere.find(coord) == beenHere.end())
        {
            ++numOfDiferentHouses;
            beenHere.insert(coord);
        }
    }
    std::cout << numOfDiferentHouses << std::endl;
}

void Feladat4()
{
    std::ifstream input;
    input.open("santa.txt");

    std::map<std::pair<int, int>, int> presents;

    char command;
    std::pair<int, int> coord = { 0, 0 };
    ++presents[coord];

    while (input >> command)
    {
        
        switch (command)
        {
        case '^':
            ++coord.second;
            break;
        case 'v':
            --coord.second;
            break;
        case '>':
            ++coord.first;
            break;
        case '<':
            --coord.first;
            break;
        }
        
        ++presents[coord];
    }

    auto result = std::max_element(presents.begin(), presents.end(),
        [](const std::pair<std::pair<int, int>, int>& p1, const std::pair<std::pair<int, int>, int>& p2) {
        return p1.second < p2.second; });

    std::cout << result->second << '\t' << result->first.first << ", " << result->first.second << std::endl;
}

int main()
{
	//Feladat1();
    //Feladat3();
    Feladat4();
}