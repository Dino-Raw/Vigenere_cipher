#include <iostream>
#include <fstream>

using namespace std;

string symbols = "абвгдежзийклмнопрстуфхцчшщъыьэюя_";

int keycode(char symbol)
{
    for (int code = 0; code <= symbols.length(); code++)
        if (symbol == symbols[code])
            return code;
    return -1;
}


string encode(string text, string key)
{
    int codeKey = 0;
    int codeText = 0;
    string result = "";

    for (int indexText = 0, indexKey = 0; indexText <= text.length() - 1; indexText++, indexKey++)
    {
        if (indexKey >= key.length())
            indexKey = 0;
        
        codeText = keycode(text[indexText]);
        codeKey = keycode(key[indexKey]);

        if (codeKey == -1 || codeText == -1)
            return "";

        if (codeText + codeKey >= symbols.length())
        {
            result += symbols[codeText + codeKey - symbols.length()];
        }
        else
        {
            result += symbols[codeText + codeKey];
        }
    }
    return result;
}


string decode(string text, string key)
{
    int codeKey = 0;
    int codeText = 0;
    string result = "";

    for (int indexText = 0, indexKey = 0; indexText <= text.length() - 1; indexText++, indexKey++)
    {
        if (indexKey >= key.length())
            indexKey = 0;

        codeText = keycode(text[indexText]);
        codeKey = keycode(key[indexKey]);

        if (codeKey == -1 || codeText == -1)
            return "";

        if (codeText - codeKey < 0)
        {
            result += symbols[codeText - codeKey + symbols.length()];
        }
        else
        {
            result += symbols[codeText - codeKey];
        }
    }
    return result;
}


int main()
{
    setlocale(LC_ALL, "");

    string text = "";
    string key = "";
    
    ifstream fin("input.txt");

    if (!fin.is_open())
    {
        cout << "Нет файла для чтения" << endl;
        return 0;
    }

    fin >> text;
    fin >> key;
    fin.close();

    ofstream fout("output.txt", ios_base::trunc);

    if (text == "" || key == "" || text.length() < key.length())
    {
        cout << "Некорректный ввод." << endl;
        fout.close();
        return 0;
    }

    string code = encode(text, key);

    if (code == "")
    {
        cout << "Некорректный ввод." << endl;
        fout.close();
        return 0;
    }

    fout << code;
    fout << " ";
    fout << decode(code, key);
    fout.close();
    
    cout << "Успешно завершено." << endl;

    return 0;
}
