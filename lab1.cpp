/*
	Дано N городов и известны расстояния между ними. Не все города связаны друг с другом дорогой. Найти все возможные маршруты из города
	A в город B (ни в один город не заходить дважды). Определить самый длинный и самый короткий маршрут.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
using namespace std;
#define MAX_WAY 10000

// Главное меню
int Menu()
{
    cout << "---------------------------------------\n";
    cout << "                 МЕНЮ                  \n";
    cout << "---------------------------------------\n";
    cout << "1 - Загрузить текст из файла.\n";
    cout << "2 - Ввести текст в консоли.\n";
    cout << "---------------------------------------\n";
    int p;
    do {
        cin >> p;
        if ((p != 1) && (p != 2))
            cout << "Введенное значение неверно. Повторите ввод.\n";
    } while ((p != 1) && (p != 2));
    getchar();
    cout << "\n";
    return p;
}

// Ответ на вопрос (txt)
bool Question(const char *txt)
{
    char ans; // Переменная, содержащая ответ на вопрос
    cout << txt << endl;
    do {
        cin >> ans;
        if ((ans != 'N') && (ans != 'n') && (ans != 'Y') && (ans != 'y'))
            cout << "Введеное значение неверно. Повторите ввод.\n";
    } while ((ans != 'N') && (ans != 'n') && (ans != 'Y') && (ans != 'y'));
    getchar();
    if ((ans == 'Y') || (ans == 'y'))
        return true; // Если ответ положительный, то вернуть функции true
    else
        return false;
}

// Объявление динамической матрицы
int **CreateMatrix(int n)
{
    int **Matrix = new int*[n];
    for (int i = 0; i < n; i++) {
        Matrix[i] = new int[n];
    }
    
    for (int i = 0; i < n; i++) {
        Matrix[i][i] = 0;
        
    }
    return Matrix;
}

// добавление эл-та в матрицу
bool AddElem(int **Matr, int a, int i, int j)
{
    if (a < 0) return false;
    Matr[i][j] = a;
    Matr[j][i] = a;
    return true;
}

// DFS алгоритм обхода в глубину: находим и выводим на экран все возможные пути,
// длину самого длинного и самого короткого маршрута
void dfs(int *used, int *way,  int **Matr, int & step, int start, int curr, int stop, int n, int & min, int & max) {
	used[curr] = 1;
	step++;
	
	if (stop == curr)
	{
		int last = start;
		int summ = 0;
		cout << "\nPath:\n ";
		for(int j = 0; j < step; j++)
		{
			cout  << "-> " << way[j]+1;
			summ += Matr[last][way[j]];
			last = way[j];
		}
		cout  << "; Len of way: " << summ;
		if (summ < min) min = summ;
		if(summ > max) max = summ;
		return;
	}
	else
	{
		for(int k = 0; k<n ; k++)
		{
			if ((used[k] == 0) && (Matr[curr][k] > 0))
			{
				way[step] = k;
				dfs(used, way, Matr, step, start, k, stop, n, min, max);
				step--;
				used[k] = 0;
			}
		}
	}
}

int main()
{
    setlocale(LC_ALL, "");
    int **Matrix;
    int SIZE;
    int m = Menu();
    switch (m) {
        case 1:
        {
            char str[32];
            cout << "Введите имя файла:\n";
            cin >> str;
            // Открытие введенного пользователем файла
            ifstream file(str);
            if (!file.good())
            {
                cout << "Не удается открыть файл.\n";
                return 0;
            }
            else
            {
                // Инициализация матрицы дорог
                file >> SIZE;
                Matrix = CreateMatrix(SIZE);
                bool ok = true;
                int i = 0, j = 0;
                while (i <SIZE - 1 && !file.eof() && ok)
                {
                    j = i + 1;
                    while (j < SIZE  && !file.eof() && ok)
                    {
                        int a;
                        file >> a;
                        ok = (AddElem(Matrix, a, i, j));
                        j++;
                    }
                    i++;
                }
                if (i < SIZE - 1)
                {
                    cout << "В файле недостаточно данных.\n" << endl;
                    ok = false;
                }
                file.close();
                if (!ok)
                {
                    return 0;
                }
            }
            break;
        }
        case 2:
        {
            // Инициализация матрицы дорог
            cout << "Введите количество городов:" << endl;
            cin >> SIZE;
            Matrix = CreateMatrix(SIZE);
            cout << "Введите длину дороги между городами, если дороги нет, введите 0:" << endl;
            for (int i = 0; i < SIZE - 1; i++)
            {
                for (int j = i + 1; j < SIZE; j++)
                {
                    int a;
                    cout << "Между " << i + 1 << " и " << j + 1 << ":" << endl;
                    do
                    {
                        cin >> a;
                    } while (!AddElem(Matrix,a,i,j));
                    
                }
            }
            break;
        }
    }
    
	// Ввод первого города
	cout << "Выберите город А [1, " << SIZE <<"]:\n";
	int start;
	do {
        cin >> start;
        if ((start < 0) && (start > SIZE))
            cout << "Введенное значение неверно. Повторите ввод.\n" << endl;
    } while ((start < 0) && (start > SIZE));
	start--;
	
	// Ввод второго города
	cout << "Выберите город Б [1, " << SIZE <<"]:\n";
	int stop;
	do {
        cin >> stop;
        if ((stop < 0) && (stop > SIZE))
            cout << "Введенное значение неверно. Повторите ввод.\n";
    } while ((stop < 0) && (stop > SIZE));
	stop--;
    
    // Вывод матрицы дорог
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cout << Matrix[i][j] << " ";
        }
        cout << endl;
    }
	

	int *used = new int[SIZE]; // Посещенные города
	int *way = new int[SIZE];  // Текущий просматриваемый маршрут
	int max = 0;               // Длина минимального пути
	int min = 9999;            // Длина максимального пути
	int step = 0;               // Текущий уровень глубины
	for(int i = 0; i< SIZE; i++)
		used[i] = 0;
	for(int i = 0; i< SIZE; i++)
		way[i] = 0;
	way[step] = start;

	dfs(used, way, Matrix, step, start, start, stop, SIZE, min, max);

	cout << "\nМакс. путь: " << max << ";\n";
	cout << "Мин. путь:  " << min << ";";




    getchar();
    getchar();
    return 0;
}