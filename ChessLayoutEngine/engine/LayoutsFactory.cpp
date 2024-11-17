#include <iostream>
#include "EnumLayouts.h"
#include "LayoutsFactory.h"

Layouts LayoutsFactory::createLayout(int x) {
	switch (x) {
	case 1:
		return Layouts::ALL;
	case 2:
		return Layouts::FUNDEMENTAL;
	case 3:
		return Layouts::FIRST;
	default:
		std::cout << "Layout non existings\n";
		exit(1);
	}
}