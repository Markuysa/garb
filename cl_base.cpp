#include "cl_application.h"
#include "cl_branch.h"
#include "cl_base.h"
#include <iomanip>
cl_base::cl_base(cl_base* p_head, string name) {
	this->obj_name = name; // Присваивание имени объекту
	if (p_head) { // Если не nullptr
		this->p_head = p_head;
		set_p(p_head);
	}
}
void cl_base::set_p(cl_base* ptr) {
	int size = p_head->childes.size(); // Размер массива наследников текущего гол.объекта
	for (int i = 0; i < size; i++) // Проход по всем потомкам родительского объекта и удаление объекта, который перестал подчиняться родительскому
	{
		if (p_head->childes[i] == this)
		{
			p_head->childes.erase(p_head->childes.begin() + i);
			break;
		}
	}
	p_head->childes.push_back(this); //Добавление указателя на текущий объект
	this->p_head = p_head;
}
cl_base* cl_base::get_object_by_name(string name) //Метод поиска объекта по имени
{
	if (this->childes.size() == 0 && this->get_name() != name) {
		return nullptr;// Если это крайний элемент, который не подходит
	}
	if (this->get_name() == name) // Если имя текущего объекта совпадает с требуемым
		return this;
	for (int i = 0; i < this->childes.size(); i++)
		if (this->childes[i]->get_object_by_name(name) != nullptr) // Поиск среди дочерних
			return this->childes[i]->get_object_by_name(name);
	return nullptr;
}
void cl_base::set_name(string name) {
	this->obj_name = name; // Установка имени объекта
}
string cl_base::get_name() {
	return obj_name; // Возврат имени объекта
}

void cl_base::print_tree(int num_of_tabs) {
	string tabulaion = string(num_of_tabs * 4, ' '); // Определение отступа

	for (int i = 0; i < this->childes.size(); i++) {
		cout << endl << tabulaion << this->childes[i]->get_name();   //Вывод имени
		if (this->childes[i]->childes.size() != 0) {
			this->childes[i]->print_tree(num_of_tabs + 1); // Рекурсивный вызов функции для наследников
		}
	}
}

void cl_base::Status_setter(string name_r) {
	string name;
	int temp;
	while (cin >> name >> temp) {
		cl_base* obj = get_object_by_name(name);
		if (name_r == name)
			obj->set_value(temp); // Установка значения для головного объекта
		else {
			if (obj->get_phead() != nullptr) {
				if (obj->get_phead()->get_value() == 0) // Если объект выше по иерархии не активирован-установка 0
					obj->set_value(0);
				else
					obj->set_value(temp); // Иначе установка заданного значения 
			}
		}
	}
}
void cl_base::Print_status(int num_of_tabs) {
	string tabulaion = string(num_of_tabs * 4, ' '); //Определение отступа
	for (int i = 0; i < this->childes.size(); i++)
	{
		if (this->childes[i]->get_value() == 0) {
			cout << endl << tabulaion << this->childes[i]->get_name() << " is not ready"; //Если состояние равно 0
		}
		else {
			cout << endl << tabulaion << this->childes[i]->get_name() << " is ready";//Если состояние отлично от 0
		}
		if (this->childes[i]->childes.size() != 0)
		{
			this->childes[i]->Print_status(num_of_tabs + 1); //Рекурсивный вызов для наследников
		}
	}
}



void cl_base::get_by_path() {

	string command, path;
	cl_base* current = this, * object = nullptr;
	cin >> command;
	while (command != "END") {
		cin >> path;
		if (path == "/")
			object = this; // Если путь состоит только из одного /, то присвоить корневой объект
		else
			object = current->get_path(path); // Иначе присвоить объекту указатель на объект от текущего
		string temp_path = path;
		cl_base* temp = nullptr;
		if (command == "FIND") {
			if (object)
				cout << endl << temp_path << "     Object name: " << object->get_name(); // Если найден объект по координате
			else
				cout << endl << temp_path << "     Object is not found"; //Если объект не найден
		}
		else if (command == "SET") {
			if (object) {
				current = object; // Установленный объект
				cout << endl << "Object is set: " << current->get_name(); //Если объект успешно установлен
			}
			else
				cout << endl << "Object is not found: " << current->get_name() << " " << path;// Ошибка установки

		}
		if (command == "EMIT") {    // Если введена функция EMIT
			string message;
			getline(cin, message);

			if (object == nullptr) {
				cout << endl << "Object " << path << " not found";
			}
			else {
				object->emit(message);
			}
		}
		else if (command == "SET_CONNECT") {  // Если введена функция SET_CONNECT
			string path_2;
			cin >> path_2;
			cl_base* ob2;
			if (path_2 == "/") ob2 = root;
			else ob2 = get_path(path_2); //  Определение указателя на объект по координате
			if (object == nullptr || ob2 == nullptr) {
				if (object == nullptr)
					cout << endl << "Object " << path << " not found";   // Если объект не найден
				else
					cout << endl << "Handler object " << path_2 << " not found";
			}
			else {
				object->connect(object, ob2);
			}
		}

		else if (command == "DELETE_CONNECT") { // Если введена функция DELETE_CONNECT 
			string  path_2;
			cin >> path_2;
			cl_base* ob2;
			if (path_2 == "/") {
				ob2 = this;
			}
			else {
				ob2 = get_path(path_2);
			}
			if (object == nullptr || ob2 == nullptr) {
				if (object == nullptr)
					cout << endl << "Object " << path << " not found";
				else// Если объект не найден
					cout << endl << "Handler object " << path_2 << " not found";
			}
			else {
				object->deletec(object, ob2);
			}
		}
		else if (command == "SET_CONDITION") { // Если введена функция SET_CONDITION 
			int value;
			cin >> value;
			cl_base* obj1;
			if (path == "/")
				obj1 = this;
			else
				obj1 = get_path(path);//  Определение указателя на объект по координате
			if (obj1 == nullptr) {
				cout << endl << "Object " << path << " not found"; // Если объект не найден
			}
			else obj1->change_state(value); // Установка значения состояния
		}
		cin >> command;
	}
}
void cl_base::change_state(int state) {
	if (state == 0) {

		//Установка нулевого состояния для текщего объекта
		this->set_value(0);

		// Установка нулеового состояния на дочерние объекты
		for (int i = 0; i < this->childes.size(); i++) {
			this->childes[i]->change_state(0);
		}

	}
	else if (this->get_phead() == nullptr) {
		//Установка состояния для корневого объекта
		this->set_value(state);
	}
	else {

		if (this->get_phead()->get_value() == 0) {
			// Если родительский объект текущего не включен, то установить 0
			this->set_value(0);
		}
		else {
			//Устанавливается введенное состояние
			this->set_value(state);
		}
	}
}
cl_base* cl_base::get_path(string name_of_p) {

	if (name_of_p == "/") return root;
	cl_base* temp;
	string child = "", name_of_r = "";;
	bool checker = true;

	for (int i = 0; i < name_of_p.length(); i++) {
		if (name_of_p[i] == '/' and name_of_r == "") {
			continue;
		}
		else if (name_of_p[i] != '/' and checker) {      // Выделение подстроки из имени головного объекта и потомка
			name_of_r += name_of_p[i];
		}
		else if (name_of_p[i] == '/') {
			checker = false;
			child += name_of_p[i];
		}
		else {
			child += name_of_p[i];
		}
	}

	for (int i = 0; i < this->childes.size(); i++) { // Проход по потомкам текущего объекта

		if (this->childes[i]->get_name() == name_of_r) {

			if (child == "") { // Если в координате был один объект и он найден, то вернуть его

				return this->childes[i];
			}
			else {

				temp = this->childes[i]->get_path(child); // Иначе продолжить поиск от ранее найденного
				if (temp != nullptr) {
					return temp;
				}
			}
		}
	}
	return nullptr;

}
cl_base* cl_base::koord_abs_relat(string name_of_p) {
	cl_base* current = this;
	int index;
	string name_of_p2;
	cl_base* parent = nullptr;
	name_of_p.erase(0, 1); // Удаление первого слеша
	while (name_of_p.length() != 0) {
		index = name_of_p.find("/"); // Поиск первого вхождения /
	// Если индекс не найден, то присвоить значение длины координаты
		if (index == -1)
			index = name_of_p.length();
		name_of_p2 = name_of_p.substr(0, index); // Подстрока с именем объекта
		name_of_p.erase(0, name_of_p2.length() + 1); // Удаление подстроки
		cl_base* head = current->get_object_by_name(name_of_p2); // Поиск объекта из подстроки
		current = head;
		if (current == nullptr) return nullptr;
		if (current->get_object_by_name(name_of_p2) == nullptr) { //Если от текущего объекта не найден объект из координаты
			parent = nullptr;
		}
		else
			parent = current->get_object_by_name(name_of_p2);

	}
	return parent;
}
void cl_base::signal_m(string path) {
	
};
TYPE_SIGNAL cl_base::getSignal() {
	switch (getObjectNum()) {
	case 1:
	default:
		return SIGNAL_D(cl_base::signal_m);
	case 2:
		return SIGNAL_D(cl_2::signal_m);
	case 3:
		return SIGNAL_D(cl_3::signal_m);
	case 4:
		return SIGNAL_D(cl_4::signal_m);
	case 5:
		return SIGNAL_D(cl_5::signal_m);
	case 6:
		return SIGNAL_D(cl_6::signal_m);
	}
}

TYPE_HANDLER cl_base::getHandler() {
	switch (getObjectNum()) {
	case 1:
	default:
		return HANDLER_D(cl_base::handler_m);
	case 2:
		return HANDLER_D(cl_2::handler_m);
	case 3:
		return HANDLER_D(cl_3::handler_m);
	case 4:
		return HANDLER_D(cl_4::handler_m);
	case 5:
		return HANDLER_D(cl_5::handler_m);
	case 6:
		return HANDLER_D(cl_6::handler_m);
	}
}
// Метод установки связи
void cl_base::set_connection(TYPE_SIGNAL pointer_signal, cl_base* obj_pointer, TYPE_HANDLER pointer_handler) {

	connection_strct* pointer_value;

	for (int i = 0; i < this->connections.size(); i++) {
		if (connections.at(i)->pointer_handler == pointer_handler &&
			connections.at(i)->obj_pointer == obj_pointer && //Проверка на существование связи с текущими параметрами
			connections.at(i)->pointer_signal == pointer_signal
			) return;
	}
	pointer_value = new connection_strct;

	pointer_value->obj_pointer = obj_pointer;
	pointer_value->pointer_handler = pointer_handler;  // Заполнение полей связи
	pointer_value->pointer_signal = pointer_signal;

	this->connections.push_back(pointer_value); // Добавление в вектор связей 

}
string cl_base::get_path_of_obj() {
	string result;
	if (this == root) {
		return "/"; // Если текущий объект является корневым 
	}
	else {
		cl_base* current = this;
		while (current != root) {
			result = '/' + current->get_name() + result; // Иначе с текущего объекта проследовать до корневого и запомнить путь
			current = current->get_phead();

		}
	}
	return result;

}
void cl_base::handler_m(string path, string message) {
	cl_base* system_obj = root;
	if (!get_value()) return;
	size_t count_of_5, count_of_10;
	size_t count;
	string ava;
	coffe_types* obj = new coffe_types;
	cin >> count;
	for (size_t i = 0; i < count; i++) {
		cin >> obj->name;
		types_of_coffe.push_back(obj);
		obj=new coffe_types;
	}
	for (size_t i = 0; i < count; i++)
		cin >> types_of_coffe.at(i)->price;

	cin >> count_of_5 >> count_of_10;
	system_obj->setFiveCount(count_of_5);
	system_obj->setTenCount(count_of_10);

	message = "Ready to work";
	emit_connection(SIGNAL_D(cl_6::signal_m), message);
	while (true){
		cin >> message;
		if (message == "Cancel") break;
		emit_connection(SIGNAL_D(cl_2::signal_m), message);
	}
	message = "Turned off";
	emit_connection(SIGNAL_D(cl_branch::signal_m), message);
}

void cl_base::emit_connection(TYPE_SIGNAL p_signal, string& command) {
	if (connections.size() == 0 || this->get_value() == 0) return; // Если вектор связей пуст или значение состояния объекта равно 0
	(this->*signal_m)(command);	
	for (int i = 0; i < this->connections.size(); i++) {
		if (connections.at(i)->pointer_signal == p_signal) {
			if (connections.at(i)->obj_pointer->get_value() != 0)
			{
				(this->*handler_m)(command); // Выполнение метода-обработчика
			}
		}
	}
}

int cl_base::getObjectNum() {
	return this->num_of_class; // Получение номера класса
}
void cl_base::deleteTheConnection(TYPE_SIGNAL pointer_signal, cl_base* obj_pointer, TYPE_HANDLER pointer_handler) {

	for (int i = 0; i < connections.size(); i++) {
		if (connections.at(i)->pointer_handler == pointer_handler &&
			connections.at(i)->obj_pointer == obj_pointer &&// При обнаружении совпадения удалить связь из вектора
			connections.at(i)->pointer_signal == pointer_signal
			) {
			this->connections.erase(connections.begin() + i);
			return;
		};
	}
}
void cl_base::set_all() {
	if (this->childes.size() != 0)
		for (int i = 0; i < this->childes.size(); i++) {
			childes.at(i)->set_value(1); 	// Установка готовности объекта (допустимо любое ненулевое значение)
			childes.at(i)->set_all(); // Рекурсивный вызов для наследников 
		}
	else return;
}
void cl_base::emit(string message) {
	cl_base* ob1 = this;
	cl_base* ob2 = this;

	while (ob2 != root) {
		if (ob2->get_value() == 0)
			return;
		else
			ob2 = ob2->get_phead();
	}
	if (ob1->get_value() != 0) {
		switch (ob1->getObjectNum()) {
		case 1:
			ob1->emit_connection(SIGNAL_D(cl_branch::signal_m), message);
			break;
		case 2:
			ob1->emit_connection(SIGNAL_D(cl_2::signal_m), message);
			break;
		case 3:
			ob1->emit_connection(SIGNAL_D(cl_3::signal_m), message);  /* Выполнение метода выдачи сигнала для объектов																с учетом классовой принадлежности*/
			break;
		case 4:
			ob1->emit_connection(SIGNAL_D(cl_4::signal_m), message);
			break;
		case 5:
			ob1->emit_connection(SIGNAL_D(cl_5::signal_m), message);
			break;
		case 6:
			ob1->emit_connection(SIGNAL_D(cl_6::signal_m), message);
			break;
		}
	}

}


void cl_base::connect(cl_base* ob1, cl_base* ob2) {
	switch (ob1->getObjectNum()) {
	case 1:
		ob1->set_connection(SIGNAL_D(cl_branch::signal_m), (cl_branch*)ob2, HANDLER_D(cl_branch::handler_m));
		break;
	case 2:
		ob1->set_connection(SIGNAL_D(cl_2::signal_m), (cl_2*)ob2, HANDLER_D(cl_2::handler_m));
		break;
	case 3:
		ob1->set_connection(SIGNAL_D(cl_3::signal_m), (cl_3*)ob2, HANDLER_D(cl_3::handler_m)); /* Выполнение метода установки связи для объектов
																									с учетом классовой принадлежности*/
		break;
	case 4:
		ob1->set_connection(SIGNAL_D(cl_4::signal_m), (cl_4*)ob2, HANDLER_D(cl_4::handler_m));
		break;
	case 5:
		ob1->set_connection(SIGNAL_D(cl_5::signal_m), (cl_5*)ob2, HANDLER_D(cl_5::handler_m));
		break;
	case 6:
		ob1->set_connection(SIGNAL_D(cl_6::signal_m), (cl_6*)ob2, HANDLER_D(cl_6::handler_m));
		break;
	}

}


void cl_base::deletec(cl_base* ob1, cl_base* ob2) {
	switch (ob1->getObjectNum()) {
	case 1:
		ob1->deleteTheConnection(SIGNAL_D(cl_branch::signal_m), (cl_branch*)ob2, HANDLER_D(cl_branch::handler_m));
		break;
	case 2:
		ob1->deleteTheConnection(SIGNAL_D(cl_2::signal_m), (cl_2*)ob2, HANDLER_D(cl_2::handler_m));
		break;
	case 3:
		ob1->deleteTheConnection(SIGNAL_D(cl_3::signal_m), (cl_3*)ob2, HANDLER_D(cl_3::handler_m));
		break;																									/* Выполнение метода удаления связи для объектов
																													с учетом классовой принадлежности*/
	case 4:
		ob1->deleteTheConnection(SIGNAL_D(cl_4::signal_m), (cl_4*)ob2, HANDLER_D(cl_4::handler_m));
		break;
	case 5:
		ob1->deleteTheConnection(SIGNAL_D(cl_5::signal_m), (cl_5*)ob2, HANDLER_D(cl_5::handler_m));
		break;
	case 6:
		ob1->deleteTheConnection(SIGNAL_D(cl_6::signal_m), (cl_6*)ob2, HANDLER_D(cl_6::handler_m));
		break;
	}

}

//void (*handler_finder(cl_base* obj))(cl_base*, string&) {
//
//	
//
//}
