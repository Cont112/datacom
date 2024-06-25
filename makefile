linker = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
cpps = main.cpp Components/Textbox.cpp  Components/Component.cpp Sections/Section.cpp  Sections/ConnSection.cpp Sections/MsgSection.cpp Sections/PlotSection.cpp Manager/InputManager.cpp

all:
	g++ -o main $(cpps) $(linker) 
	rm -f *.o