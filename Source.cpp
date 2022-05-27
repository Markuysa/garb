#include <iostream>
#include "cl_application.h"
#include "cl_base.h"
#include "cl_branch.h"
using namespace std;
int main() {
	application obj(nullptr); // Объявление корневого объекта с указателем на null
	//bool checker = obj.build_Tree(); //Построение дерева иерархии
	obj.build_obj_tree();
	return obj.executeApp(1); // Запуск системы
}