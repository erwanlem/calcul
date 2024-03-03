
main : main.cpp program/file.dll program/animBackground.dll program/exercice.dll program/calcul.dll program/button.dll program/entry.dll program/checkBox.dll program/graphics.dll program/image.dll program/slideBar.dll 
	g++ -O -o program/main main.cpp -L./program -lfile -lexercice -lbutton -lentry -lanimBackground -lcheckBox -lgraphics -limage -lcalcul -lslideBar -lsfml-system -lsfml-window -lsfml-graphics


file.o : file.cpp
	g++ -c file.cpp

program/file.dll : file.o exercice.o calcul.o
	g++ -shared -o program/file.dll file.o exercice.o calcul.o -lsfml-system -lsfml-window -lsfml-graphics


exercice.o : exercice.cpp
	g++ -c exercice.cpp

program/exercice.dll : exercice.o calcul.o file.o
	g++ -shared -o program/exercice.dll exercice.o calcul.o file.o -lsfml-system -lsfml-window -lsfml-graphics
 

calcul.o : calcul.cpp
	g++ -c calcul.cpp 

program/calcul.dll : calcul.o
	g++ -shared -o program/calcul.dll calcul.o -lsfml-system -lsfml-window -lsfml-graphics


animBackground.o : animBackground.cpp
	g++ -c animBackground.cpp

program/animBackground.dll : animBackground.o
	g++ -shared -o program/animBackground.dll animBackground.o -lsfml-system -lsfml-window -lsfml-graphics


button.o : widget/button.cpp
	g++ -c widget/button.cpp

program/button.dll : button.o
	g++ -shared -o program/button.dll button.o -lsfml-system -lsfml-window -lsfml-graphics


entry.o : widget/entry.cpp
	g++ -c widget/entry.cpp

program/entry.dll : entry.o
	g++ -shared -o program/entry.dll entry.o -lsfml-system -lsfml-window -lsfml-graphics


image.o : widget/image.cpp
	g++ -c widget/image.cpp

program/image.dll : image.o
	g++ -shared -o program/image.dll image.o -lsfml-system -lsfml-window -lsfml-graphics


checkBox.o : widget/checkBox.cpp
	g++ -c widget/checkBox.cpp

program/checkBox.dll : checkBox.o
	g++ -shared -o program/checkBox.dll checkBox.o -lsfml-system -lsfml-window -lsfml-graphics


graphics.o : widget/graphics.cpp
	g++ -c widget/graphics.cpp

program/graphics.dll : graphics.o
	g++ -shared -o program/graphics.dll graphics.o -lsfml-system -lsfml-window -lsfml-graphics

slideBar.o : widget/slideBar.cpp
	g++ -c widget/slideBar.cpp

program/slideBar.dll : slideBar.o
	g++ -shared -o program/slideBar.dll slideBar.o -lsfml-system -lsfml-window -lsfml-graphics


clean :
	del /s *.o test.exe *.dll