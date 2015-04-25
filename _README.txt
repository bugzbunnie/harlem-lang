Code2AST транлятор:
	программа: 1.cpp
	библиотеки: lexis.h, node.h, 1_recursive_down.h
	входной файл: code.txt (примеры программ из папки Examples надо копировать в него)
	выходной файл: ast.txt

AST2ASM транлятор:
	программа: 2.cpp
	библиотеки: lexis.h, node.h, 2_recursive_down.h, 2_node.h, 2_reader.h
	входной файл: ast.txt
	выходной файл: asm.txt

Code2AST транлятор:
	программа: 3.cpp
	библиотеки: lexis.h, node.h, 2_recursive_down.h, 2_node.h, 2_reader.h
	входной файл: ast.txt
	выходной файл: code_back.txt

процессор:
	программа: 5_Stack_22.cpp
	библиотеки: Exception.h
	входной файл: asm.txt

визуализатор:
	программа: demo\Dotter2.exe
	входной файл: demo\ast.txt
	выходной файл: demo\Graph.jpg

