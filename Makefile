CXX = g++
CXXFLAGS = -Wall -std=c++14
TARGET = cafenele
SRCS = Angajati/Angajat.cpp Comenzi/Comanda.cpp Produse/Produs.cpp CSV/CsvHandler.cpp main.cpp Raport/Raport.cpp Evenimente/Eveniment.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
