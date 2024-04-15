NAME 		= kdolib.a

CXX			= c++
RM			= rm -f
CLONE 		= git clone --depth=1

CXXFLAGS	+= -Wall -Wextra -Werror -std=c++98
LDLIBS		=

SRC 		= BNF/BNFAlts.cpp\
			  BNF/BNFCat.cpp\
			  BNF/BNFChar.cpp\
			  BNF/BNFFind.cpp\
			  BNF/BNFInher.cpp\
			  BNF/BNFParser.cpp\
			  BNF/BNFRange.cpp\
			  BNF/BNFRep.cpp\
			  BNF/BNFStr.cpp\
			  BNF/BNFVar.cpp\
			  io/convert.cpp\
			  Socket/Socket.cpp\
			  Socket/TcpClient.cpp\
			  Socket/TcpServer.cpp\
			  State/State.cpp\
			  str/string_view.cpp\
			  str/strtrim.cpp\
			  str/strupper.cpp

OBJ 		= $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar crs $(NAME) $(OBJ)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

fast: fclean
	$(MAKE) -j$$(nproc)

.PHONY:		all clean fclean re
