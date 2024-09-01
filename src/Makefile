include common.mk

INCLUDE_DIR   = ../include
FRONTEND_DIR  = frontend/
EXECUTION_DIR = execution/

NAME = $(TARGET_NAME)

OBJS_PREFIXED = $(FRONTEND_DIR)frontend.o $(EXECUTION_DIR)execution.o
CXXFLAGS += -I $(INCLUDE_DIR)

$(OBJS_PREFIXED):
	$(MAKE) -C $(FRONTEND_DIR) all
	$(MAKE) -C $(EXECUTION_DIR) all

$(NAME): $(OBJS_PREFIXED)
	$(CXX) $(CXXFLAGS) $(OBJS_PREFIXED) main.cpp debug.cpp -o $(NAME)

all: $(NAME)
	mv $(NAME) ../

clean:
	$(MAKE) -C $(FRONTEND_DIR) fclean
	$(MAKE) -C $(EXECUTION_DIR) fclean

fclean: clean
	rm -f ../$(NAME)

re: clean all