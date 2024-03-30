NAME 		= kdolib.a

CCPP		= c++
RM			= rm -f
CLONE 		= git clone --depth=1

CPPFLAGS	+= -Wall -Wextra -Werror -std=c++98
CPPLINKS	=

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
			  Socket/SocketTcpClient.cpp\
			  Socket/SocketTcpServer.cpp\
			  str/strtrim.cpp\
			  str/upper.cpp\
			  str/iequals.cpp\
			  str/splitlist.cpp

OBJ 		= $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar crs $(NAME) $(OBJ)

%.o: %.cpp
	$(CCPP) $(CPPFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

fast: fclean
	$(MAKE) -j$$(nproc)

.PHONY:		all clean fclean re
