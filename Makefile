

CC = g++

CFLAGS = -std=c++17 
TRAIN_SRC = train/main 
PRDCT_SRC = prediction/main

INC = include

HEADER = include/MVector/MVector.hpp include/Matrix/Matrix.hpp include/lr/lr.hpp include/csv_to_matrix/csv_to_matrix.hpp

ODIR = obj
TOBJ = $(addprefix $(ODIR)/, $(TRAIN_SRC:=.o))
POBJ = $(addprefix $(ODIR)/, $(PRDCT_SRC:=.o))

TRAIN_NAME = train
PRDCT_NAME = prediction
TEST_NAME = test

all: $(TRAIN_NAME) $(PRDCT_NAME) $(TEST_NAME)

$(TRAIN_NAME): $(TOBJ)
	$(CC) $(CFLAGS)  $(TOBJ) -o $(TRAIN_NAME)

$(PRDCT_NAME): $(POBJ)
	$(CC) $(CFLAGS)  $(POBJ) -o $(PRDCT_NAME) 

$(ODIR)/%.o: src/%.cpp $(HEADER)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(INC)  -c $< -o $@

clean:
	rm -rf $(ODIR)

fclean: clean
	rm -rf  $(TRAIN_NAME) $(PRDCT_NAME) $(TEST_NAME)

re: fclean all

.PHONY : re fclean clean all