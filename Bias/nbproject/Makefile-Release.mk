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
CND_CONF=Release
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
	${OBJECTDIR}/_ext/c32d8f73/SSEBIASINTERVAL.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ../lib/libbias.a

../lib/libbias.a: ${OBJECTFILES}
	${MKDIR} -p ../lib
	${RM} ../lib/libbias.a
	${AR} -rv ../lib/libbias.a ${OBJECTFILES} 
	$(RANLIB) ../lib/libbias.a

${OBJECTDIR}/_ext/c32d8f73/Bias0.o: ../src/BIAS/Bias0.c
	${MKDIR} -p ${OBJECTDIR}/_ext/c32d8f73
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I../include -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32d8f73/Bias0.o ../src/BIAS/Bias0.c

${OBJECTDIR}/_ext/c32d8f73/Bias0Ext.o: ../src/BIAS/Bias0Ext.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/c32d8f73
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32d8f73/Bias0Ext.o ../src/BIAS/Bias0Ext.cpp

${OBJECTDIR}/_ext/c32d8f73/Bias1.o: ../src/BIAS/Bias1.c
	${MKDIR} -p ${OBJECTDIR}/_ext/c32d8f73
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I../include -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32d8f73/Bias1.o ../src/BIAS/Bias1.c

${OBJECTDIR}/_ext/c32d8f73/Bias2.o: ../src/BIAS/Bias2.c
	${MKDIR} -p ${OBJECTDIR}/_ext/c32d8f73
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I../include -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32d8f73/Bias2.o ../src/BIAS/Bias2.c

${OBJECTDIR}/_ext/c32d8f73/BiasF.o: ../src/BIAS/BiasF.c
	${MKDIR} -p ${OBJECTDIR}/_ext/c32d8f73
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I../include -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32d8f73/BiasF.o ../src/BIAS/BiasF.c

${OBJECTDIR}/_ext/c32d8f73/BiasFExt.o: ../src/BIAS/BiasFExt.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/c32d8f73
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32d8f73/BiasFExt.o ../src/BIAS/BiasFExt.cpp

${OBJECTDIR}/_ext/c32d8f73/BiasRnd.o: ../src/BIAS/BiasRnd.c
	${MKDIR} -p ${OBJECTDIR}/_ext/c32d8f73
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I../include -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32d8f73/BiasRnd.o ../src/BIAS/BiasRnd.c

${OBJECTDIR}/_ext/c32d8f73/Rounding.o: ../src/BIAS/Rounding.c
	${MKDIR} -p ${OBJECTDIR}/_ext/c32d8f73
	${RM} "$@.d"
	$(COMPILE.c) -O2 -I../include -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32d8f73/Rounding.o ../src/BIAS/Rounding.c

${OBJECTDIR}/_ext/c32d8f73/SSEBIASINTERVAL.o: ../src/BIAS/SSEBIASINTERVAL.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/c32d8f73
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I../include -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/c32d8f73/SSEBIASINTERVAL.o ../src/BIAS/SSEBIASINTERVAL.cpp

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
