#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>

#define MAIN_MENU_MAX_CHOOSE 5

bool up_flag = 0, down_flag = 0, enter_flag = 0;//ЧТО БЛЯЦ ЗА ФЛАГИ
bool Up_Now = 0, Down_Now = 0, Enter_Now = 0; //КАКИЕ ЕЩЕ НАВЫ
int pointer = 1; //аналог choice нужен для позиции стрелочки
int trains = 0, screen_now = 0;
bool exit_display_address = 0;//ДА СККА МОЖНА БЛЛЛЛ


using namespace std;

void Display_Main_Menu(); //выводит текст менюшки без стрелки
void New_Screen(); //обновлят экран 
void Clear_Cin(); //очищвет всеь ввод cin'а
void Up_Or_Down_Button(); //отработка нажатий без залипаний
void Delete_Last_Pointer(int, int); //такаяж хня но для уаления
void Enter_Button(); // отработка ENTER без залипаний
void Creat_New_Pointer(int, int); // создание стрелочки (принимается место стрелочки и макс ее значение)
void Display_Pointer(); // отобразить стрелочку выбора
void Up_Or_Down_Logic(int); //логика смены стрелочки

string Get_Number();
string Cin_Time();//ввода времени

//void Change_Class(int); //метод для изменения объектов

double Get_Value(); //считывает введенные данные(надо будет)
string Get_Punk();

class Train
{
private:
	string Time;
	string number;
	string Punk_Vidachi;
	int Hours;
	int Minutes;
public:
	Train();
	Train(string number, string Punk_Vidachi, int Hours, int Minutes);
	~Train();

	//Train(const Train &obj);
	void Display_Info(); // прототип функции вывода данных по объекту
	void Change_Number(string number) { this->number = number; } //изменеие номера поезда
	void Change_Punk_Vidachi(string Punk_Vidachi) { this->Punk_Vidachi = Punk_Vidachi; } //изменеие ширины
	void Change_Time(string Time) { this->Time = Time; } //изменеие
	void Show_Time() {
		int H = 0, M = 0;
		if (Hours < 10 && Minutes < 10) {
			cout << H << Hours << ':' << M << Minutes;
		} 
		else if (H < 0) {
			cout << H << Hours << ':' << Minutes;
		}
		else {
			cout  << Hours << ':' << M << Minutes;
		}
	}

	string Display_Element(string); //для вывод конкретного поля
	//void Save_To_File(const string& filename, int);
};

vector<Train> vec_trains;
//vector<Train> vec_for_saving;

void Swap_Elements(Train&, Train&);//проосто свап
int Partition_Vector(vector<Train>&, int, int);//разбиение массива на меньше/больше опрного элема
void Quick_Sort(vector<Train>&, int, int);//само тело квик сорта передаем массив(вектор) и гарницы L|R

Train::Train() { //конструктор по умолчанию
	this->number = "";
	this->Punk_Vidachi = "";
	this->Hours = -1;
	this->Minutes = -1;
}
Train::Train(string number, string Punk_Vidachi, int Hours, int Minutes) { //конструктор с параметрами
	this->number = number;
	this->Punk_Vidachi = Punk_Vidachi;
	this->Hours = Hours;
	this->Minutes = Minutes;
}

Train::~Train()  //диструктор , но он тут не нужен
{

}


void Train::Display_Info() {
	cout << "[номер: " << number << ", пункт назначения: " << Punk_Vidachi << ", время прибытия: " << Time << " ]";
	//Show_Time();
	//cout << " ]";
}

string Train::Display_Element(string type = "0") {
	if (type == "number") {
		return number;
	}
	else if (type == "Punk_Vidachi") {
		return Punk_Vidachi;
	}
	else if (type == "Time") {
		return Time;
	}
	else {
		cout << "Error (!-!)";
		return "";
	}
}

int main()
{
	SetConsoleCP(1251); // Устанавливаем кодировку ввода (CP1251) нужно для кодировки клавиш
	SetConsoleOutputCP(1251); // Устанавливаем кодировку вывода для кореекстоывып (кароч для русского)
	setlocale(LC_ALL, "rus");
	Display_Main_Menu(); //главное меню без стрелки
	Creat_New_Pointer(pointer, MAIN_MENU_MAX_CHOOSE); //создаем стрелочку по ее месту
	bool exit = 0;
	while (!exit) { //работаем пока exit не станет 1 -> !exit = 0
		Up_Or_Down_Logic(MAIN_MENU_MAX_CHOOSE);
		Enter_Button();
		if (Enter_Now == 1) {
			Enter_Now = 0;
			switch (pointer) {
			case 1: { // добавить данные по коробке(создание)
				New_Screen();
				Clear_Cin();

				vec_trains.resize(trains + 1); //создаем вектор 
				string input; //временная переменная для класса
				cout << "Введите номер поезда: ";
				input = Get_Number();
				vec_trains[trains].Change_Number(input);
				cout << "Введите пункт назначения: ";
				input = Get_Punk();
				vec_trains[trains].Change_Punk_Vidachi(input);
				cout << "Введите время прибытия: ";
				input = Cin_Time();
				vec_trains[trains].Change_Time(input);

				trains++;
				New_Screen();
				Display_Main_Menu();
				Creat_New_Pointer(pointer, MAIN_MENU_MAX_CHOOSE);
				break;
			}
			case 2: { //поиск по пункту (бывш.изменение данных)
				New_Screen();
				Clear_Cin();
				cout << "Введите пункт назначения: " << flush;
			

				int count = 0;
				
				cin.ignore();
				string input; //временная переменная для класса
				input = Get_Punk();
				
				New_Screen();

				cout << "   Вы ввели: [" << input << "]" << endl; 

				for (int i = 0; i < vec_trains.size(); i++) {
					if (input == vec_trains[i].Display_Element("Punk_Vidachi")) {
						cout << "   ";
						vec_trains[i].Display_Info();
						cout << endl;
						count++;
					}
				}
				cout << "   [Назад]\n";
				if (count == 0) {
					Delete_Last_Pointer(pointer, count + 1);
					New_Screen();
					cout << "   Нет совпадений :(" << endl;
					cout << "   [Назад]\n";
					pointer = 1;
					Creat_New_Pointer(pointer, count + 1);
				}
				else {

				}
				exit_display_address = 0;
				while (!exit_display_address) {//для простора имеющихся коробочек (^-^)
					Up_Or_Down_Logic(trains + 1); //бо проходимся по списку + 1 для выхода
					Enter_Button();
					if (Enter_Now == 1) {
						Enter_Now = 0;
						if (pointer == trains + 1) {//если выбрали кнопку выхода
							exit_display_address = 1;
							pointer = 1;
						}
					}
				}
				New_Screen();
				Display_Main_Menu();
				Creat_New_Pointer(pointer, MAIN_MENU_MAX_CHOOSE);
				break;
			}
			case 3: {//вывод данных
				New_Screen();
				for (int i = 0; i < trains; i++) {//вывод инфы
					cout << "   ";
					vec_trains[i].Display_Info();
					cout << endl;
				}
				if (trains == 0) { cout << " Нет данных :(\n"; }
				cout << "   [Назад]\n";
				pointer = 1;
				Creat_New_Pointer(pointer, trains + 1);
				exit_display_address = 0;
				while (!exit_display_address) {//для простора имеющихся коробочек (^-^)
					Up_Or_Down_Logic(trains + 1); //бо проходимся по списку + 1 для выхода
					Enter_Button();
					if (Enter_Now == 1) {
						Enter_Now = 0;
						if (pointer == trains + 1) {//если выбрали кнопку выхода
							exit_display_address = 1;
							pointer = 1;
						}
					}
				}
				New_Screen();
				Display_Main_Menu();
				Creat_New_Pointer(pointer, MAIN_MENU_MAX_CHOOSE);
				break;
			}
			case 4: { //сортировка (бывш. запись в файл)
				New_Screen();
				if (trains == 0) {
					cout << "   Нет данных для сортировки :(\n";
				}
				else {
					Quick_Sort(vec_trains, 0, trains - 1); // Сортируем весь вектор
					cout << "   Данные отсортированы по пункту назначения:\n";
					for (int i = 0; i < trains; i++) {
						cout << "   ";
						vec_trains[i].Display_Info();
						cout << endl;
					}
				}
				cout << "   [Назад]\n";
				pointer = 1;
				Creat_New_Pointer(pointer, trains + 1);

				exit_display_address = 0;
				while (!exit_display_address) {
					Up_Or_Down_Logic(trains + 1); // Логика для кнопки "Назад"
					Enter_Button();
					if (Enter_Now == 1) {
						Enter_Now = 0;
						if (pointer == trains + 1) { // Выход
							exit_display_address = 1;
							pointer = 1;
						}
					}
				}
				New_Screen();
				Display_Main_Menu();
				Creat_New_Pointer(pointer, MAIN_MENU_MAX_CHOOSE);
				break;
				//выход обратно
				break;
			}
			case 5: {//Exit
				exit = 1;
				break;
			}
			default:
				break;
			}
		}
	}
	return 0;
}


void Display_Main_Menu() {
	cout << "   [Заполнить данны по поездам]" << endl << "   [Поиск по пункту]" << endl << "   [Вывести информацию]" << endl << "   [Отсортировать]" << endl << "   [Выйти]\n";
}

void Up_Or_Down_Button() {
	if (GetAsyncKeyState(VK_UP) != 0 && up_flag == 0) {//проверка нажаьа ли через асинк и сосотояние до этого через флаг
		up_flag = 1;
		Up_Now = 1;
	}
	else if (GetAsyncKeyState(VK_UP) == 0 && up_flag == 1) {
		up_flag = 0;
	}
	if (GetAsyncKeyState(VK_DOWN) != 0 && down_flag == 0) {//проверка нажаьа ли через асинк и сосотояние до этого через флаг
		down_flag = 1;
		Down_Now = 1;
	}
	else if (GetAsyncKeyState(VK_DOWN) == 0 && down_flag == 1) {
		down_flag = 0;
	}
}

void Display_Pointer()
{
	cout << "-->";
}

void Enter_Button() {
	if (GetAsyncKeyState(VK_RETURN) != 0 && enter_flag == 0) {
		enter_flag = 1;
		Enter_Now = 1;
	}
	else if (GetAsyncKeyState(VK_RETURN) == 0 && enter_flag == 1) {
		enter_flag = 0;
	}
}

void Delete_Last_Pointer(int pointer, int MAX) {
	for (int i = 0; i < MAX - pointer + 1; i++) { //такая пиза потому что проходимся по циклу всегда снизу
		cout << "\033[A"; // для подъема вверх
	}
	cout << "   " << "\b\b\b";
	for (int i = 0; i < MAX - pointer + 1; i++) { //такая пиза потому что проходимся по циклу всегда снизу
		cout << "\033[B"; // спускаемся 
	}
}

void Creat_New_Pointer(int pointer, int MAX) {
	for (int i = 0; i < MAX - pointer + 1; i++) { //такая пиза потому что проходимся по циклу всегда снизу
		cout << "\033[A"; // для подъема вверх
	}
	Display_Pointer();
	cout << "\b\b\b"; //возвращаем на 3 влево
	for (int i = 0; i < MAX - pointer + 1; i++) { //такая пиза потому что проходимся по циклу всегда снизу
		cout << "\033[B"; // спускаемся 

	}
}

void Up_Or_Down_Logic(int MAX) {
	Up_Or_Down_Button();
	if (Up_Now == 1 || Down_Now == 1) {
		Delete_Last_Pointer(pointer, MAX);
		if (Up_Now == 1) {
			if (pointer == 1) {
				pointer = MAX;
			}
			else
				pointer--;
			Up_Now = 0;
		}
		else {
			if (pointer == MAX) {
				pointer = 1;
			}
			else
				pointer++;
			Down_Now = 0;
		}
		Creat_New_Pointer(pointer, MAX);
	}
}

void New_Screen() {
	system("cls");
}
//заменить на system("cls");
void Clear_Cin() {
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE)); // Очистка консольного ввода
	cin.clear(); // Сброс любых ошибок в cin
//	cin.sync(); // Синхронизация буфера (убирает остатки)
}

double Get_Value() {// 
	double input;
	bool Valid_Input = 0;
	while (!Valid_Input) {
		cin >> input;
		if (!cin.good()) {
			cin.clear();
			do {
				cin.ignore(1); // типо - 1 символ //ignore = delete
			} while (cin.peek() != '\n');
			cout << "Invalid data type (^^)" << endl;
		}
		else {
			return input;
			Valid_Input = 1;
		}
	}
}

string Get_Punk() {
	string input, input_new;
	cin >> input;
	while (cin.peek() != '\n') {
		if (cin.peek() == ' ') input += " ";
		cin >> input_new;
		input += input_new;
	}
	return input;
}

string Get_Number() {
	string number;
	bool valid_exit = 0;
	while (!valid_exit) {
		cin >> number;
		if (number.size() != 4)
		{
			cout << "ЭБАНЬКО ? \n";
		} 
		else {
			int valid_digit = 0;
			
			for (int i = 0; i < 3; i++)	{
				if (isdigit(number[i])) {
					valid_digit++;
				}
			}
			if (isalpha(number[3]) && valid_digit == 3) {
				char last_ch = toupper(number[3]);
				if (last_ch >= 'A' && last_ch <= 'Z') {
					valid_exit = 1;
				}
			}
		}
		cin.clear();
		cin.ignore(4, '\n');
	}
	return number;
}

string Cin_Time() {
	string input;
	int hour = -1, min = -1;
	bool validInput = false;

	while (!validInput) {
		cout << "Введите время в формате (чч:мм): ";
		cin >> input; // Считываем всю строку целиком
		if (input.length() == 5 && input[2] == ':') {
			string hourStr = input.substr(0, 2); // Первые две цифры — часы
			string minStr = input.substr(3, 2);  // Последние две цифры — минуты
			if (hourStr.find_first_not_of("0123456789") == string::npos &&
				minStr.find_first_not_of("0123456789") == string::npos) {
				hour = stoi(hourStr); // Преобразуем в int
				min = stoi(minStr);

			
				if (hour >= 0 && hour <= 23 && min >= 0 && min <= 59) {
					validInput = true; // Ввод корректен
				}
				else {
					cout << "Eblan y nas chaci 0-23 i minuti toje po formatu 0-59" << endl;
				}
			}
			else {
				cout << "ты долбаеб. Ну реально:  iq не хватает циферки от другого отличать?\n";
			}
		}
		else {
			cout << "Eblan формат для кого? бездарь слепой или криворукий" << endl;
		}

		// Очищаем поток ввода, если что-то пошло не так
		if (!validInput) {
			cin.clear();
		}
	}

	// Форматируем результат: добавляем ведущий ноль, если нужно
	string result = (hour < 10 ? "0" : "") + to_string(hour) + ":" +
		(min < 10 ? "0" : "") + to_string(min);
	return result;
}


//-------------------------------------------------------------SORTIROUKAAAAAA

// Функция для обмена элементов
void Swap_Elements(Train& firstElement, Train& secondElement) {
	Train temporary = firstElement;  // Используем копирование объекта
	firstElement = secondElement;
	secondElement = temporary;
}

// Функция разделения массива
int Partition_Vector(vector<Train>& arrayToSort, int leftIndex, int rightIndex) {
	string pivotValue = arrayToSort[rightIndex].Display_Element("Punk_Vidachi"); // Опорный элемент — пункт назначения
	int smallerElementsBoundary = leftIndex - 1; // Граница элементов, меньших pivot

	for (int currentIndex = leftIndex; currentIndex < rightIndex; currentIndex++) {
		if (arrayToSort[currentIndex].Display_Element("Punk_Vidachi") <= pivotValue) {
			smallerElementsBoundary++;
			Swap_Elements(arrayToSort[smallerElementsBoundary], arrayToSort[currentIndex]);
		}
	}

	Swap_Elements(arrayToSort[smallerElementsBoundary + 1], arrayToSort[rightIndex]);
	return smallerElementsBoundary + 1; // Позиция pivot
}

// Рекурсивная функция быстрой сортировки
void Quick_Sort(vector<Train>& arrayToSort, int leftIndex, int rightIndex) {
	if (leftIndex < rightIndex) {
		int pivotPosition = Partition_Vector(arrayToSort, leftIndex, rightIndex);
		Quick_Sort(arrayToSort, leftIndex, pivotPosition - 1);
		Quick_Sort(arrayToSort, pivotPosition + 1, rightIndex);
	}
}
//Данила ГЕЙ (^^)