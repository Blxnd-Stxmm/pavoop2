#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <cmath>

using namespace std;

class SymbString
{
protected:
    string name;
    string str;

public:
    SymbString();
    SymbString(const char*, const char*);
    void Show();
    SymbString* ShiftRight(int);
    SymbString* Add(const SymbString*);
    SymbString* Div(const SymbString*);
};

class HexString : public SymbString
{
private:
    bool isHexSymbol(const char);
    int hexToInt(const char);
    char intToHex(unsigned int);

public:
    HexString();
    HexString(const char*, const char*);
    HexString* ShiftRight(int);
    HexString* Add(const HexString*);
};

class Factory
{
public:
    SymbString* CreateSymbString();
    HexString* CreateHexString();
};

void main()
{
    Factory* f = new Factory();
    SymbString* symbString1, * symbString2, * symbString3, * symbString4, * tmpss;
    HexString* hexString1, * hexString2, * hexString3, * tmphs1, * tmphs2;

    symbString1 = f->CreateSymbString();
    symbString2 = f->CreateSymbString();
    hexString1 = f->CreateHexString();
    hexString2 = f->CreateHexString();
    delete(f);

    symbString1->Show();
    symbString2->Show();
    symbString3 = symbString1->Add(symbString2);
    symbString3->Show();
    symbString4 = symbString1->Div(symbString2);
    symbString4->Show();
    delete(symbString3);
    symbString3 = NULL;
    delete(symbString4);
    symbString4 = NULL;

    hexString1->Show();
    hexString2->Show();
    hexString3 = hexString1->Add(hexString2);
    hexString3->Show();
    delete(hexString3);
    hexString3 = NULL;

    int num, arg;
    do
    {
        cin >> num;
        if (num != 0)
            cin >> arg;
        switch (num)
        {
        case 1:
            tmpss = symbString1;
            symbString1 = tmpss->ShiftRight(arg);
            delete(tmpss);
            tmpss = NULL;
            symbString1->Show();
            symbString2->Show();
            symbString3 = symbString1->Add(symbString2);
            symbString3->Show();
            symbString4 = symbString1->Div(symbString2);
            symbString4->Show();
            delete(symbString3);
            symbString3 = NULL;
            delete(symbString4);
            symbString4 = NULL;
            break;
        case 2:
            tmpss = symbString2;
            symbString2 = tmpss->ShiftRight(arg);
            delete(tmpss);
            tmpss = NULL;
            symbString1->Show();
            symbString2->Show();
            symbString3 = symbString1->Add(symbString2);
            symbString3->Show();
            symbString4 = symbString1->Div(symbString2);
            symbString4->Show();
            delete(symbString3);
            symbString3 = NULL;
            delete(symbString4);
            symbString4 = NULL;
            break;
        case 3:
            tmphs1 = hexString1->ShiftRight(arg);
            tmphs1->Show();
            hexString2->Show();
            tmphs2 = tmphs1->Add(hexString2);
            tmphs2->Show();
            delete(tmphs1);
            tmphs1 = NULL;
            delete(tmphs2);
            tmphs2 = NULL;
            break;
        case 4:
            hexString1->Show();
            tmphs1 = hexString2->ShiftRight(arg);
            tmphs1->Show();
            tmphs2 = hexString1->Add(tmphs1);
            tmphs2->Show();
            delete(tmphs1);
            tmphs1 = NULL;
            delete(tmphs2);
            tmphs2 = NULL;
            break;
        default:
            break;
        }
    } while (num != 0);
    delete(symbString1);
    delete(symbString2);
}

SymbString::SymbString() {}

SymbString::SymbString(const char* n, const char* s)
{
    name = string(n);
    str = string(s);
}

void SymbString::Show()
{
    cout << name << ' ' << str << endl;
}

SymbString* SymbString::ShiftRight(int rdist)
{
    int dist = rdist % str.size();
    string resName = "sdvig" + to_string(rdist) + ' ' + name;
    string resStr = string(str, dist) + string(str, 0, dist);
    return new SymbString(resName.c_str(), resStr.c_str());
}

SymbString* SymbString::Add(const SymbString* second)
{
    string resName = name + " + " + second->name;
    string resStr = str + second->str;
    return new SymbString(resName.c_str(), resStr.c_str());
}

SymbString* SymbString::Div(const SymbString* second)
{
    string resName = name + " - " + second->name;
    return new SymbString(resName.c_str(), str.c_str());
}

bool HexString::isHexSymbol(const char c)
{
    for (int i = 0; i < 10; i++)
        if (c == '0' + i)
            return true;
    for (int i = 0; i < 6; i++)
        if (c == 'a' + i)
            return true;

    return false;
}

HexString::HexString() {}

HexString::HexString(const char* n, const char* s)
{
    name = string(n);
    for (int i = 0; i < (int)strlen(s); i++)
        if (!isHexSymbol(s[i])) return;

    str = string(s);
}

HexString* HexString::ShiftRight(int rdist)
{
    int dist = rdist % str.size();
    string resName = "sdvig" + to_string(rdist) + ' ' + name;
    string resStr = string(str, dist) + string(str, 0, dist);
    return new HexString(resName.c_str(), resStr.c_str());
}

char HexString::intToHex(unsigned int val)
{
    string hex = "0123456789abcdef";
    if (val > 15) return 'E';

    return hex[val];
}

int HexString::hexToInt(const char c)
{
    string hex = "0123456789abcdef";
    for (int i = 0; i < 16; i++)
        if (c == hex[i]) return i;

    return -1;
}

HexString* HexString::Add(const HexString* second)
{
    string resName = name + " + " + second->name;
    string resStr;

    unsigned long long secondVal = 0;
    unsigned long long thisVal = 0;
    unsigned long long resVal;

    unsigned int l1 = str.size();
    unsigned int l2 = second->str.size();

    for (int i = l1 - 1; i >= 0; i--) {
        thisVal += hexToInt(str[i]) * pow(16, l1 - i - 1);
    }

    for (int i = l2 - 1; i >= 0; i--) {
        secondVal += hexToInt(second->str[i]) * pow(16, l2 - i - 1);
    }

    resVal = thisVal + secondVal;

    stringstream ss;
    ss << hex << resVal;

    ss >> resStr;
    return new HexString(resName.c_str(), resStr.c_str());
}

SymbString* Factory::CreateSymbString()
{
    string name, str;
    cin >> name >> str;
    SymbString* res = new SymbString(name.c_str(), str.c_str());
    return res;
}

HexString* Factory::CreateHexString()
{
    string name, str;
    cin >> name >> str;
    HexString* res = new HexString(name.c_str(), str.c_str());
    return res;
}