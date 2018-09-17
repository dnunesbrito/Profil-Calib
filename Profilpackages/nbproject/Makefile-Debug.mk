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
CCC=g++
CXX=g++
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
	${OBJECTDIR}/_ext/189662bc/AutoDiff.o \
	${OBJECTDIR}/_ext/189662bc/IntervalAutoDiff.o \
	${OBJECTDIR}/_ext/afd184a8/AppList.o \
	${OBJECTDIR}/_ext/afd184a8/Expand.o \
	${OBJECTDIR}/_ext/afd184a8/UnconstrainedOpt.o \
	${OBJECTDIR}/_ext/afd184a8/VecList.o \
	${OBJECTDIR}/_ext/afd184a8/VecUtils.o \
	${OBJECTDIR}/_ext/b704acca/LinOpt.o \
	${OBJECTDIR}/_ext/34280fb0/Brent.o \
	${OBJECTDIR}/_ext/34280fb0/NelderMead.o \
	${OBJECTDIR}/_ext/530a0d54/MiscFunctions.o \
	${OBJECTDIR}/_ext/2bf81100/NLF.o \
	${OBJECTDIR}/_ext/2bf81100/NLF2.o \
	${OBJECTDIR}/_ext/9b54e027/NonLinOpt.o \
	${OBJECTDIR}/_ext/2e7522b3/OverDetLinSys.o \
	${OBJECTDIR}/_ext/3a9aca05/PolinomialRoots.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libprofilpackages.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libprofilpackages.a: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libprofilpackages.a
	${AR} -rv ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libprofilpackages.a ${OBJECTFILES} 
	$(RANLIB) ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libprofilpackages.a

${OBJECTDIR}/_ext/189662bc/AutoDiff.o: ../src/Packages/AutoDiff/AutoDiff.C
	${MKDIR} -p ${OBJECTDIR}/_ext/189662bc
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../include -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/189662bc/AutoDiff.o ../src/Packages/AutoDiff/AutoDiff.C

${OBJECTDIR}/_ext/189662bc/IntervalAutoDiff.o: ../src/Packages/AutoDiff/IntervalAutoDiff.C
	${MKDIR} -p ${OBJECTDIR}/_ext/189662bc
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../include -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/189662bc/IntervalAutoDiff.o ../src/Packages/AutoDiff/IntervalAutoDiff.C

${OBJECTDIR}/_ext/afd184a8/AppList.o: ../src/Packages/GlobalOpt/AppList.C
	${MKDIR} -p ${OBJECTDIR}/_ext/afd184a8
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../include -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/afd184a8/AppList.o ../src/Packages/GlobalOpt/AppList.C

${OBJECTDIR}/_ext/afd184a8/Expand.o: ../src/Packages/GlobalOpt/Expand.C
	${MKDIR} -p ${OBJECTDIR}/_ext/afd184a8
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../include -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/afd184a8/Expand.o ../src/Packages/GlobalOpt/Expand.C

${OBJECTDIR}/_ext/afd184a8/UnconstrainedOpt.o: ../src/Packages/GlobalOpt/UnconstrainedOpt.C
	${MKDIR} -p ${OBJECTDIR}/_ext/afd184a8
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../include -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/afd184a8/UnconstrainedOpt.o ../src/Packages/GlobalOpt/UnconstrainedOpt.C

${OBJECTDIR}/_ext/afd184a8/VecList.o: ../src/Packages/GlobalOpt/VecList.C
	${MKDIR} -p ${OBJECTDIR}/_ext/afd184a8
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../include -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/afd184a8/VecList.o ../src/Packages/GlobalOpt/VecList.C

${OBJECTDIR}/_ext/afd184a8/VecUtils.o: ../src/Packages/GlobalOpt/VecUtils.C
	${MKDIR} -p ${OBJECTDIR}/_ext/afd184a8
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../include -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/afd184a8/VecUtils.o ../src/Packages/GlobalOpt/VecUtils.C

${OBJECTDIR}/_ext/b704acca/LinOpt.o: ../src/Packages/LinOpt/LinOpt.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/b704acca
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../include -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/b704acca/LinOpt.o ../src/Packages/LinOpt/LinOpt.cpp

${OBJECTDIR}/_ext/34280fb0/Brent.o: ../src/Packages/LocalOpt/Brent.C
	${MKDIR} -p ${OBJECTDIR}/_ext/34280fb0
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../include -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/34280fb0/Brent.o ../src/Packages/LocalOpt/Brent.C

${OBJECTDIR}/_ext/34280fb0/NelderMead.o: ../src/Packages/LocalOpt/NelderMead.C
	${MKDIR} -p ${OBJECTDIR}/_ext/34280fb0
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../include -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/34280fb0/NelderMead.o ../src/Packages/LocalOpt/NelderMead.C

${OBJECTDIR}/_ext/530a0d54/MiscFunctions.o: ../src/Packages/Misc/MiscFunctions.c
	${MKDIR} -p ${OBJECTDIR}/_ext/530a0d54
	${RM} "$@.d"
	$(COMPILE.c) -g -I../include -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/530a0d54/MiscFunctions.o ../src/Packages/Misc/MiscFunctions.c

${OBJECTDIR}/_ext/2bf81100/NLF.o: ../src/Packages/NLF/NLF.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/2bf81100
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../include -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2bf81100/NLF.o ../src/Packages/NLF/NLF.cpp

${OBJECTDIR}/_ext/2bf81100/NLF2.o: ../src/Packages/NLF/NLF2.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/2bf81100
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../include -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2bf81100/NLF2.o ../src/Packages/NLF/NLF2.cpp

${OBJECTDIR}/_ext/9b54e027/NonLinOpt.o: ../src/Packages/NonLinOpt/NonLinOpt.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/9b54e027
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../include -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/9b54e027/NonLinOpt.o ../src/Packages/NonLinOpt/NonLinOpt.cpp

${OBJECTDIR}/_ext/2e7522b3/OverDetLinSys.o: ../src/Packages/OverdetLinSys/OverDetLinSys.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/2e7522b3
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../include -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2e7522b3/OverDetLinSys.o ../src/Packages/OverdetLinSys/OverDetLinSys.cpp

${OBJECTDIR}/_ext/3a9aca05/PolinomialRoots.o: ../src/Packages/PolinomialRoots/PolinomialRoots.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/3a9aca05
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../include -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/3a9aca05/PolinomialRoots.o ../src/Packages/PolinomialRoots/PolinomialRoots.cpp

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
