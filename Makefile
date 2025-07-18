

CC = g++

CFLAGS = -std=c++17 
#SRC = MVector/MVector csv_to_matrix/csv_to_matrix
TRAIN_SRC = train/main 
PRDCT_SRC = prediction/main

INC = include

HEADER = include/MVector/MVector.hpp include/Matrix/Matrix.hpp include/lr/lr.hpp include/csv_to_matrix/csv_to_matrix.hpp

ODIR = obj

OBJ = $(addprefix $(ODIR)/, $(SRC:=.o))
TOBJ = $(addprefix $(ODIR)/, $(TRAIN_SRC:=.o))
POBJ = $(addprefix $(ODIR)/, $(PRDCT_SRC:=.o))

TRAIN_NAME = train
PRDCT_NAME = prediction

all: $(TRAIN_NAME) $(PRDCT_NAME)

$(TRAIN_NAME): $(TOBJ)
	@echo  $(TOBJ) $(OBJ) $(TRAIN_NAME)
	$(CC) $(CFLAGS)  $(TOBJ) $(OBJ) -o $(TRAIN_NAME)
# -L/usr/local/lib -flto=28 -I/usr/local/include -lmatplot
$(PRDCT_NAME): $(POBJ)
	@echo  $(POBJ) $(OBJ) $(PRDCT_NAME)
	$(CC) $(CFLAGS)  $(POBJ) $(OBJ) -o $(PRDCT_NAME) 
#-L/usr/local/lib -flto=28 -I/usr/local/include -lmatplot

$(ODIR)/%.o: src/%.cpp $(HEADER)
	@echo exec3 src/%.cpp
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(INC)  -c $< -o $@
#$(CC) $(CFLAGS) -I$(INC) -L/usr/local/lib -I/usr/local/include -flto=28 -lmatplot -c $< -o $@

clean:
	rm -rf $(ODIR)

fclean: clean
	rm -rf  $(TRAIN_NAME) $(PRDCT_NAME)

re: fclean all

.PHONY : re fclean clean all