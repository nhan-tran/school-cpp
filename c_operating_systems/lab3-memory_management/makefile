

#Makefile variable definitions
CC = /usr/bin/g++
LD = /usr/bin/g++
CFLAGS =
LDFLAGS =
LIB = 
RM = /bin/rm -f
#
#Variables for the file being compiled
###########################
NAME = nt_lab3_main
###########################
#
OBJS = $(NAME).o
PROG = $(NAME)
SRC = $(NAME).cpp

all: $(PROG)

$(PROG): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(PROG) $(LIB)

$(OBJS):  $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)

clean:
	$(RM) $(PROG) $(OBJS)
	
