#include "sched.h"

void init_ctx(struct ctx_s* ctx, func_t f, unsigned int stack_size)
{
	(*ctx).sp = (int)phyAlloc_alloc(stack_size)+stack_size-4;
	// ADRESSE DE LA FONCTION
	(*ctx).adresse = f;
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
