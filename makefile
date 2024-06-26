linker = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
cpps1 = client.cpp Components/Component.cpp Components/Textbox.cpp  Components/Button.cpp  Sections/Section.cpp  Sections/ClientSection.cpp Sections/MsgSection.cpp Sections/PlotSection.cpp Manager/InputManager.cpp Client/Client.cpp Server/Server.cpp encoding_functions.cpp Components/Plot.cpp

cpps2 = server.cpp Components/Component.cpp Components/Textbox.cpp  Components/Button.cpp  Sections/Section.cpp  Sections/ClientSection.cpp Sections/MsgSection.cpp Sections/PlotSection.cpp Manager/InputManager.cpp Client/Client.cpp Server/Server.cpp encoding_functions.cpp Components/Plot.cpp
all:
	g++ -o client $(cpps1) $(linker) 
	g++ -o server $(cpps2) $(linker)
	rm -f *.o