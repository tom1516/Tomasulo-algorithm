// Azelis Thomas
// AM:1310
#include "pin.H"

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

#include <queue>
#include <list>
#include <vector>
#include <new>

#include "sim.h"


// ---------------------------------------------------------------------------
// --------------------------------- KNOBS -----------------------------------
// ---------------------------------------------------------------------------
KNOB<UINT32> Knob_issue_width (KNOB_MODE_WRITEONCE, "pintool", "issue_width", "1", "issue width of the processor");
KNOB<UINT32> Knob_cdb_width   (KNOB_MODE_WRITEONCE, "pintool", "cdb_width", "1", "number of Common Data Busses (CDB)");

// ----------------- Number of functional units per type
KNOB<UINT32> Knob_num_memports (KNOB_MODE_WRITEONCE, "pintool", "num_memports", "1", "number of memory ports");

KNOB<UINT32> Knob_num_ialus   (KNOB_MODE_WRITEONCE, "pintool", "num_ialus", "1", "number of integer ALUs");
KNOB<UINT32> Knob_num_imuls   (KNOB_MODE_WRITEONCE, "pintool", "num_imuls", "1", "number of integer multipliers");
KNOB<UINT32> Knob_num_idivs   (KNOB_MODE_WRITEONCE, "pintool", "num_idivs", "1", "number of integer dividers");

KNOB<UINT32> Knob_num_falus   (KNOB_MODE_WRITEONCE, "pintool", "num_falus", "1", "number of FP ALUs");
KNOB<UINT32> Knob_num_fmuls   (KNOB_MODE_WRITEONCE, "pintool", "num_fmuls", "1", "number of FP multipliers");
KNOB<UINT32> Knob_num_fdivs   (KNOB_MODE_WRITEONCE, "pintool", "num_fdivs", "1", "number of FP dividers");

// ----------------- Number of reservation stations per functional unit type
KNOB<UINT32> Knob_num_rs_mem  (KNOB_MODE_WRITEONCE, "pintool", "num_rs_mem", "10", "number of reservation stations for memory");

KNOB<UINT32> Knob_num_rs_ialu (KNOB_MODE_WRITEONCE, "pintool", "num_rs_ialu", "2", "number of reservation stations for integer ALUs");
KNOB<UINT32> Knob_num_rs_imul (KNOB_MODE_WRITEONCE, "pintool", "num_rs_imul", "2", "number of reservation stations for integer multipliers");
KNOB<UINT32> Knob_num_rs_idiv (KNOB_MODE_WRITEONCE, "pintool", "num_rs_idiv", "2", "number of reservation stations for integer dividers");

KNOB<UINT32> Knob_num_rs_falu (KNOB_MODE_WRITEONCE, "pintool", "num_rs_falu", "1", "number of reservation stations for FP ALUs");
KNOB<UINT32> Knob_num_rs_fmul (KNOB_MODE_WRITEONCE, "pintool", "num_rs_fmul", "1", "number of reservation stations for FP multipliers");
KNOB<UINT32> Knob_num_rs_fdiv (KNOB_MODE_WRITEONCE, "pintool", "num_rs_fdiv", "1", "number of reservation stations for FP dividers");

// ----------------- functional unit pipeline depth
KNOB<UINT32> Knob_mem_pdepth  (KNOB_MODE_WRITEONCE, "pintool", "mem_pdepth", "1", "memory port pipeline depth");

KNOB<UINT32> Knob_ialu_pdepth (KNOB_MODE_WRITEONCE, "pintool", "ialu_pdepth", "1", "integer ALU pipeline depth");
KNOB<UINT32> Knob_imul_pdepth (KNOB_MODE_WRITEONCE, "pintool", "imul_pdepth", "1", "integer multiplier pipeline depth");
KNOB<UINT32> Knob_idiv_pdepth (KNOB_MODE_WRITEONCE, "pintool", "idiv_pdepth", "1", "integer divider pipeline depth");

KNOB<UINT32> Knob_falu_pdepth (KNOB_MODE_WRITEONCE, "pintool", "falu_pdepth", "1", "FP ALU pipeline depth");
KNOB<UINT32> Knob_fmul_pdepth (KNOB_MODE_WRITEONCE, "pintool", "fmul_pdepth", "1", "FP multiplier pipeline depth");
KNOB<UINT32> Knob_fdiv_pdepth (KNOB_MODE_WRITEONCE, "pintool", "fdiv_pdepth", "1", "FP divider pipeline depth");

// ----------------- functional unit latencies
KNOB<UINT32> Knob_mem_lat  (KNOB_MODE_WRITEONCE, "pintool", "mem_lat", "1", "memory address generation latency");
KNOB<UINT32> Knob_mem_acc_lat  (KNOB_MODE_WRITEONCE, "pintool", "mem_acc_lat", "1", "memory access latency");

KNOB<UINT32> Knob_ialu_lat (KNOB_MODE_WRITEONCE, "pintool", "ialu_lat", "1", "integer ALU latency");
KNOB<UINT32> Knob_imul_lat (KNOB_MODE_WRITEONCE, "pintool", "imul_lat", "4", "integer multiplier latency");
KNOB<UINT32> Knob_idiv_lat (KNOB_MODE_WRITEONCE, "pintool", "idiv_lat", "8", "integer divider latency");

KNOB<UINT32> Knob_falu_lat (KNOB_MODE_WRITEONCE, "pintool", "falu_lat", "4", "FP ALU latency");
KNOB<UINT32> Knob_fmul_lat (KNOB_MODE_WRITEONCE, "pintool", "fmul_lat", "8", "FP multiplier latency");
KNOB<UINT32> Knob_fdiv_lat (KNOB_MODE_WRITEONCE, "pintool", "fdiv_lat", "10", "FP divider latency");

// ----------------- functional unit initiation intervals
KNOB<UINT32> Knob_mem_ivl  (KNOB_MODE_WRITEONCE, "pintool", "mem_interval", "1", "memory initiation interval");

KNOB<UINT32> Knob_ialu_ivl (KNOB_MODE_WRITEONCE, "pintool", "ialu_interval", "1", "integer ALU initiation interval");
KNOB<UINT32> Knob_imul_ivl (KNOB_MODE_WRITEONCE, "pintool", "imul_interval", "1", "integer multiplier initiation interval");
KNOB<UINT32> Knob_idiv_ivl (KNOB_MODE_WRITEONCE, "pintool", "idiv_interval", "4", "integer divider initiation interval");

KNOB<UINT32> Knob_falu_ivl (KNOB_MODE_WRITEONCE, "pintool", "falu_interval", "1", "FP ALU initiation interval");
KNOB<UINT32> Knob_fmul_ivl (KNOB_MODE_WRITEONCE, "pintool", "fmul_interval", "2", "FP multiplier initiation interval");
KNOB<UINT32> Knob_fdiv_ivl (KNOB_MODE_WRITEONCE, "pintool", "fdiv_interval", "5", "FP divider initiation interval");

// ---------------------------------------------------------------------------
// --------------------------------- GLOBALS -----------------------------------
// ---------------------------------------------------------------------------

UINT64 g_cycle;

UINT32 g_issue_count;
bool   g_is_new_cycle;


UINT64 g_instructions_issued, g_instructions_wb;


struct registerstat{
	UINT32 Qi;
};

struct registerstat *RegisterStat;
#define NUM 10

struct reservation_station{
	int busy;
	int execcompl;
	UINT32 Op;
	UINT32 Vj;
	UINT32 Vk;
	UINT32 Qj;
	UINT32 Qk;
};

struct reservation_station *LSBUF;
struct reservation_station *IALUBUF;
struct reservation_station *IMULBUF;
struct reservation_station *IDIVBUF;
struct reservation_station *FALUBUF;
struct reservation_station *FMULBUF;
struct reservation_station *FDIVBUF;

void sim_init()
{
	// --------------------------------------------------------------------------
	// Initialise data structures and counters here.
	// --------------------------------------------------------------------------
	unsigned int i;
	RegisterStat = new  struct registerstat[NUM];
	LSBUF = new struct reservation_station[Knob_num_rs_mem.Value()];
	IALUBUF = new struct reservation_station[Knob_num_rs_ialu.Value()];
	IMULBUF = new struct reservation_station[Knob_num_rs_imul.Value()];
	IDIVBUF = new struct reservation_station[Knob_num_rs_idiv.Value()];
	FALUBUF = new struct reservation_station[Knob_num_rs_falu.Value()];
	FMULBUF = new struct reservation_station[Knob_num_rs_fmul.Value()];
	FDIVBUF = new struct reservation_station[Knob_num_rs_fdiv.Value()];

	for(i=0; i<Knob_num_rs_mem.Value(); i++){
		LSBUF[i].busy=0;
	}
	for(i=0; i<Knob_num_rs_ialu.Value(); i++){
		IALUBUF[i].busy=0;
	}
	for(i=0; i<Knob_num_rs_imul.Value(); i++){
		IMULBUF[i].busy=0;
	}
	for(i=0; i<Knob_num_rs_idiv.Value(); i++){
		IDIVBUF[i].busy=0;
	}
	for(i=0; i<Knob_num_rs_falu.Value(); i++){
		FALUBUF[i].busy=0;
	}
	for(i=0; i<Knob_num_rs_fmul.Value(); i++){
		FMULBUF[i].busy=0;
	}
	for(i=0; i<Knob_num_rs_fdiv.Value(); i++){
		FDIVBUF[i].busy=0;
	}
	// --------------------------------------------------------------------------
	g_instructions_issued = 0;
	g_instructions_wb = 0;
	// --------------------------------------------------------------------------
	g_issue_count = 0;
	g_is_new_cycle = false;
	g_cycle = 0;

	return;
}


void print_stats()
{
	TraceFile << "Number of instructions issued: " << g_instructions_issued << endl;
	TraceFile << "Number of instructions written back: " << g_instructions_wb << endl;
	TraceFile << "Number of cycles: " << g_cycle << endl;
	TraceFile << "CPI (wb) " << (double) g_cycle / g_instructions_wb << endl;

}



void run_WriteResult_stage()
{
	/* --------------------- This is the WRITE_RESULT stage ------------------- */
	UINT32 i;
	struct reservation_station *RS;
	//dont care about load-store
	RS= IALUBUF;
	for(i=0; i<Knob_num_rs_ialu.Value(); i++){
		if(RS[i].busy==1 && RS[i].Qk==0 && RS[i].execcompl==1){
			RS[i].execcompl = 0;
			RS[i].busy = 0;
			//write result back- dont care about memory
			g_instructions_wb++;
		}
	}
	RS = IMULBUF;
	for(i=0; i<Knob_num_rs_imul.Value(); i++){
		if(RS[i].busy==1 && RS[i].Qk==0 && RS[i].execcompl==1){
			RS[i].execcompl = 0;
			RS[i].busy = 0;
			//write result back- dont care about memory
			g_instructions_wb++;
		}
	}
	RS = IDIVBUF;
	for(i=0; i<Knob_num_rs_idiv.Value(); i++){
		if(RS[i].busy==1 && RS[i].Qk==0 && RS[i].execcompl==1){
			RS[i].execcompl = 0;
			RS[i].busy = 0;
			//write result back- dont care about memory
			g_instructions_wb++;
		}
	}
	RS = FALUBUF;
	for(i=0; i<Knob_num_rs_falu.Value(); i++){
		if(RS[i].busy==1 && RS[i].Qk==0 && RS[i].execcompl==1){
			RS[i].execcompl = 0;
			RS[i].busy = 0;
			//write result back- dont care about memory
			g_instructions_wb++;
		}
	}
	RS = FMULBUF;
	for(i=0; i<Knob_num_rs_fmul.Value(); i++){
		if(RS[i].busy==1 && RS[i].Qk==0 && RS[i].execcompl==1){
			RS[i].execcompl = 0;
			RS[i].busy = 0;
			//write result back- dont care about memory
			g_instructions_wb++;
		}
	}
	RS = FDIVBUF;
	for(i=0; i<Knob_num_rs_fdiv.Value(); i++){
		if(RS[i].busy==1 && RS[i].Qk==0 && RS[i].execcompl==1){
			RS[i].execcompl = 0;
			RS[i].busy = 0;
			//write result back- dont care about memory
			g_instructions_wb++;
		}
	}// Modify this so that it gets incremented only when instructions do write their results...
	return;
}



void run_Execute_stage()
{
	/* ----------------------- This is the EXECUTE stage ---------------------- */
	UINT32 i;
	struct reservation_station *RS;
	//dont care about load-store
	RS= IALUBUF;
	for(i=0; i<Knob_num_rs_ialu.Value(); i++){
		if(RS[i].busy==1 && RS[i].Qj==0 && RS[i].Qk==0){
			//compute result in Vj and Vk
			RS[i].execcompl = 1;
		}
	}
	RS = IMULBUF;
	for(i=0; i<Knob_num_rs_imul.Value(); i++){
		if(RS[i].busy==1 && RS[i].Qj==0 && RS[i].Qk==0){
			//compute result in Vj and Vk
			RS[i].execcompl = 1;
		}
	}
	RS = IDIVBUF;
	for(i=0; i<Knob_num_rs_idiv.Value(); i++){
		if(RS[i].busy==1 && RS[i].Qj==0 && RS[i].Qk==0){
			//compute result in Vj and Vk
			RS[i].execcompl = 1;
		}
	}
	RS = FALUBUF;
	for(i=0; i<Knob_num_rs_falu.Value(); i++){
		if(RS[i].busy==1 && RS[i].Qj==0 && RS[i].Qk==0){
			//compute result in Vj and Vk
			RS[i].execcompl = 1;
		}
	}
	RS = FMULBUF;
	for(i=0; i<Knob_num_rs_fmul.Value(); i++){
		if(RS[i].busy==1 && RS[i].Qj==0 && RS[i].Qk==0){
			//compute result in Vj and Vk
			RS[i].execcompl = 1;
		}
	}
	RS = FDIVBUF;
	for(i=0; i<Knob_num_rs_fdiv.Value(); i++){
		if(RS[i].busy==1 && RS[i].Qj==0 && RS[i].Qk==0){
			//compute result in Vj and Vk
			RS[i].execcompl = 1;
		}
	}
	return;
}



int find_lsbuf()
{
	UINT32 i;

	for(i=0; i<Knob_num_rs_mem.Value(); i++){
		if(LSBUF[i].busy==0){
			return i;
		}
	}
	return -1;
}


int find_ialu()
{
	UINT32 i;

	for(i=0; i<Knob_num_rs_ialu.Value(); i++){
		if(IALUBUF[i].busy==0){
			return i;
		}
	}
	return -1;
}

int find_imul()
{
	UINT32 i;

	for(i=0; i<Knob_num_rs_imul.Value(); i++){
		if(IMULBUF[i].busy==0){
			return i;
		}
	}
	return -1;
}


int find_idiv()
{
	UINT32 i;

	for(i=0; i<Knob_num_rs_idiv.Value(); i++){
		if(IDIVBUF[i].busy==0){
			return i;
		}
	}
	return -1;
}



int find_falu()
{
	UINT32 i;

	for(i=0; i<Knob_num_rs_falu.Value(); i++){
		if(FALUBUF[i].busy==0){
			return i;
		}
	}
	return -1;
}

int find_fmul()
{
	UINT32 i;

	for(i=0; i<Knob_num_rs_fmul.Value(); i++){
		if(FMULBUF[i].busy==0){
			return i;
		}
	}
	return -1;
}


int find_fdiv()
{
	UINT32 i;

	for(i=0; i<Knob_num_rs_fdiv.Value(); i++){
		if(FDIVBUF[i].busy==0){
			return i;
		}
	}
	return -1;
}


void sim_uop (CPU_OPCODE_enum opCode,
	      UINT32 src1,
	      UINT32 src2,
	      UINT32 src3,
	      UINT32 dst)
{

	bool instruction_can_issue;
	struct reservation_station *RS=NULL;
	int r;
	/* ------------------------ This is the ISSUE stage ----------------------- */

	do {
		instruction_can_issue = true;
		// --------------------------------------------------------------------------
		// Write code to check if instruction can issue, i.e. if there is a suitable
		//   reservation station available.
		// --------------------------------------------------------------------------
		if(opCode==LOAD || opCode==STORE){
			if((r = find_lsbuf())==-1){
				instruction_can_issue=false;
			}
		}
		else if(opCode==IALU){
			if((r = find_ialu())==-1){
				instruction_can_issue=false;
			}

		}
		else if(opCode==IMUL){
			if((r = find_imul())==-1){
				instruction_can_issue=false;
			}

		}
		else if(opCode==IDIV){
			if((r = find_idiv())==-1){
				instruction_can_issue=false;
			}

		}
		else if(opCode==FALU){
			if((r = find_falu())==-1){
				instruction_can_issue=false;
			}

		}
		else if(opCode==FMUL){
			if((r = find_fmul())==-1){
				instruction_can_issue=false;
			}

		}
		else if(opCode==FDIV){
			if((r = find_fdiv())==-1){
				instruction_can_issue=false;
			}

		}
		// --------------------------------------------------------------------------
		if (instruction_can_issue) {
			// ------------------------------------------------------------------------
			// ------------------------------------------------------------------------
			// Write main issue code here....
			// ------------------------------------------------------------------------
			// ------------------------------------------------------------------------
			if(opCode==LOAD || opCode==STORE){
				if(RegisterStat[src1].Qi!=0){
					LSBUF[r].Qj = RegisterStat[src1].Qi;
				}
				else{
					LSBUF[r].Vj = src2;
					LSBUF[r].Qj = r;
				}
				//dont care about memory //LSBUF[r].A =imm;
				LSBUF[r].busy=1;
				LSBUF[r].execcompl=0;
				if(opCode==LOAD){
					RegisterStat[src1].Qi=r;
				}
				else if(opCode==STORE){
					if(RegisterStat[src2].Qi!=0){
						LSBUF[r].Qk = RegisterStat[src1].Qi;
					}
					else{
						LSBUF[r].Vk = src2;
						LSBUF[r].Qk= 0;
					}
				}
			}
			else{
				if(opCode==IALU)     { RS = IALUBUF;}
				else if(opCode==IMUL){ RS = IMULBUF;}
				else if(opCode==IDIV){ RS = IDIVBUF;}
				else if(opCode==FALU){ RS = FALUBUF;}
				else if(opCode==FMUL){ RS = FMULBUF;}
				else if(opCode==FDIV){ RS = FDIVBUF;}

				if(RegisterStat[src1].Qi!=0){
					RS[r].Qj = RegisterStat[src1].Qi;
				}
				else{
					RS[r].Vj = src1;
					RS[r].Qj = 0;
				}
				if(RegisterStat[src2].Qi!=0){
					RS[r].Qk=RegisterStat[src2].Qi;
				}
				else{
					RS[r].Vk= src2;
					RS[r].Qk= 0;
				}
				RS[r].busy=1;
				RS[r].execcompl=0;
				RegisterStat[dst].Qi=r;
			}

			// ------------------------------------------------------------------------
			g_instructions_issued++;

			// Count number of instructions issued in this clock cycle
			g_issue_count++;
			if (g_issue_count == Knob_issue_width.Value()) {
				g_is_new_cycle = true;
				g_issue_count = 0;
			}
		}
		else { // Issue is stalled. Move on to the next cycle
			g_is_new_cycle = true;
			g_issue_count = 0;
		}

		if (g_is_new_cycle) {
			g_is_new_cycle = false;
			g_cycle++;
			// Run pipe stages in reverse order
			//  so as not to propagate an instruction through all stages in a single cycle!
			run_WriteResult_stage();
			run_Execute_stage();
		}
	} while (!instruction_can_issue);
}




