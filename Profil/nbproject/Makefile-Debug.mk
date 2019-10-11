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

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
