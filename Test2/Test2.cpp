#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

class abonent
{
public:
    int strNum;
    string name;
    string street;
    string house;
    string flat;
    int calcType;
    float past;
    float present;
    float prise;

    void set_prise(int calcType, float past, float present)
    {
        if (calcType == 1)
        {
            prise = 301.26;
        }
        else
        {
            prise = (present - past) * 1.52;
        }
    }
};

class house
{
public:
    string street;
    string number;
    float prise;
};

int main()
{
    setlocale(LC_ALL, "Russian");
    string s;
    string path = "C:\\абоненты.csv";
    string path2 = "C:\\Начисления_абоненты.csv";
    string path3 = "C:\\Начисления_дома.csv";
    ifstream file;
    ofstream fout;
    char buf[225];
    char* tmp_char;
    char* token1 = NULL;
    char* next_token1 = NULL;


    //ЗАДАНИЕ 1
    file.open(path);
    getline(file, s);
    s = s + ";Начисленно";
    fout.open(path2, std::ios::in | std::ios::out);
    fout << s << endl;

    abonent FAbonent;
    house FHouse;
    vector<abonent> aVector;
    vector<house> hVector;

    while (getline(file, s))
    {
        strcpy_s(buf, s.c_str());
        tmp_char = strtok_s(buf, ";", &next_token1);
        FAbonent.strNum = atoi(tmp_char);
        tmp_char = strtok_s(NULL, ";", &next_token1);
        FAbonent.name = tmp_char;
        tmp_char = strtok_s(NULL, ";", &next_token1);
        FAbonent.street = tmp_char;
        tmp_char = strtok_s(NULL, ";", &next_token1);
        FAbonent.house = tmp_char;
        tmp_char = strtok_s(NULL, ";", &next_token1);
        FAbonent.flat = tmp_char;
        tmp_char = strtok_s(NULL, ";", &next_token1);
        FAbonent.calcType = atoi(tmp_char);
        tmp_char = strtok_s(NULL, ";", &next_token1);
        FAbonent.past = (float)strtod(tmp_char, NULL);
        tmp_char = strtok_s(NULL, ";", &next_token1);
        FAbonent.present = (float)strtod(tmp_char, NULL);

        FAbonent.set_prise(FAbonent.calcType, FAbonent.past, FAbonent.present);
        aVector.push_back(FAbonent);
    }
    
    for (int i = 0; i < aVector.size(); i++)
    {
        fout << aVector[i].strNum << ";" <<
        aVector[i].name << ";" <<
        aVector[i].street << ";" <<
        aVector[i].house << ";" <<
        aVector[i].flat << ";" <<
        aVector[i].calcType << ";" <<
        aVector[i].past << ";" <<
        aVector[i].present << ";" <<
        aVector[i].prise << endl;
    }

    file.close();
    fout.close();

    //ЗАДАНИЕ 2
    FHouse.street = aVector[0].street;
    FHouse.number = aVector[0].house;
    FHouse.prise = aVector[0].prise;
    hVector.push_back(FHouse);

    fout.open(path3, std::ios::in | std::ios::out);
    
    for (int i = 1; i < aVector.size(); i++)
    {
        bool houseFound = false;

        for (int j = 0; j < hVector.size(); j++)
        {
            if ((aVector[i].street == hVector[j].street) && (aVector[i].house == hVector[j].number))
            {
                hVector[j].prise = hVector[j].prise + aVector[i].prise;
                houseFound = true;
                break;
            }

        }
        if (houseFound == false)
        {
            FHouse.street = aVector[i].street;
            FHouse.number = aVector[i].house;
            FHouse.prise = aVector[i].prise;
            hVector.push_back(FHouse);
        }

    }
   
    for (int i = 0; i < hVector.size(); i++)
    {
        fout << hVector[i].street << ";" <<
                hVector[i].number << ";" <<
                hVector[i].prise << endl;

    }

    fout.close();
    return 0;
}

