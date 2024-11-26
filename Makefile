

CC = g++

CFLAGS = -std=c++17 -Werror -Wall -Wextra

SRC = main

INC = include

HEADER = 

ODIR = obj

OBJ = $(addprefix $(ODIR)/, $(SRC:=.o))

NAME = train

all: $(NAME)

$(NAME): $(OBJ)
	@echo $(OBJ)
	@$(CC) $(CFLAGS)  $(OBJ) -o $(NAME)  -L/usr/local/lib -flto=28 -I/usr/local/include -lmatplot

$(ODIR)/%.o: src/%.cpp $(HEADER)
	@echo src/%.cpp
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(INC) -L/usr/local/lib -I/usr/local/include -flto=28 -lmatplot -c $< -o $@

clean:
	rm -rf $(ODIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY : re fclean clean all