CXX=	clang++
#CXX=	eg++

# compiler flags.
##CXXFLAGS+=	-O0 -mtune=generic -gfull
CXXFLAGS+=	-Ofast -mtune=native -gfull
#CXXFLAGS+=	-O3 -mtune=native -g3
# This doesn't work, we need operator >>, operator << with ongoing stdlibc++.
#CXXFLAGS+=	-I/usr/local/include -mlong-double-128
#CXXFLAGS+=	-Oz -mtune=native -gfull
#CXXFLAGS+=	-O2 -mtune=native -gfull
#CXXFLAGS+=	-O0 -mtune=native -gfull
#CXXFLAGS+=	-pg
MPFLAGS=	-I/usr/local/include -L/usr/local/lib -lomp -fopenmp
#MPFLAGS=	-I/usr/local/include -L/usr/local/lib -lgomp -fopenmp
CXXFLAGS+=	-std=c++11
LDFLAGS+=	-lc++ -L/usr/local/lib
#LDFLAGS+=	-lestdc++ -L/usr/local/lib
# Same as -mlong-double-128
#LDFLAGS+=	-lquadmath -lm

CLEANFILES= *.o intscalc

clean:
	@rm -rf ${CLEANFILES}

all:	intscalc

intscalc:
	${CXX} ${CXXFLAGS} -static -D_FLOAT_BITS_=2048 -o intscalc intscalc.cc

