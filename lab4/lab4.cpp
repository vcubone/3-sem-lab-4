// lab4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <stdlib.h>

using namespace std;

struct spis
{
	int		a =0, b = 0, ves = 0;
	spis* pred = NULL;
	spis* next = NULL;
};
void	put(spis* list, int a, int b, int ves);
int		kolvo(spis* a);
void	vivod(spis* a);
int	    count(int number);
void	masvivod(int** mas, int max);
void	Del(spis* a);
void	DelAll(spis* a);


void	poisk(int** mas, int loop, int chis, int graf, int max, char* c[]);
void	zapis(int** mas, int loop, char* c[]);


int main(int argc, char* c[])
{
	setlocale(LC_ALL, "Russian");
	ifstream    vhod(c[1]);
	ofstream    vihod(c[2]);


	int start_time = clock();
	if (vhod.is_open() && vihod.is_open())
	{
		spis* list = new spis;
		spis* list2;
		string str;
		int a, b, ves;
		int max = 0;//предположу, что номера графов - числа натуральные
		while (!vhod.eof())//считывание с файла в список
		{
			for (int i = 0; i < 3; i++)
			{
				vhod >> str;
				if ((str[0] >= '0' || str[0] <= '9' || str[0] == '-') && count(atoi(str.c_str())) == str.length())
				{
					if (i == 0) a = atoi(str.c_str());
					if (i == 1) b = atoi(str.c_str());
					if (i == 2) ves = atoi(str.c_str());
				}
			}
			if (a > max)
				max = a;
			if (b > max)
				max = b;
			put(list, a, b, ves);
		}
		max++;
		vivod(list);
		cout << kolvo(list) << endl;

		int** mas = new int*[max];
		for (int i = 0; i < max; i++)
		{
			mas[i] = new int[max];
		}

		for (size_t i = 0; i < max; i++)
		{
			for (size_t j = 0; j < max; j++)
			{
				mas[i][j] = 0;
				if (i == 0)
					mas[i][j] = j;
				if (j == 0)
					mas[i][j] = i;
			}
		}

		masvivod(mas, max);


		if (kolvo(list) > 0)
		{
			list2 = list->next;

			for (size_t i = 0; i < kolvo(list); i++)
			{
				mas[list2->a][list2->b] = list2->ves;
				list2 = list2->next;
			}
		}

		
		
		masvivod(mas, max);

		for (int i = 1; i < max; i++)
		{
			poisk(mas, 0, i, i, max, c);
		}
		
	}
	else
	{
		cout << "Файл не открылся" << endl;
	}
	int end_time = clock();
	vhod.close();
	vihod.close();
}

void	poisk(int **mas, int loop, int chis, int graf, int max, char* c[])
{
	if (graf == chis && loop > 0)
	{
		zapis(mas, loop, c);
		return;
	}
	if (loop >= max)
		return;//?
	mas[loop][0] = graf;
	masvivod(mas, max);
	for (int i = 1; i < max; i++)
	{
		if (mas[graf][i] != 0)
			poisk(mas, loop + 1, chis, i, max,c);
	}
	return;
}

void	zapis(int** mas, int loop, char* c[])
{
	ofstream    vihod(c[2],ios_base::app);
	for (int i = 0; i < loop; i++)
	{
		vihod << mas[i][0] << " ";
	}
	vihod << endl;
	vihod.close();
}

void Del(spis* a)
{
	if (a->pred != NULL)
		a->pred->next = a->next;
	if (a->pred != NULL)
		a->next->pred = a->pred;
	a->next = NULL;
	a->pred = NULL;

	delete a;
}

void DelAll(spis *a)
{
	while (a->next != NULL)
		Del(a->next);
	delete a;
}


void	masvivod(int** mas, int max)
{
	for (size_t i = 0; i < max; i++)
	{
		for (size_t j = 0; j < max; j++)
		{
			cout << mas[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

int     count(int number)
{
	int count = (number == 0 || number < 0) ? 1 : 0;
	while (number != 0) {
		count++;
		number /= 10;
	}
	return count;
}

void	vivod(spis* a)
{
	while (a->next != NULL)
	{
		cout << a->a << " " << a->b << " " << a->ves << endl;
		a = a->next;
	}
	cout << a->a << " " << a->b << " " << a->ves << endl;
}
int		kolvo(spis* a)//1 элемент вводный
{
	int k = 0;
	while (a->next != NULL)
	{
		k++;
		a = a->next;
	}
	return k;
}
void	put(spis* list, int a, int b, int ves)//функции списка
{
	spis* list2 = new spis;

	list2->a = a;
	list2->b = b;
	list2->ves = ves;
	while (list->next != NULL)
	{
		list = list->next;
	}
	list->next = list2;
	list2->pred = list;
}


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
