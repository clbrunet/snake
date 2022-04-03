NAME := snake
SRCS_DIR := ./src
SRCS_EXTENSION := cpp
BUILD_DIR := ./build

CXX := clang++
CXXFLAGS := -Wall -Wextra -Werror
CXXFLAGS += -I./src/
CXXFLAGS += -g3 -fsanitize=address
# CXXFLAGS += -DNDEBUG
LDLIBS := -lncurses

SRCS := $(shell find $(SRCS_DIR) -type f -name "*.$(SRCS_EXTENSION)")
OBJS := $(SRCS:$(SRCS_DIR)/%.$(SRCS_EXTENSION)=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

.PHONY: all
all: $(NAME)

-include $(DEPS)

$(BUILD_DIR)/%.o: $(SRCS_DIR)/%.$(SRCS_EXTENSION) Makefile
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -MMD -MP -MF $(@:.o=.d) -o $@ -c $<

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(NAME) $(OBJS) $(LDLIBS)

.PHONY: clean
clean:
	$(RM) -r $(BUILD_DIR)

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)

.PHONY: re
re: fclean all
