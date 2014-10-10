#define STACK_SIZE 1024

//TYPES

struct ctx_s
{
unsigned int sp;
unsigned int adresse;
};

typedef enum process_state_s {waiting,working,sleeping} ;

typedef struct pcb_s
{
	unsigned int id_process;
	enum process_state_s state_process;
	unsigned int sp_process;
	unsigned int adresse_process;
	struct pcb_s* next_process;
	void* args_f;
};




typedef void (*func_t) ( void);

// Fonctions

//void init_ctx(struct ctx_s* ctx, func_t f, unsigned int stack_size);
void create_process(func_t f, void* args, unsigned int stack_size);
void __attribute__ ((naked)) switch_to(struct ctx_s* ctx);
void ctx_switch();
void start_sched();

//
static unsigned int idprocess = 0;
static struct pcb_s* last_process;
static struct pcb_s* first_process;
struct struct pcb_s* current_process;
static struct ctx_s* current_ctx;


