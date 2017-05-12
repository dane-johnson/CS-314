.PHONY: all pt5 pt6 wc pt7 reverse reverse2 timetrial test
all: pt5 pt6 pt7
pt5:
	gcc -o pt5 pt5.c
pt6:
	gcc -o wc pt6.c
wc: pt6
pt7: reverse reverse2 timetrial
reverse: test
	gcc -o reverse pt7.a.c
reverse2: test
	gcc -o reverse2 pt7.b.c
timetrial:
	gcc -o timetrial pt7.c.c
test:
	@echo Creating a file to test reversing on...
	echo adcdef > test

