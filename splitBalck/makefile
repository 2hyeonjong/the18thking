CC = g++
SRCS = blackbox.cpp
PROG = blackbox

OPENCV = `pkg-config opencv --cflags --libs`
LIBS = $(OPENCV)

$(PROG):$(SRCS)
	$(CC)  -o $(PROG) $(SRCS) $(LIBS) -pthread
