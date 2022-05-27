#ifndef branch_H4
#define branch_H4
#include <iostream>
#include <string>
#include <vector>
#include "cl_base.h"
class cl_4 :public cl_base {
	
public:
	cl_4(cl_base* root, string name) :cl_base(root, name) {}; // Наследованный от базового класса параметризированный коснструктор
	void signal_m(char path) { cout << endl << "Signal from " << path; };
	void handler_m(string path, string message = "/") {
		int cash;
		cin >> cash;
		set_money(get_money() + cash);
		this->cl_4::signal_m(get_money());
	}
};
#endif