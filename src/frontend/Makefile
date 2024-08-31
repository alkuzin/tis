include ../common.mk

INCLUDE_DIR = ../../include
NAME = frontend.o

SRC  = token lexer
SRCS = $(addsuffix .cpp, $(SRC))
OBJS = $(addsuffix .o, $(SRC))

CXXFLAGS += -I $(INCLUDE_DIR)

OBJS_DIR = objs/
OBJS_PREFIXED = $(addprefix $(OBJS_DIR), $(OBJS))

$(OBJS_PREFIXED): $(SRCS)
	mkdir -p $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) -c $(SRCS)
	mv *.o $(OBJS_DIR)

$(NAME): $(OBJS_PREFIXED)
	ld $(LFLAGS) $(OBJS_PREFIXED) -o $(NAME)

all: $(NAME) 

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: clean all