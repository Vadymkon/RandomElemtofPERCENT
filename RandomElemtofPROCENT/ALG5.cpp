#include <iostream> //cin,cout
#include <chrono> //для "хроно" штуки, которая в последствии будет в сиде
#include <random> //для функций рандома
#include <string> //стринги на word замени просто потом
#include <vector>

using namespace std; //миллион раз не писать

void printMATRIX(int rows, string* arr)
{
	//выводим массив
	cout << endl; //отступ
		for (int i = 0; i < rows; i++) //каждый элемент строки
		{
			cout << arr[i] << " "; //вывод
		}
		cout << endl; //отступ
}

void fill_arr(int startpoint, int indexOf_elem, string *&arr, string elems[], int procents[], int rows)
{
	if (startpoint < rows)
	{
		for (int i = 0; i < procents[indexOf_elem]; i++)
		{
			arr[i+startpoint] = elems[indexOf_elem];
		}
		fill_arr(startpoint + procents[indexOf_elem], indexOf_elem + 1, arr, elems, procents, rows);
	}
	else return;
}

string randelem(string colors[], double percents[], int sizer)
{

	int max = 1; //поиск максимального ко-ва знаков после запятой
	for (int i = 0; i < sizer; i++)
	{
		// 0.00700000
	//так как количество символов ДО КОМЫ всегда равно 1, то мы просто поиск начинаем со второго символа 
		string str = to_string(percents[i]);
		str.erase(0, 1); str.erase(0, 1); //убиарем 2 символа в начале
		// "00700000"
		int index_of_start = 0;
		for (int j = 0; j < str.size(); j++)
		{
			if (str[j] != '0') index_of_start = j;
		}
		//"007_00000"
		int counter_of_zero = 0; //считалка "нулей" от 
		for (int j = 0; j < str.size() - index_of_start; j++)
		{
			if (str[str.size() - 1 - j] == '0') // если элемент от конца это 0
			{
				counter_of_zero++; //количество нулей злесь ++
			}
		}

		if (max < to_string(percents[i]).size() - 2 - counter_of_zero) max = to_string(percents[i]).size() - 2 - counter_of_zero; // тогда максимум это новое количество знаков после запятой
	}

	//max - это максимальное количество знаков после запятой 
	int *  percents_but_int = new int[sizer]; //сотворим более понятный массив с процентами только в интовом значении
	for (int i = 0; i < sizer; i++)
	{
		percents_but_int[i] = _cvt_dtoi_sat(percents[i] * pow(10, max));
	}
	int rows = pow(10, max); //считаем количество нужных мест для контейнереса
	string* arr = new string[rows];  //создание контейнера

	//определение рандома
	unsigned seed = chrono::system_clock::now().time_since_epoch().count(); //формировка сида, с помощью времени хроно
	default_random_engine generator(seed); //обозначение генератора
	uniform_int_distribution<int> distribution(1, rows); //определение границ и функции вызова


	//заполнение массива
	fill_arr(0, 0, arr, colors, percents_but_int, rows);

	// printMATRIX(rows, arr);

	///вывод результативного случайного элемента
		int n = distribution(generator); //определение рандомного номера
		cout << endl << "printed element index " << n << " is = " << arr[n] << endl;
	
	
	string result = arr[n];

	//delete чистим память
	delete[] arr; //очистка главного массива
	delete[] percents_but_int; //очистка вспомогательного

	return result;
}


int main()
{
	//создаём динамический массив

	string colors [] { "Blue", "Red", "Green", "Yellow" };
	double percents [] { 1,21,532,232,34};
	
	double sum = 0;
	for (int i = 0; i < size(percents); i++)
	{
		sum += percents[i];
	}
	for (int i = 0; i < size(percents); i++)
	{
		percents[i] = percents[i] / sum;
	}
	sum = 0;
	for (int i = 0; i < size(percents); i++)
	{
		sum += percents[i];
	}
	cout << sum;
	return(0);
	randelem(colors, percents, size(colors));
}

