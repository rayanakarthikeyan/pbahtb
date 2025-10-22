all:
	gcc src/*.c -Iinclude -o hash_analyzer -Wall

clean:
	rm -f hash_analyzer
