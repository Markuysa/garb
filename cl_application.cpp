#include "cl_application.h"
#include "cl_base.h"
cl_base* cl_base::root;

bool application::build_Tree() {
	string name_of_p, name_of_ch, name_temp; // Вводимые имена 
	int temp;
	cin >> name_of_p;
	this->set_name(name_of_p);
	cl_base::root = this; // Определение root-объекта
	root->setObjectNum(1);
	cin >> name_of_p;
	cl_base* parent = nullptr, * br = nullptr;
	while (name_of_p != "endtree") {
		parent = get_path(name_of_p); // Определение родителя по координате
		string name_of_p2;
		name_temp = name_of_p;
		cin >> name_of_ch >> temp;
		if (parent != nullptr) {
			switch (temp)
			{
			case 2:
				br = new cl_2(parent, name_of_ch);
				br->setObjectNum(2);
				break;
			case 3:
				br = new cl_3(parent, name_of_ch);
				br->setObjectNum(3);
				break;
			case 4:
				br = new cl_4(parent, name_of_ch);  // Создание объекта с учетом введенного номера класса и установка значения соответствующего поля
				br->setObjectNum(4);
				break;
			case 5:
				br = new cl_5(parent, name_of_ch);
				br->setObjectNum(5);
				break;
			case 6:
				br = new cl_6(parent, name_of_ch);
				br->setObjectNum(6);
				break;
			}
			cin >> name_of_p;
		}
		else {
			cout << "Object tree\n" << this->get_name();   					// Вывод при неудачной сборке дерева
			this->print_tree(1);
			cout << endl << "The head object " << name_temp << " is not found";
			return false;
		}

	}
	build_connections();  // Построение связей 
	return true;
}
void application::build_connections() {
	string path_signal, path_handler;
	cin >> path_signal;
	while (path_signal != "end_of_connections") {
		cin >> path_handler;
		cl_base* ob1 = get_path(path_signal), * ob2 = get_path(path_handler); //  Определение указателя на объект по координате
		ob1->connect(ob1, ob2); // Выполнение установки связи с учетом номера класса 
		cin >> path_signal;
	}
}	
void application::build_obj_tree() {
	cl_base::root = this;
	this->set_name("System");
	cl_base* in = new cl_base(this, "Input");
	cl_2* control = new cl_2(this, "ControlPanel");
	control->setObjectNum(2);
	cl_3* money = new cl_3(this, "CashInput");
	control->setObjectNum(3);
	cl_4* refund = new cl_4(this, "Refund");
	control->setObjectNum(4);
	cl_5*  coffee= new cl_5(this, "CoffeeDevise");
	control->setObjectNum(5);
	cl_6* output = new cl_6(this, "Output");
	control->setObjectNum(6);
	set_connection(in->getSignal(), control, control->getHandler());
	set_connection(in->getSignal(), money, money->getHandler());
	set_connection(in->getSignal(), refund, refund->getHandler());
	set_connection(in->getSignal(), coffee, coffee->getHandler());
	set_connection(in->getSignal(), output, output->getHandler());
	
	/*set_connection(in->getSignal(), output, output->getHandler());
	set_connection(in->getSignal(), output, output->getHandler());
	set_connection(in->getSignal(), output, output->getHandler());
	set_connection(in->getSignal(), output, output->getHandler());*/
}

int application::executeApp(bool checker) {
	if (checker) {
		string command;
		cout << "Object tree\n" << this->get_name();
		this->print_tree(1); // Вызов метода для вывода дерева иерархии
		this->set_all(); // Приведение всех объектов в состояние готовности 
		cin >> command;
		emit_connection(SIGNAL_D(cl_base::signal_m),command);
		

	}
	return 0;
}





























