/*
	���� N ������� � �������� ���������� ����� ����. �� ��� ������ ������� ���� � ������ �������. ����� ��� ��������� �������� �� ������
	A � ����� B (�� � ���� ����� �� �������� ������). ���������� ����� ������� � ����� �������� �������.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
using namespace std;
#define MAX_WAY 10000

// ������� ����
int Menu()
{
    cout << "---------------------------------------\n";
    cout << "                 ����                  \n";
    cout << "---------------------------------------\n";
    cout << "1 - ��������� ����� �� �����.\n";
    cout << "2 - ������ ����� � �������.\n";
    cout << "---------------------------------------\n";
    int p;
    do {
        cin >> p;
        if ((p != 1) && (p != 2))
            cout << "��������� �������� �������. ��������� ����.\n";
    } while ((p != 1) && (p != 2));
    getchar();
    cout << "\n";
    return p;
}

// ����� �� ������ (txt)
bool Question(const char *txt)
{
    char ans; // ����������, ���������� ����� �� ������
    cout << txt << endl;
    do {
        cin >> ans;
        if ((ans != 'N') && (ans != 'n') && (ans != 'Y') && (ans != 'y'))
            cout << "�������� �������� �������. ��������� ����.\n";
    } while ((ans != 'N') && (ans != 'n') && (ans != 'Y') && (ans != 'y'));
    getchar();
    if ((ans == 'Y') || (ans == 'y'))
        return true; // ���� ����� �������������, �� ������� ������� true
    else
        return false;
}

// ���������� ������������ �������
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

// ���������� ��-�� � �������
bool AddElem(int **Matr, int a, int i, int j)
{
    if (a < 0) return false;
    Matr[i][j] = a;
    Matr[j][i] = a;
    return true;
}

// DFS �������� ������ � �������: ������� � ������� �� ����� ��� ��������� ����,
// ����� ������ �������� � ������ ��������� ��������
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
            cout << "������� ��� �����:\n";
            cin >> str;
            // �������� ���������� ������������� �����
            ifstream file(str);
            if (!file.good())
            {
                cout << "�� ������� ������� ����.\n";
                return 0;
            }
            else
            {
                // ������������� ������� �����
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
                    cout << "� ����� ������������ ������.\n" << endl;
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
            // ������������� ������� �����
            cout << "������� ���������� �������:" << endl;
            cin >> SIZE;
            Matrix = CreateMatrix(SIZE);
            cout << "������� ����� ������ ����� ��������, ���� ������ ���, ������� 0:" << endl;
            for (int i = 0; i < SIZE - 1; i++)
            {
                for (int j = i + 1; j < SIZE; j++)
                {
                    int a;
                    cout << "����� " << i + 1 << " � " << j + 1 << ":" << endl;
                    do
                    {
                        cin >> a;
                    } while (!AddElem(Matrix,a,i,j));
                    
                }
            }
            break;
        }
    }
    
	// ���� ������� ������
	cout << "�������� ����� � [1, " << SIZE <<"]:\n";
	int start;
	do {
        cin >> start;
        if ((start < 0) && (start > SIZE))
            cout << "��������� �������� �������. ��������� ����.\n" << endl;
    } while ((start < 0) && (start > SIZE));
	start--;
	
	// ���� ������� ������
	cout << "�������� ����� � [1, " << SIZE <<"]:\n";
	int stop;
	do {
        cin >> stop;
        if ((stop < 0) && (stop > SIZE))
            cout << "��������� �������� �������. ��������� ����.\n";
    } while ((stop < 0) && (stop > SIZE));
	stop--;
    
    // ����� ������� �����
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cout << Matrix[i][j] << " ";
        }
        cout << endl;
    }
	

	int *used = new int[SIZE]; // ���������� ������
	int *way = new int[SIZE];  // ������� ��������������� �������
	int max = 0;               // ����� ������������ ����
	int min = 9999;            // ����� ������������� ����
	int step = 0;               // ������� ������� �������
	for(int i = 0; i< SIZE; i++)
		used[i] = 0;
	for(int i = 0; i< SIZE; i++)
		way[i] = 0;
	way[step] = start;

	dfs(used, way, Matrix, step, start, start, stop, SIZE, min, max);

	cout << "\n����. ����: " << max << ";\n";
	cout << "���. ����:  " << min << ";";




    getchar();
    getchar();
    return 0;
}