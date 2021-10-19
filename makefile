main:
	clang++ Convert2Binary.cpp -Ofast -o c2b.exe

run:
	c2bO0.exe c2b.exe
	c2bO1.exe c2b.exe
	c2bO2.exe c2b.exe
	c2bO3.exe c2b.exe
	c2bOf.exe c2b.exe

console:
	c2bO0.exe a.exe -c
	c2bO1.exe a.exe -c
	c2bO2.exe a.exe -c
	c2bO3.exe a.exe -c
	c2bOf.exe a.exe -c

compile:
	clang++ Convert2Binary.cpp -O0 -o c2bO0.exe
	clang++ Convert2Binary.cpp -O1 -o c2bO1.exe
	clang++ Convert2Binary.cpp -O2 -o c2bO2.exe
	clang++ Convert2Binary.cpp -O3 -o c2bO3.exe
	clang++ Convert2Binary.cpp -Ofast -o c2bOf.exe

assembly:
	clang++ Convert2Binary.cpp -O0 -S -o c2bO0.s
	clang++ Convert2Binary.cpp -O1 -S -o c2bO1.s
	clang++ Convert2Binary.cpp -O2 -S -o c2bO2.s
	clang++ Convert2Binary.cpp -O3 -S -o c2bO3.s
	clang++ Convert2Binary.cpp -Ofast -S -o c2bOf.s