#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;



template <typename T>
void InputCorrectNumber(T& var)
{
    cin >> var;
    while (cin.fail() || cin.peek() != '\n' || var <= 0)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Ошибка! Пожалуйста введите корректное значение: ";
        cin >> var;
    }
};



struct Pipe
{
    string pipename = "";
    double pipelength = 0;
    int pipediameter = 0;
    bool piperepair = 0;

};

int AddPipe(Pipe& pipe) {
    if ((pipe.pipename != ""))
    {

        cout << "У вас уже есть труба\n\n";
        return 1;
    }



    cout << "Введите название трубы: ";
    cin.ignore();
    getline(cin, pipe.pipename);
    cout << "Введите длину трубы: ";
    InputCorrectNumber(pipe.pipelength);

    cout << "Введите диаметр трубы: ";
    InputCorrectNumber(pipe.pipediameter);
    cout << "Находится ли труба сейчас в ремонте?? (1 - Да, 0 - Нет) ";
    InputCorrectNumber(pipe.piperepair);

}



int ChangeRepair(Pipe& pipe)
{

    if (pipe.pipelength != 0)
    {
        pipe.piperepair = 0;
        cout << "Находится ли труба сейчас в ремонте?? (1 - Да, 0 - Нет) ";
        InputCorrectNumber(pipe.piperepair);

    }
    else
    {

        cout << "У вас нет трубы\n\n";
    }
    return 1;
};

struct CS
{
    string csname = "";
    int csworkshop = 0;
    int csworkshop_in_active = 0;
    double cseffective = 0;

};
int AddCS(CS& cs)
{
    if ((cs.csname != ""))
    {
        cout << "У вас уже есть компрессорная станция \n\n";

    }
    else
    {
        cout << "Введите название компрессорной станции: ";
        cin.ignore();
        getline(cin, cs.csname);
        cout << "Введите количество цехов: ";
        InputCorrectNumber(cs.csworkshop);

        cout << "Введите количество цехов в работе: ";
        InputCorrectNumber(cs.csworkshop_in_active);
        while (!((cs.csworkshop) >= (cs.csworkshop_in_active)))
        {

            cout << "Количество активных цехов не должно превышать количество всех цехов\n\n";
            cout << "Введите корректное значение: ";
            InputCorrectNumber(cs.csworkshop_in_active);
        }

        if (cs.csworkshop != 0)
        {
            cs.cseffective = double(cs.csworkshop_in_active) / double(cs.csworkshop);
        }
    }
    return 1;
};



int ChangeCS(CS& cs)
{

    if (cs.csname == "")
    {
        cout << "Создайте компрессорную станцию \n\n";

    }
    else
    {

        cout << "Введите количество цехов: ";
        InputCorrectNumber(cs.csworkshop);

        cout << "Введите количество цехов в работе: ";
        InputCorrectNumber(cs.csworkshop_in_active);
        while (((cs.csworkshop) < (cs.csworkshop_in_active)))
        {

            cout << "Количество активных цехов не должно превышать количество всех цехов\n\n";
            cout << "Введите корректное значение: ";
            InputCorrectNumber(cs.csworkshop_in_active);
        }
    }

    cs.cseffective = double(cs.csworkshop_in_active) / double(cs.csworkshop);
    return  1;
};

void show_Pipe(const Pipe& p)//!!!
{
    if (p.pipelength == 0)
    {

        cout << "Создайте свою первую трубу\n\n";

    }

    else
    {

        cout << "------ТРУБА------" <<
            "\nНазвание: " << p.pipename <<
            "\nДлина: " << p.pipelength <<
            "\nДиаметр: " << p.pipediameter <<
            "\nНаходится в ремонте? (1 - Да, 0 - Нет) " << p.piperepair <<
            "\n--------------------\n\n";

    }
};

void show_CS(const CS& cs)//!!!
{
    if (cs.csname == "")
    {

        cout << "Создайте свою первую кс\n\n";

    }
    else
    {
        cout << "------КС------" <<
            "\nНазвание: " << cs.csname <<
            "\nКоличество цехов: " << cs.csworkshop <<
            "\nКоличество цехов в работе: " << cs.csworkshop_in_active <<
            "\nЭффективность: " << cs.cseffective <<
            "\n--------------------\n\n";

    }
};

void Save_Pipe(ofstream& fout, const Pipe& pipe)//!!
{

    string Marker = "Pipeline";

    if (pipe.pipename == "") fout << Marker << endl;

    else
    {

        fout << (pipe.pipename) << endl;

        fout << pipe.pipelength << endl;

        fout << pipe.pipediameter << endl;

        fout << pipe.piperepair << endl;
    }

}

void Save_CS(ofstream& fout, const CS& cs)//!!
{

    string Marker = "CS";
    if (cs.csname == "") fout << Marker << endl;

    else {


        fout << cs.csname << endl;
        fout << cs.csworkshop << endl;
        fout << cs.csworkshop_in_active << endl;
        fout << cs.cseffective << endl;
    }

}

Pipe Load_Pipe(ifstream& fin, Pipe& pipe)
{

    string Marker;
    getline(fin >> ws, Marker);
    if (Marker == "Pipeline")
    {
        return pipe = { "", 0, 0, 0 };
    }

    else
    {
        pipe.pipename = Marker;
        fin >> pipe.pipelength;
        fin >> pipe.pipediameter;
        fin >> pipe.piperepair;
        return pipe;
    }

}

CS Load_CS(ifstream& fin, CS& cs)
{

    string Marker;
    getline(fin >> ws, Marker);

    if (Marker == "CS")
    {
        return cs = { "", 0, 0 };
    }

    else
    {
        cs.csname = Marker;
        fin >> cs.csworkshop;
        fin >> cs.csworkshop_in_active;
        cs.cseffective = double(cs.csworkshop_in_active) / double(cs.csworkshop);
        return cs;

    }

}


int main()
{

    setlocale(LC_ALL, "Russian");
    Pipe pipeline;
    CS cs;

    int chose;

    do
    {

        cout << "------МЕНЮ------\n";
        cout << "1. Показать все объекты\n";
        cout << "2. Добавить трубу\n";
        cout << "3. Изменить состояние ремонта\n";
        cout << "4. Добавить КС\n";
        cout << "5. Изменить количество рабочих цехов\n";
        cout << "6. Cохранить в файл\n";
        cout << "7. Взять данные из файла\n";
        cout << "8. Выйти из программы\n";
        cout << "----------------\n";

        cout << "\nВыбор действия: ";

        InputCorrectNumber(chose);


        switch (chose)
        {
        case 1:
            show_Pipe(pipeline);
            show_CS(cs);
            break;


        case 2:
            AddPipe(pipeline);
            break;

        case 3:
            ChangeRepair(pipeline);
            break;

        case 4:
            AddCS(cs);
            break;

        case 5:
            ChangeCS(cs);
            break;


        case 6:
        {
            ofstream fout("save.txt");
            if (fout.is_open())
            {
                Save_Pipe(fout, pipeline);
                Save_CS(fout, cs);
            }

            else
            {
                cout << "Файл не открывается" << endl;
            }
            break;
        }



        case 7:
        {
            ifstream fin("save.txt");
            if (fin.is_open())
            {
                pipeline = Load_Pipe(fin, pipeline);
                cs = Load_CS(fin, cs);
                fin.close();
            }
            else
            {
                cout << "Файл не открывается" << endl;
            }
            break;
        }

        case 8:
            cout << "До новых встреч!" << endl;
            return 0;


        default:
            system("cls");
            cout << "Такого пункта нет в меню\n\n";
            break;
        }

    } while (chose != 0);
    return 0;
}
