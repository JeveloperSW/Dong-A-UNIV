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

    if (!inputFile.is_open()) 
    {
        cerr << "입력 파일 'test.inp'를 열 수 없습니다." << endl;
        return 1;
    }

    if (!outputFile.is_open()) 
    {
        cerr << "출력 파일 'test.out'을 열 수 없습니다." << endl;
        return 1;
    }

    int N;
    inputFile >> N;

    vector<Person> people(N);

    // Read Data
    for (int i = 0; i < N; ++i) 
    {
        inputFile >> people[i].id >> people[i].firstName >> people[i].lastName;
    }

    // Sort by Unique Number Criteria
    sort(people.begin(), people.end(), [](const Person& a, const Person& b) 
    {
        return a.id < b.id;
    });

    // Find the longest first name length
    int maxFirstNameLength = 0;
    for (const auto& person : people) 
    {
        maxFirstNameLength = max(maxFirstNameLength, (int)person.firstName.length());
    }

    // Sorted information output
    for (const auto& person : people) 
    {
        outputFile << person.id << " "
            << left << setw(maxFirstNameLength + 1) << person.firstName
            << person.lastName << endl;
    }

    // Same Last name analysis
    map<string, vector<string>> lastNameMap;
    for (const auto& person : people) 
    {
        lastNameMap[person.lastName].push_back(person.firstName);
    }

    // Make sure you have the same Last name
    bool sameLastNameExists = false;
    for (const auto& pair : lastNameMap) 
    {
        if (pair.second.size() > 1) 
        {
            sameLastNameExists = true;
            break;
        }
    }

    if (sameLastNameExists) 
    {
        outputFile << endl;

        for (const auto& pair : lastNameMap) 
        {
            if (pair.second.size() > 1) 
            {
                outputFile << pair.first << " " << pair.second.size() << endl;
            }
        }
    }

    inputFile.close();
    outputFile.close();

    return 0;
}
