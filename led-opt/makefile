TARGET = led
CXX = avr-unknown-elf-g++
CXXFLAGS = -Wall -Wextra -O3 -pedantic -Weffc++ -std=c++11 -mmcu=atmega328p
OBJECTS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))
HEADERS = $(wildcard *.h)

default: $(TARGET).hex
	@echo 
	@echo $(OBJECTS) $(HEADERS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET).elf: $(OBJECTS)
	$(CXX) -mmcu=atmega328p -nostartfiles -Wl,-Tavr.ld,-Map,$(TARGET).map $(OBJECTS) crt0.o -o $(TARGET).elf

$(TARGET).hex: $(TARGET).elf
	avr-unknown-elf-objcopy -O ihex $< $@	

clean:
	rm -f $(OBJECTS) $(TARGET).elf $(TARGET).hex
