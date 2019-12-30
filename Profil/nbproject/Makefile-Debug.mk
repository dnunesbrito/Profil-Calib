#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++-7
CXX=g++-7
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/c32d8f73/Bias0.o \
	${OBJECTDIR}/_ext/c32d8f73/Bias0Ext.o \
	${OBJECTDIR}/_ext/c32d8f73/Bias1.o \
	${OBJECTDIR}/_ext/c32d8f73/Bias2.o \
	${OBJECTDIR}/_ext/c32d8f73/BiasF.o \
	${OBJECTDIR}/_ext/c32d8f73/BiasFExt.o \
	${OBJECTDIR}/_ext/c32d8f73/BiasRnd.o \
	${OBJECTDIR}/_ext/c32d8f73/Rounding.o \
	${OBJECTDIR}/_ext/c32defab/Complex.o \
	${OBJECTDIR}/_ext/c32defab/Constants.o \
	${OBJECTDIR}/_ext/c32defab/EFunctions.o \
	${OBJECTDIR}/_ext/c32defab/EINTERVAL.o \
	${OBJECTDIR}/_ext/c32defab/EINTERVALVECTOR.o \
	${OBJECTDIR}/_ext/c32defab/EINTERVAL_MATRIX.o \
	${OBJECTDIR}/_ext/c32defab/Error.o \
	${OBJECTDIR}/_ext/c32defab/Functions.o \
	${OBJECTDIR}/_ext/c32defab/HighPrec.o \
	${OBJECTDIR}/_ext/c32defab/IntegerMatrix.o \
	${OBJECTDIR}/_ext/c32defab/IntegerVector.o \
	${OBJECTDIR}/_ext/c32defab/Interval.o \
	${OBJECTDIR}/_ext/c32defab/IntervalMatrix.o \
	${OBJECTDIR}/_ext/c32defab/IntervalVector.o \
	${OBJECTDIR}/_ext/c32defab/LSS.o \
	${OBJECTDIR}/_ext/c32defab/LongInterval.o \
	${OBJECTDIR}/_ext/c32defab/LongReal.o \
	${OBJECTDIR}/_ext/c32defab/Matrix.o \
	${OBJECTDIR}/_ext/c32defab/NiceIntervalIO.o \
	${OBJECTDIR}/_ext/c32defab/RealOp.o \
	${OBJECTDIR}/_ext/c32defab/Utilities.o \
	${OBJECTDIR}/_ext/c32defab/Vector.o

# Test Directory
TESTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}/tests

# Test Files
TESTFILES= \
	${TESTDIR}/TestFiles/f1

# Test Object Files
TESTOBJECTFILES= \
	${TESTDIR}/_ext/a2b90085/Teste_PROFIL.o

# C Compiler Flags
CFLAGS=-m64

# CC Compiler Flags
CCFLAGS=-m64
CXXFLAGS=-m64

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libprofil.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libprofil.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libprofil.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libprofil.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libprofil.a

${OBJECTDIR}/_ext/c32d8f73/Bias0.o: ../src/BIAS/Bias0.c
	${MKDIR} -p ${OBJECTDIR}/_ext/c32d8f73
	${RM} "$@.d"
	$(COMPILE.c) -g -I../include -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32d8f73/Bias0.o ../src/BIAS/Bias0.c

${OBJECTDIR}/_ext/c32d8f73/Bias0Ext.o: ../src/BIAS/Bias0Ext.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/c32d8f73
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I../include -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32d8f73/Bias0Ext.o ../src/BIAS/Bias0Ext.cpp

${OBJECTDIR}/_ext/c32d8f73/Bias1.o: ../src/BIAS/Bias1.c
	${MKDIR} -p ${OBJECTDIR}/_ext/c32d8f73
	${RM} "$@.d"
	$(COMPILE.c) -g -I../include -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32d8f73/Bias1.o ../src/BIAS/Bias1.c

${OBJECTDIR}/_ext/c32d8f73/Bias2.o: ../src/BIAS/Bias2.c
	${MKDIR} -p ${OBJECTDIR}/_ext/c32d8f73
	${RM} "$@.d"
	$(COMPILE.c) -g -I../include -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32d8f73/Bias2.o ../src/BIAS/Bias2.c

${OBJECTDIR}/_ext/c32d8f73/BiasF.o: ../src/BIAS/BiasF.c
	${MKDIR} -p ${OBJECTDIR}/_ext/c32d8f73
	${RM} "$@.d"
	$(COMPILE.c) -g -I../include -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32d8f73/BiasF.o ../src/BIAS/BiasF.c

${OBJECTDIR}/_ext/c32d8f73/BiasFExt.o: ../src/BIAS/BiasFExt.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/c32d8f73
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I../include -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32d8f73/BiasFExt.o ../src/BIAS/BiasFExt.cpp

${OBJECTDIR}/_ext/c32d8f73/BiasRnd.o: ../src/BIAS/BiasRnd.c
	${MKDIR} -p ${OBJECTDIR}/_ext/c32d8f73
	${RM} "$@.d"
	$(COMPILE.c) -g -I../include -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32d8f73/BiasRnd.o ../src/BIAS/BiasRnd.c

${OBJECTDIR}/_ext/c32d8f73/Rounding.o: ../src/BIAS/Rounding.c
	${MKDIR} -p ${OBJECTDIR}/_ext/c32d8f73
	${RM} "$@.d"
	$(COMPILE.c) -g -I../include -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32d8f73/Rounding.o ../src/BIAS/Rounding.c

${OBJECTDIR}/_ext/c32defab/Complex.o: ../src/Base/Complex.C
	${MKDIR} -p ${OBJECTDIR}/_ext/c32defab
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I../include -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32defab/Complex.o ../src/Base/Complex.C

${OBJECTDIR}/_ext/c32defab/Constants.o: ../src/Base/Constants.C
	${MKDIR} -p ${OBJECTDIR}/_ext/c32defab
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I../include -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32defab/Constants.o ../src/Base/Constants.C

${OBJECTDIR}/_ext/c32defab/EFunctions.o: ../src/Base/EFunctions.C
	${MKDIR} -p ${OBJECTDIR}/_ext/c32defab
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I../include -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32defab/EFunctions.o ../src/Base/EFunctions.C

${OBJECTDIR}/_ext/c32defab/EINTERVAL.o: ../src/Base/EINTERVAL.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/c32defab
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I../include -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32defab/EINTERVAL.o ../src/Base/EINTERVAL.cpp

${OBJECTDIR}/_ext/c32defab/EINTERVALVECTOR.o: ../src/Base/EINTERVALVECTOR.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/c32defab
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I../include -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32defab/EINTERVALVECTOR.o ../src/Base/EINTERVALVECTOR.cpp

${OBJECTDIR}/_ext/c32defab/EINTERVAL_MATRIX.o: ../src/Base/EINTERVAL_MATRIX.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/c32defab
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I../include -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32defab/EINTERVAL_MATRIX.o ../src/Base/EINTERVAL_MATRIX.cpp

${OBJECTDIR}/_ext/c32defab/Error.o: ../src/Base/Error.C
	${MKDIR} -p ${OBJECTDIR}/_ext/c32defab
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I../include -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32defab/Error.o ../src/Base/Error.C

${OBJECTDIR}/_ext/c32defab/Functions.o: ../src/Base/Functions.C
	${MKDIR} -p ${OBJECTDIR}/_ext/c32defab
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I../include -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32defab/Functions.o ../src/Base/Functions.C

${OBJECTDIR}/_ext/c32defab/HighPrec.o: ../src/Base/HighPrec.C
	${MKDIR} -p ${OBJECTDIR}/_ext/c32defab
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I../include -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32defab/HighPrec.o ../src/Base/HighPrec.C

${OBJECTDIR}/_ext/c32defab/IntegerMatrix.o: ../src/Base/IntegerMatrix.C
	${MKDIR} -p ${OBJECTDIR}/_ext/c32defab
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I../include -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32defab/IntegerMatrix.o ../src/Base/IntegerMatrix.C

${OBJECTDIR}/_ext/c32defab/IntegerVector.o: ../src/Base/IntegerVector.C
	${MKDIR} -p ${OBJECTDIR}/_ext/c32defab
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I../include -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32defab/IntegerVector.o ../src/Base/IntegerVector.C

${OBJECTDIR}/_ext/c32defab/Interval.o: ../src/Base/Interval.C
	${MKDIR} -p ${OBJECTDIR}/_ext/c32defab
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I../include -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32defab/Interval.o ../src/Base/Interval.C

${OBJECTDIR}/_ext/c32defab/IntervalMatrix.o: ../src/Base/IntervalMatrix.C
	${MKDIR} -p ${OBJECTDIR}/_ext/c32defab
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I../include -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32defab/IntervalMatrix.o ../src/Base/IntervalMatrix.C

${OBJECTDIR}/_ext/c32defab/IntervalVector.o: ../src/Base/IntervalVector.C
	${MKDIR} -p ${OBJECTDIR}/_ext/c32defab
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I../include -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32defab/IntervalVector.o ../src/Base/IntervalVector.C

${OBJECTDIR}/_ext/c32defab/LSS.o: ../src/Base/LSS.C
	${MKDIR} -p ${OBJECTDIR}/_ext/c32defab
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I../include -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32defab/LSS.o ../src/Base/LSS.C

${OBJECTDIR}/_ext/c32defab/LongInterval.o: ../src/Base/LongInterval.C
	${MKDIR} -p ${OBJECTDIR}/_ext/c32defab
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I../include -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32defab/LongInterval.o ../src/Base/LongInterval.C

${OBJECTDIR}/_ext/c32defab/LongReal.o: ../src/Base/LongReal.C
	${MKDIR} -p ${OBJECTDIR}/_ext/c32defab
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I../include -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32defab/LongReal.o ../src/Base/LongReal.C

${OBJECTDIR}/_ext/c32defab/Matrix.o: ../src/Base/Matrix.C
	${MKDIR} -p ${OBJECTDIR}/_ext/c32defab
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I../include -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32defab/Matrix.o ../src/Base/Matrix.C

${OBJECTDIR}/_ext/c32defab/NiceIntervalIO.o: ../src/Base/NiceIntervalIO.C
	${MKDIR} -p ${OBJECTDIR}/_ext/c32defab
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I../include -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32defab/NiceIntervalIO.o ../src/Base/NiceIntervalIO.C

${OBJECTDIR}/_ext/c32defab/RealOp.o: ../src/Base/RealOp.c
	${MKDIR} -p ${OBJECTDIR}/_ext/c32defab
	${RM} "$@.d"
	$(COMPILE.c) -g -I../include -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32defab/RealOp.o ../src/Base/RealOp.c

${OBJECTDIR}/_ext/c32defab/Utilities.o: ../src/Base/Utilities.C
	${MKDIR} -p ${OBJECTDIR}/_ext/c32defab
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I../include -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32defab/Utilities.o ../src/Base/Utilities.C

${OBJECTDIR}/_ext/c32defab/Vector.o: ../src/Base/Vector.C
	${MKDIR} -p ${OBJECTDIR}/_ext/c32defab
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I../include -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32defab/Vector.o ../src/Base/Vector.C

# Subprojects
.build-subprojects:

# Build Test Targets
.build-tests-conf: .build-tests-subprojects .build-conf ${TESTFILES}
.build-tests-subprojects:

${TESTDIR}/TestFiles/f1: ${TESTDIR}/_ext/a2b90085/Teste_PROFIL.o ${OBJECTFILES:%.o=%_nomain.o}
	${MKDIR} -p ${TESTDIR}/TestFiles
	${LINK.cc} -o ${TESTDIR}/TestFiles/f1 $^ ${LDLIBSOPTIONS}   


${TESTDIR}/_ext/a2b90085/Teste_PROFIL.o: ../src/BIAS/tests/Teste\ PROFIL.cpp 
	${MKDIR} -p ${TESTDIR}/_ext/a2b90085
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I../include -I. -std=c++14 -MMD -MP -MF "$@.d" -o ${TESTDIR}/_ext/a2b90085/Teste_PROFIL.o ../src/BIAS/tests/Teste\ PROFIL.cpp


${OBJECTDIR}/_ext/c32d8f73/Bias0_nomain.o: ${OBJECTDIR}/_ext/c32d8f73/Bias0.o ../src/BIAS/Bias0.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/c32d8f73
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/c32d8f73/Bias0.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../include -std=c11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32d8f73/Bias0_nomain.o ../src/BIAS/Bias0.c;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/c32d8f73/Bias0.o ${OBJECTDIR}/_ext/c32d8f73/Bias0_nomain.o;\
	fi

${OBJECTDIR}/_ext/c32d8f73/Bias0Ext_nomain.o: ${OBJECTDIR}/_ext/c32d8f73/Bias0Ext.o ../src/BIAS/Bias0Ext.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/c32d8f73
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/c32d8f73/Bias0Ext.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -I../include -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32d8f73/Bias0Ext_nomain.o ../src/BIAS/Bias0Ext.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/c32d8f73/Bias0Ext.o ${OBJECTDIR}/_ext/c32d8f73/Bias0Ext_nomain.o;\
	fi

${OBJECTDIR}/_ext/c32d8f73/Bias1_nomain.o: ${OBJECTDIR}/_ext/c32d8f73/Bias1.o ../src/BIAS/Bias1.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/c32d8f73
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/c32d8f73/Bias1.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../include -std=c11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32d8f73/Bias1_nomain.o ../src/BIAS/Bias1.c;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/c32d8f73/Bias1.o ${OBJECTDIR}/_ext/c32d8f73/Bias1_nomain.o;\
	fi

${OBJECTDIR}/_ext/c32d8f73/Bias2_nomain.o: ${OBJECTDIR}/_ext/c32d8f73/Bias2.o ../src/BIAS/Bias2.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/c32d8f73
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/c32d8f73/Bias2.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../include -std=c11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32d8f73/Bias2_nomain.o ../src/BIAS/Bias2.c;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/c32d8f73/Bias2.o ${OBJECTDIR}/_ext/c32d8f73/Bias2_nomain.o;\
	fi

${OBJECTDIR}/_ext/c32d8f73/BiasF_nomain.o: ${OBJECTDIR}/_ext/c32d8f73/BiasF.o ../src/BIAS/BiasF.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/c32d8f73
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/c32d8f73/BiasF.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../include -std=c11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32d8f73/BiasF_nomain.o ../src/BIAS/BiasF.c;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/c32d8f73/BiasF.o ${OBJECTDIR}/_ext/c32d8f73/BiasF_nomain.o;\
	fi

${OBJECTDIR}/_ext/c32d8f73/BiasFExt_nomain.o: ${OBJECTDIR}/_ext/c32d8f73/BiasFExt.o ../src/BIAS/BiasFExt.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/c32d8f73
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/c32d8f73/BiasFExt.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -I../include -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32d8f73/BiasFExt_nomain.o ../src/BIAS/BiasFExt.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/c32d8f73/BiasFExt.o ${OBJECTDIR}/_ext/c32d8f73/BiasFExt_nomain.o;\
	fi

${OBJECTDIR}/_ext/c32d8f73/BiasRnd_nomain.o: ${OBJECTDIR}/_ext/c32d8f73/BiasRnd.o ../src/BIAS/BiasRnd.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/c32d8f73
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/c32d8f73/BiasRnd.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../include -std=c11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32d8f73/BiasRnd_nomain.o ../src/BIAS/BiasRnd.c;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/c32d8f73/BiasRnd.o ${OBJECTDIR}/_ext/c32d8f73/BiasRnd_nomain.o;\
	fi

${OBJECTDIR}/_ext/c32d8f73/Rounding_nomain.o: ${OBJECTDIR}/_ext/c32d8f73/Rounding.o ../src/BIAS/Rounding.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/c32d8f73
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/c32d8f73/Rounding.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../include -std=c11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32d8f73/Rounding_nomain.o ../src/BIAS/Rounding.c;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/c32d8f73/Rounding.o ${OBJECTDIR}/_ext/c32d8f73/Rounding_nomain.o;\
	fi

${OBJECTDIR}/_ext/c32defab/Complex_nomain.o: ${OBJECTDIR}/_ext/c32defab/Complex.o ../src/Base/Complex.C 
	${MKDIR} -p ${OBJECTDIR}/_ext/c32defab
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/c32defab/Complex.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -I../include -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32defab/Complex_nomain.o ../src/Base/Complex.C;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/c32defab/Complex.o ${OBJECTDIR}/_ext/c32defab/Complex_nomain.o;\
	fi

${OBJECTDIR}/_ext/c32defab/Constants_nomain.o: ${OBJECTDIR}/_ext/c32defab/Constants.o ../src/Base/Constants.C 
	${MKDIR} -p ${OBJECTDIR}/_ext/c32defab
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/c32defab/Constants.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -I../include -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32defab/Constants_nomain.o ../src/Base/Constants.C;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/c32defab/Constants.o ${OBJECTDIR}/_ext/c32defab/Constants_nomain.o;\
	fi

${OBJECTDIR}/_ext/c32defab/EFunctions_nomain.o: ${OBJECTDIR}/_ext/c32defab/EFunctions.o ../src/Base/EFunctions.C 
	${MKDIR} -p ${OBJECTDIR}/_ext/c32defab
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/c32defab/EFunctions.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -I../include -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32defab/EFunctions_nomain.o ../src/Base/EFunctions.C;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/c32defab/EFunctions.o ${OBJECTDIR}/_ext/c32defab/EFunctions_nomain.o;\
	fi

${OBJECTDIR}/_ext/c32defab/EINTERVAL_nomain.o: ${OBJECTDIR}/_ext/c32defab/EINTERVAL.o ../src/Base/EINTERVAL.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/c32defab
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/c32defab/EINTERVAL.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -I../include -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32defab/EINTERVAL_nomain.o ../src/Base/EINTERVAL.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/c32defab/EINTERVAL.o ${OBJECTDIR}/_ext/c32defab/EINTERVAL_nomain.o;\
	fi

${OBJECTDIR}/_ext/c32defab/EINTERVALVECTOR_nomain.o: ${OBJECTDIR}/_ext/c32defab/EINTERVALVECTOR.o ../src/Base/EINTERVALVECTOR.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/c32defab
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/c32defab/EINTERVALVECTOR.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -I../include -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32defab/EINTERVALVECTOR_nomain.o ../src/Base/EINTERVALVECTOR.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/c32defab/EINTERVALVECTOR.o ${OBJECTDIR}/_ext/c32defab/EINTERVALVECTOR_nomain.o;\
	fi

${OBJECTDIR}/_ext/c32defab/EINTERVAL_MATRIX_nomain.o: ${OBJECTDIR}/_ext/c32defab/EINTERVAL_MATRIX.o ../src/Base/EINTERVAL_MATRIX.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/c32defab
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/c32defab/EINTERVAL_MATRIX.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -I../include -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32defab/EINTERVAL_MATRIX_nomain.o ../src/Base/EINTERVAL_MATRIX.cpp;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/c32defab/EINTERVAL_MATRIX.o ${OBJECTDIR}/_ext/c32defab/EINTERVAL_MATRIX_nomain.o;\
	fi

${OBJECTDIR}/_ext/c32defab/Error_nomain.o: ${OBJECTDIR}/_ext/c32defab/Error.o ../src/Base/Error.C 
	${MKDIR} -p ${OBJECTDIR}/_ext/c32defab
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/c32defab/Error.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -I../include -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32defab/Error_nomain.o ../src/Base/Error.C;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/c32defab/Error.o ${OBJECTDIR}/_ext/c32defab/Error_nomain.o;\
	fi

${OBJECTDIR}/_ext/c32defab/Functions_nomain.o: ${OBJECTDIR}/_ext/c32defab/Functions.o ../src/Base/Functions.C 
	${MKDIR} -p ${OBJECTDIR}/_ext/c32defab
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/c32defab/Functions.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -I../include -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32defab/Functions_nomain.o ../src/Base/Functions.C;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/c32defab/Functions.o ${OBJECTDIR}/_ext/c32defab/Functions_nomain.o;\
	fi

${OBJECTDIR}/_ext/c32defab/HighPrec_nomain.o: ${OBJECTDIR}/_ext/c32defab/HighPrec.o ../src/Base/HighPrec.C 
	${MKDIR} -p ${OBJECTDIR}/_ext/c32defab
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/c32defab/HighPrec.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -I../include -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32defab/HighPrec_nomain.o ../src/Base/HighPrec.C;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/c32defab/HighPrec.o ${OBJECTDIR}/_ext/c32defab/HighPrec_nomain.o;\
	fi

${OBJECTDIR}/_ext/c32defab/IntegerMatrix_nomain.o: ${OBJECTDIR}/_ext/c32defab/IntegerMatrix.o ../src/Base/IntegerMatrix.C 
	${MKDIR} -p ${OBJECTDIR}/_ext/c32defab
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/c32defab/IntegerMatrix.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -I../include -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32defab/IntegerMatrix_nomain.o ../src/Base/IntegerMatrix.C;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/c32defab/IntegerMatrix.o ${OBJECTDIR}/_ext/c32defab/IntegerMatrix_nomain.o;\
	fi

${OBJECTDIR}/_ext/c32defab/IntegerVector_nomain.o: ${OBJECTDIR}/_ext/c32defab/IntegerVector.o ../src/Base/IntegerVector.C 
	${MKDIR} -p ${OBJECTDIR}/_ext/c32defab
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/c32defab/IntegerVector.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -I../include -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32defab/IntegerVector_nomain.o ../src/Base/IntegerVector.C;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/c32defab/IntegerVector.o ${OBJECTDIR}/_ext/c32defab/IntegerVector_nomain.o;\
	fi

${OBJECTDIR}/_ext/c32defab/Interval_nomain.o: ${OBJECTDIR}/_ext/c32defab/Interval.o ../src/Base/Interval.C 
	${MKDIR} -p ${OBJECTDIR}/_ext/c32defab
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/c32defab/Interval.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -I../include -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32defab/Interval_nomain.o ../src/Base/Interval.C;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/c32defab/Interval.o ${OBJECTDIR}/_ext/c32defab/Interval_nomain.o;\
	fi

${OBJECTDIR}/_ext/c32defab/IntervalMatrix_nomain.o: ${OBJECTDIR}/_ext/c32defab/IntervalMatrix.o ../src/Base/IntervalMatrix.C 
	${MKDIR} -p ${OBJECTDIR}/_ext/c32defab
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/c32defab/IntervalMatrix.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -I../include -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32defab/IntervalMatrix_nomain.o ../src/Base/IntervalMatrix.C;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/c32defab/IntervalMatrix.o ${OBJECTDIR}/_ext/c32defab/IntervalMatrix_nomain.o;\
	fi

${OBJECTDIR}/_ext/c32defab/IntervalVector_nomain.o: ${OBJECTDIR}/_ext/c32defab/IntervalVector.o ../src/Base/IntervalVector.C 
	${MKDIR} -p ${OBJECTDIR}/_ext/c32defab
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/c32defab/IntervalVector.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -I../include -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32defab/IntervalVector_nomain.o ../src/Base/IntervalVector.C;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/c32defab/IntervalVector.o ${OBJECTDIR}/_ext/c32defab/IntervalVector_nomain.o;\
	fi

${OBJECTDIR}/_ext/c32defab/LSS_nomain.o: ${OBJECTDIR}/_ext/c32defab/LSS.o ../src/Base/LSS.C 
	${MKDIR} -p ${OBJECTDIR}/_ext/c32defab
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/c32defab/LSS.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -I../include -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32defab/LSS_nomain.o ../src/Base/LSS.C;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/c32defab/LSS.o ${OBJECTDIR}/_ext/c32defab/LSS_nomain.o;\
	fi

${OBJECTDIR}/_ext/c32defab/LongInterval_nomain.o: ${OBJECTDIR}/_ext/c32defab/LongInterval.o ../src/Base/LongInterval.C 
	${MKDIR} -p ${OBJECTDIR}/_ext/c32defab
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/c32defab/LongInterval.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -I../include -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32defab/LongInterval_nomain.o ../src/Base/LongInterval.C;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/c32defab/LongInterval.o ${OBJECTDIR}/_ext/c32defab/LongInterval_nomain.o;\
	fi

${OBJECTDIR}/_ext/c32defab/LongReal_nomain.o: ${OBJECTDIR}/_ext/c32defab/LongReal.o ../src/Base/LongReal.C 
	${MKDIR} -p ${OBJECTDIR}/_ext/c32defab
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/c32defab/LongReal.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -I../include -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32defab/LongReal_nomain.o ../src/Base/LongReal.C;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/c32defab/LongReal.o ${OBJECTDIR}/_ext/c32defab/LongReal_nomain.o;\
	fi

${OBJECTDIR}/_ext/c32defab/Matrix_nomain.o: ${OBJECTDIR}/_ext/c32defab/Matrix.o ../src/Base/Matrix.C 
	${MKDIR} -p ${OBJECTDIR}/_ext/c32defab
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/c32defab/Matrix.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -I../include -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32defab/Matrix_nomain.o ../src/Base/Matrix.C;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/c32defab/Matrix.o ${OBJECTDIR}/_ext/c32defab/Matrix_nomain.o;\
	fi

${OBJECTDIR}/_ext/c32defab/NiceIntervalIO_nomain.o: ${OBJECTDIR}/_ext/c32defab/NiceIntervalIO.o ../src/Base/NiceIntervalIO.C 
	${MKDIR} -p ${OBJECTDIR}/_ext/c32defab
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/c32defab/NiceIntervalIO.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -I../include -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32defab/NiceIntervalIO_nomain.o ../src/Base/NiceIntervalIO.C;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/c32defab/NiceIntervalIO.o ${OBJECTDIR}/_ext/c32defab/NiceIntervalIO_nomain.o;\
	fi

${OBJECTDIR}/_ext/c32defab/RealOp_nomain.o: ${OBJECTDIR}/_ext/c32defab/RealOp.o ../src/Base/RealOp.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/c32defab
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/c32defab/RealOp.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.c) -g -I../include -std=c11 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32defab/RealOp_nomain.o ../src/Base/RealOp.c;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/c32defab/RealOp.o ${OBJECTDIR}/_ext/c32defab/RealOp_nomain.o;\
	fi

${OBJECTDIR}/_ext/c32defab/Utilities_nomain.o: ${OBJECTDIR}/_ext/c32defab/Utilities.o ../src/Base/Utilities.C 
	${MKDIR} -p ${OBJECTDIR}/_ext/c32defab
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/c32defab/Utilities.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -I../include -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32defab/Utilities_nomain.o ../src/Base/Utilities.C;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/c32defab/Utilities.o ${OBJECTDIR}/_ext/c32defab/Utilities_nomain.o;\
	fi

${OBJECTDIR}/_ext/c32defab/Vector_nomain.o: ${OBJECTDIR}/_ext/c32defab/Vector.o ../src/Base/Vector.C 
	${MKDIR} -p ${OBJECTDIR}/_ext/c32defab
	@NMOUTPUT=`${NM} ${OBJECTDIR}/_ext/c32defab/Vector.o`; \
	if (echo "$$NMOUTPUT" | ${GREP} '|main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T main$$') || \
	   (echo "$$NMOUTPUT" | ${GREP} 'T _main$$'); \
	then  \
	    ${RM} "$@.d";\
	    $(COMPILE.cc) -O3 -I../include -std=c++14 -Dmain=__nomain -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32defab/Vector_nomain.o ../src/Base/Vector.C;\
	else  \
	    ${CP} ${OBJECTDIR}/_ext/c32defab/Vector.o ${OBJECTDIR}/_ext/c32defab/Vector_nomain.o;\
	fi

# Run Test Targets
.test-conf:
	@if [ "${TEST}" = "" ]; \
	then  \
	    ${TESTDIR}/TestFiles/f1 || true; \
	else  \
	    ./${TEST} || true; \
	fi

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
