#define TOKEN_NUMBER '0'
#define MAX_TOKEN_SIZE 100

void push(double);
double pop(void);
int read_line(char [], int);
int get_next_token(char []);

/* Input Buffer */
extern char input_line[];
extern int input_index;