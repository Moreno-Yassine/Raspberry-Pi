//TYPES
struct ctx_s
{
unsigned int sp;
unsigned int adresse;
};

typedef void (*func_t) ( void);

// Fonctions

void init_ctx(struct ctx_s* ctx, func_t f, unsigned int stack_size);
void __attribute__ ((naked)) switch_to(struct ctx_s* ctx);

//

struct ctx_s* current_ctx;


