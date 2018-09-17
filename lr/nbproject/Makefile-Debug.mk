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
	${OBJECTDIR}/_ext/cfb868c0/DynMem.o \
	${OBJECTDIR}/_ext/cfb868c0/LiCvt1.o \
	${OBJECTDIR}/_ext/cfb868c0/LiCvt2.o \
	${OBJECTDIR}/_ext/cfb868c0/LiMem.o \
	${OBJECTDIR}/_ext/cfb868c0/LiOp0.o \
	${OBJECTDIR}/_ext/cfb868c0/LiOp1.o \
	${OBJECTDIR}/_ext/cfb868c0/LrCvt0.o \
	${OBJECTDIR}/_ext/cfb868c0/LrCvt1.o \
	${OBJECTDIR}/_ext/cfb868c0/LrCvt2.o \
	${OBJECTDIR}/_ext/cfb868c0/LrIntern.o \
	${OBJECTDIR}/_ext/cfb868c0/LrMem.o \
	${OBJECTDIR}/_ext/cfb868c0/LrOp0.o \
	${OBJECTDIR}/_ext/cfb868c0/LrOp1.o \
	${OBJECTDIR}/_ext/cfb868c0/LrOp2.o \
	${OBJECTDIR}/_ext/cfb868c0/LrSc.o


# C Compiler Flags
CFLAGS=-m64

# CC Compiler Flags
CCFLAGS=-m64
CXXFLAGS=-m64

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=--64

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ../lib/liblr.a

../lib/liblr.a: ${OBJECTFILES}
	${MKDIR} -p ../lib
	${RM} ../lib/liblr.a
	${AR} -rv ../lib/liblr.a ${OBJECTFILES} 
	$(RANLIB) ../lib/liblr.a

${OBJECTDIR}/_ext/cfb868c0/DynMem.o: ../src/lr/DynMem.c
	${MKDIR} -p ${OBJECTDIR}/_ext/cfb868c0
	${RM} "$@.d"
	$(COMPILE.c) -g -I../include -I../ALIAS_TAR -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/cfb868c0/DynMem.o ../src/lr/DynMem.c

${OBJECTDIR}/_ext/cfb868c0/LiCvt1.o: ../src/lr/LiCvt1.c
	${MKDIR} -p ${OBJECTDIR}/_ext/cfb868c0
	${RM} "$@.d"
	$(COMPILE.c) -g -I../include -I../ALIAS_TAR -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/cfb868c0/LiCvt1.o ../src/lr/LiCvt1.c

${OBJECTDIR}/_ext/cfb868c0/LiCvt2.o: ../src/lr/LiCvt2.c
	${MKDIR} -p ${OBJECTDIR}/_ext/cfb868c0
	${RM} "$@.d"
	$(COMPILE.c) -g -I../include -I../ALIAS_TAR -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/cfb868c0/LiCvt2.o ../src/lr/LiCvt2.c

${OBJECTDIR}/_ext/cfb868c0/LiMem.o: ../src/lr/LiMem.c
	${MKDIR} -p ${OBJECTDIR}/_ext/cfb868c0
	${RM} "$@.d"
	$(COMPILE.c) -g -I../include -I../ALIAS_TAR -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/cfb868c0/LiMem.o ../src/lr/LiMem.c

${OBJECTDIR}/_ext/cfb868c0/LiOp0.o: ../src/lr/LiOp0.c
	${MKDIR} -p ${OBJECTDIR}/_ext/cfb868c0
	${RM} "$@.d"
	$(COMPILE.c) -g -I../include -I../ALIAS_TAR -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/cfb868c0/LiOp0.o ../src/lr/LiOp0.c

${OBJECTDIR}/_ext/cfb868c0/LiOp1.o: ../src/lr/LiOp1.c
	${MKDIR} -p ${OBJECTDIR}/_ext/cfb868c0
	${RM} "$@.d"
	$(COMPILE.c) -g -I../include -I../ALIAS_TAR -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/cfb868c0/LiOp1.o ../src/lr/LiOp1.c

${OBJECTDIR}/_ext/cfb868c0/LrCvt0.o: ../src/lr/LrCvt0.c
	${MKDIR} -p ${OBJECTDIR}/_ext/cfb868c0
	${RM} "$@.d"
	$(COMPILE.c) -g -I../include -I../ALIAS_TAR -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/cfb868c0/LrCvt0.o ../src/lr/LrCvt0.c

${OBJECTDIR}/_ext/cfb868c0/LrCvt1.o: ../src/lr/LrCvt1.c
	${MKDIR} -p ${OBJECTDIR}/_ext/cfb868c0
	${RM} "$@.d"
	$(COMPILE.c) -g -I../include -I../ALIAS_TAR -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/cfb868c0/LrCvt1.o ../src/lr/LrCvt1.c

${OBJECTDIR}/_ext/cfb868c0/LrCvt2.o: ../src/lr/LrCvt2.c
	${MKDIR} -p ${OBJECTDIR}/_ext/cfb868c0
	${RM} "$@.d"
	$(COMPILE.c) -g -I../include -I../ALIAS_TAR -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/cfb868c0/LrCvt2.o ../src/lr/LrCvt2.c

${OBJECTDIR}/_ext/cfb868c0/LrIntern.o: ../src/lr/LrIntern.c
	${MKDIR} -p ${OBJECTDIR}/_ext/cfb868c0
	${RM} "$@.d"
	$(COMPILE.c) -g -I../include -I../ALIAS_TAR -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/cfb868c0/LrIntern.o ../src/lr/LrIntern.c

${OBJECTDIR}/_ext/cfb868c0/LrMem.o: ../src/lr/LrMem.c
	${MKDIR} -p ${OBJECTDIR}/_ext/cfb868c0
	${RM} "$@.d"
	$(COMPILE.c) -g -I../include -I../ALIAS_TAR -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/cfb868c0/LrMem.o ../src/lr/LrMem.c

${OBJECTDIR}/_ext/cfb868c0/LrOp0.o: ../src/lr/LrOp0.c
	${MKDIR} -p ${OBJECTDIR}/_ext/cfb868c0
	${RM} "$@.d"
	$(COMPILE.c) -g -I../include -I../ALIAS_TAR -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/cfb868c0/LrOp0.o ../src/lr/LrOp0.c

${OBJECTDIR}/_ext/cfb868c0/LrOp1.o: ../src/lr/LrOp1.c
	${MKDIR} -p ${OBJECTDIR}/_ext/cfb868c0
	${RM} "$@.d"
	$(COMPILE.c) -g -I../include -I../ALIAS_TAR -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/cfb868c0/LrOp1.o ../src/lr/LrOp1.c

${OBJECTDIR}/_ext/cfb868c0/LrOp2.o: ../src/lr/LrOp2.c
	${MKDIR} -p ${OBJECTDIR}/_ext/cfb868c0
	${RM} "$@.d"
	$(COMPILE.c) -g -I../include -I../ALIAS_TAR -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/cfb868c0/LrOp2.o ../src/lr/LrOp2.c

${OBJECTDIR}/_ext/cfb868c0/LrSc.o: ../src/lr/LrSc.c
	${MKDIR} -p ${OBJECTDIR}/_ext/cfb868c0
	${RM} "$@.d"
	$(COMPILE.c) -g -I../include -I../ALIAS_TAR -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/cfb868c0/LrSc.o ../src/lr/LrSc.c

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
