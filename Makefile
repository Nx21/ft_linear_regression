

CC = g++

CFLAGS = -std=c++17 

TRAIN_SRC = train/main
PRDCT_SRC = prediction/main

INC = include

HEADER = include/prediction/prediction.hpp include/train/train.hpp

ODIR = obj

TOBJ = $(addprefix $(ODIR)/, $(TRAIN_SRC:=.o))
POBJ = $(addprefix $(ODIR)/, $(PRDCT_SRC:=.o))

TRAIN_NAME = train
PRDCT_NAME = prediction

all: $(TRAIN_NAME) $(PRDCT_NAME)

$(TRAIN_NAME): $(TOBJ)
	@echo  $(TOBJ) $(TRAIN_NAME)
	@$(CC) $(CFLAGS)  $(TOBJ) -o $(TRAIN_NAME)  -L/usr/local/lib -flto=28 -I/usr/local/include -lmatplot

$(PRDCT_NAME): $(POBJ)
	@echo  $(POBJ) $(PRDCT_NAME)
	@$(CC) $(CFLAGS)  $(POBJ) -o $(PRDCT_NAME)  -L/usr/local/lib -flto=28 -I/usr/local/include -lmatplot\

$(ODIR)/%.o: src/%.cpp $(HEADER)
	@echo exec3 src/%.cpp
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(INC) -L/usr/local/lib -I/usr/local/include -flto=28 -lmatplot -c $< -o $@

clean:
	rm -rf $(ODIR)

fclean: clean
	rm -rf  $(TRAIN_NAME) $(PRDCT_NAME)

re: fclean all

.PHONY : re fclean clean all