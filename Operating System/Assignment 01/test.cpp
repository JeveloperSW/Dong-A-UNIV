#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <map>
#include <iomanip>

using namespace std;

struct Person 
{
    int id;
    string firstName;
    string lastName;
};

int main() 
{
    ifstream inputFile("test.inp");
    ofstream outputFile("test.out");

    if (!inputFile || !outputFile) 
    {
        cerr << "Could not open file" << endl;
        return 1;
    }

    int N;
    inputFile >> N;
    vector<Person> people(N);

    for (auto& person : people) 
    {
        inputFile >> person.id >> person.firstName >> person.lastName;
    }

    sort(people.begin(), people.end(), [](const Person& a, const Person& b))
    {
        return a.id < b.id;
    };

    size_t maxFirstLen = 0;
    for (const auto& p : people)
        maxFirstLen = max(maxFirstLen, p.firstName.size());

    for (const auto& p : people) 
    {
        outputFile << p.id << " "
                   << left << setw(static_cast<int>(maxFirstLen + 1)) << p.firstName
                   << p.lastName << endl;
    }

    map<string, vector<string>> lastNameMap;
    for (const auto& p : people)
        lastNameMap[p.lastName].push_back(p.firstName);

    bool hasDuplicates = any_of(lastNameMap.begin(), lastNameMap.end(), [](const auto& pair) { return pair.second.size() > 1; });

    if (hasDuplicates) 
    {
        outputFile << endl;
        for (const auto& [last, firsts] : lastNameMap) 
        {
            if (firsts.size() > 1)
                outputFile << last << " " << firsts.size() << endl;
        }
    }

    return 0;
}
