bcrypt: 
	g++ -std=c++17 bcrypt.cpp main.cpp blowfish.cpp base64.cpp -o bcrypt
test:
	g++ -std=c++17 bcrypt.cpp blowfish.cpp base64.cpp test.cpp -o test
clean:
	rm -f *.o bcrypt test