PRG=g++

OUT=BF.exe
OUTDIR=Out/
CLA= -pthread -g Src/*.cpp 

build:
	$(PRG) $(CLA) -o $(OUTDIR)$(OUT)
run:
	./$(OUTDIR)$(OUT) --d 0 --f ./$(OUTDIR)test.txt
run_debug:
	./$(OUTDIR)$(OUT) --d 1 --f ./$(OUTDIR)test.txt
