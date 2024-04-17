NAME 		= kdolib.a

CXX			= c++
RM			= rm -f
CLONE 		= git clone --depth=1

CXXFLAGS	+= -Wall -Wextra -Werror -std=c++98
LDLIBS		=

SRC 		= Socket/Socket.cpp\
			  Socket/TcpServer.cpp\
			  Socket/TcpClient.cpp\
			  io/convert.cpp\
			  str/strupper.cpp\
			  str/strtrim.cpp\
			  str/string_view.cpp\
			  str/stricmp.cpp\
			  State/State.cpp\
			  BNF/BNFAlts.cpp\
			  BNF/BNFParser.cpp\
			  BNF/BNFCat.cpp\
			  BNF/BNFChar.cpp\
			  BNF/BNFFind.cpp\
			  BNF/BNFInher.cpp\
			  BNF/BNFRange.cpp\
			  BNF/BNFRep.cpp\
			  BNF/BNFStr.cpp\
			  BNF/BNFVar.cpp

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
