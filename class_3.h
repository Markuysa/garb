#ifndef branch_H3
#define branch_H3
#include <iostream>
#include <string>
#include <vector>
#include "cl_base.h"
class cl_3 :public cl_base {

public:
	cl_3(cl_base* root, string name) :cl_base(root, name) {}; // Наследованный от базового класса параметризированный коснструктор
	void signal_m(string path) { cout << endl << "Signal from " << path; };
	void handler_m(string path, string message = "/") { cout << endl << "Signal to " << path << " Text:" << message << " (class: 3)";; }
};
#endif