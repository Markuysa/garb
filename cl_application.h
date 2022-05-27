#ifndef CL_application
#define CL_application
#include "cl_branch.h"
#include "class_2.h"
#include "class_3.h"
#include "class_4.h"
#include "class_5.h"
#include "class_6.h"
#include "cl_base.h"
#include <iostream>
#include <string>
#include <vector>
class application : public cl_base {
public:
	void build_obj_tree();
	application(cl_base* root) : cl_base(root) { };
	void build_connections();
	bool build_Tree(); // Метод построения дерева иерархии
	int executeApp(bool checker); // Метод запуска алгоритма программы
};
#endif