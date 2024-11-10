CXX = g++

SRCS = sources/main.cpp sources/game.cpp

HEADERS = headers/pokemon.h headers/trainer.h

TARGET = game

build: $(SRCS) $(HEADERS) 
	$(CXX) $(SRCS) $(HEADERS) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)
	
clean:
	rm -f $(TARGET)

g:
	git add .
	git commit -m "$(filter-out $@,$(MAKECMDGOALS))"
	git push -u origin main

%:
	@:

.PHONY: build clean