include /home/snacc/SNACC/snacc-1.3/makehead
include $(ORACLE_HOME)/precomp/lib/env_precomp.mk

TOP             = /home/snacc/SNACC/snacc-1.3

ASN1_SRC_DIR	= $(TOP)/asn1specs

ASN1_C_LIB_DIR	= $(TOP)/c-lib
ASN1_C_INC_DIR	= $(ASN1_C_LIB_DIR)/inc
MBUF_ASN1_LIB	= $(ASN1_C_LIB_DIR)/libasn1cmbuf.a
SBUF_ASN1_LIB	= $(ASN1_C_LIB_DIR)/libasn1csbuf.a
EBUF_ASN1_LIB	= $(ASN1_C_LIB_DIR)/libasn1cebuf.a

COMPILERDIR     = $(TOP)/compiler
SNACC           = $(COMPILERDIR)/snacc
USEFUL_TYPES    = $(ASN1_SRC_DIR)/asn-useful.asn1
SNACCFLAGS      = -u $(USEFUL_TYPES)

CPPFLAGS        += -I$(TOP) -I$(ASN1_C_INC_DIR) $(BUFFLAG) $(LENFLAG)
CFLAGS          += -I$(TOP) -I$(ASN1_C_INC_DIR) $(BUFFLAG) $(LENFLAG)

BUFFLAG		= -DUSE_SBUF

#-------------------------------------------------------------------------------

build: minbuf-def

min-def-obj:
	mkdir $@

min-def-obj/Logger.o \
min-def-obj/reader.o	\
min-def-obj/tap312.o	\
min-def-obj/rapout.o	\
min-def-obj/rap105.o	\
min-def-obj/ProcessStatus.o	\
min-def-obj/ProcessTAP.o:
	$(REASON)
	$(MAKE) BUFFLAG=-DUSE_MIN_BUF LENFLAG= `echo $(@D) | sed -e 's:/$$::'` $(@F) 
	mv $(@F) $@

ProcessTAP.c:
	$(PROC) $(PROCFLAGS) $(BUFFLAG) iname=ProcessTAP.pc
	$(PROC) $(PROCFLAGS) $(BUFFLAG) iname=ProcessStatus.pc
	$(CC) -g -DERROR_LOG_LEVEL=1 $(CFLAGS) -c ProcessTAP.c Logger.c

	
minbuf-def: ProcessTAP.c min-def-obj/tap312.o min-def-obj/ProcessTAP.o min-def-obj/ProcessStatus.o min-def-obj/reader.o min-def-obj/rapout.o min-def-obj/rap105.o min-def-obj/Logger.o
	$(REASON)
	cc -DERROR_LOG_LEVEL=5 -o $(EXE) min-def-obj/tap312.o min-def-obj/ProcessTAP.o min-def-obj/ProcessStatus.o min-def-obj/reader.o min-def-obj/rapout.o min-def-obj/rap105.o min-def-obj/Logger.o -L$(LIBHOME) $(PROLDLIBS) $(MBUF_ASN1_LIB)  

clean::
	$(RM) *.o *~ core .emacs*
	$(RM) -r *-def-obj *-indef-obj


OTTFLAGS=$(PCCFLAGS)
CLIBS= $(TTLIBS_QA) $(LDLIBS)
PRODUCT_LIBHOME=
MAKEFILE=$(ORACLE_HOME)/precomp/demo/proc/demo_proc.mk
PROCPLSFLAGS= SQLCHECK=SEMANTICS PARSE=FULL USERID=$(USERID)

PROCFLAGS=\
sys_include=$(ORACLE_HOME)/precomp/public \
sys_include=/usr/lib/gcc-lib/i386-redhat-linux/3.2.2/include \
sys_include=/usr/include \
sys_include=/home/snacc/SNACC/snacc-1.3 \
sys_include=/home/snacc/SNACC/snacc-1.3/c-lib/inc \
sys_include=$(ORACLE_HOME)/proc/syshdr \
sys_include=$(ORACLE_HOME)/rdbms/public \
sys_include=$(ASN1_C_INC_DIR) \
SQLCHECK=SEMANTICS USERID=$(USERID) PREFETCH=20000
#SQLCHECK=SEMANTICS USERID=$(USERID) SELECT_ERROR=NO

PROCPPFLAGS= code=cpp $(CPLUS_SYS_INCLUDE)
USERID=PM_CLIENT_WBS50/PM_CLIENT_WBS50@TTTEST
NETWORKHOME=$(ORACLE_HOME)/network/
PLSQLHOME=$(ORACLE_HOME)/plsql/
INCLUDE_PC=$(I_SYM). $(I_SYM)$(PRECOMPHOME)syshdr $(I_SYM)$(PRECOMPHOME)public $(I_SYM)$(RDBMSHOME)public $(I_SYM)$(RDBMSHOME)demo $(I_SYM)$(PLSQLHOME)public $(I_SYM)$(NETWORKHOME)public
INCLUDE=$(I_SYM). $(I_SYM)$(PRECOMPHOME)public $(I_SYM)$(RDBMSHOME)public $(I_SYM)$(RDBMSHOME)demo $(I_SYM)$(PLSQLHOME)public $(I_SYM)$(NETWORKHOME)public
