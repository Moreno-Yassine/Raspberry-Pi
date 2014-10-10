#include "sched.h"

void init_ctx(struct ctx_s* ctx, func_t f, unsigned int stack_size)
{
	(*ctx).sp = (int)phyAlloc_alloc(stack_size)+stack_size-4;
	// ADRESSE DE LA FONCTION
	(*ctx).adresse = f;
}


void init_pcb(struct pcb_s* pcb, func_t f, void* args, unsigned int stack_size){
    (*pcb).id_process = idprocess++;
    (*pcb).state_process = working; 
    (*pcb).adresse_process = f; 
    (*pcb).sp_process = ((int)phyAlloc_alloc(stack_size)) + stack_size;
    (*pcb).args_f = args;
}
void start_sched()
{
}

void ctx_switch()
{
}

void elect()
{
	}
	
void create_process(func_t f, void* args, unsigned int stack_size)
{
    struct pcb_s* pcb = (struct pcb_s*)phyAlloc_alloc(sizeof(struct pcb_s));
    last_process->next_process = pcb; 
    pcb->next_process = first_process;
    last_process = pcb; 
    init_pcb(pcb,f,args, stack_size);
}

void __attribute__ ((naked)) switch_to(struct ctx_s* ctx)
{
	
	// SAUVEGARGE
	__asm("push {r0-r12}");
	__asm("mov %0, sp" : "=r"((*current_ctx).sp));
	__asm("mov %0, lr" : "=r"((*current_ctx).adresse));

	// CHNGMT DE CTXT
	current_ctx=ctx;

	//RSTR
	__asm("mov sp, %0" : : "r"((*ctx).sp));
	__asm("mov lr, %0" : : "r"((*ctx).adresse));
	__asm("pop {r0-r12}");

	//EXEC
	__asm("bx lr");
	
}
