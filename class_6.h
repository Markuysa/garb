#ifndef branch_H6
#define branch_H6
#include <iostream>
#include <string>
#include <vector>
#include "cl_base.h"
class cl_6 :public cl_base {
public:
	cl_6(cl_base* root, string name) :cl_base(root, name) {}; // Наследованный от базового класса параметризированный коснструктор
	void signal_m(string path) { cout << endl << "The amount " << path; };
	void handler_m(string path, string message = "/") {  }
};
#endif