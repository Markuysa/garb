#ifndef branch_H5
#define branch_H5
#include <iostream>
#include <string>
#include <vector>
#include "cl_base.h"
class cl_5 :public cl_base {
public:
	cl_5(cl_base* root, string name) :cl_base(root, name) {}; // Наследованный от базового класса параметризированный коснструктор
	void signal_m(string temp) {};
	void handler_m(string path, string message = "/") { 
		string command = "Ready to work";
		emit_connection(SIGNAL_D(cl_5::signal_m), command);
	}
};
#endif