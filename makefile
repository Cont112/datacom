linker = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
cpps = main.cpp Components/Component.cpp Components/Textbox.cpp  Components/Button.cpp  Sections/Section.cpp  Sections/ConnSection.cpp Sections/MsgSection.cpp Sections/PlotSection.cpp Manager/InputManager.cpp Client/Client.cpp Server/Server.cpp

all:
	g++ -o main $(cpps) $(linker) 
	rm -f *.o