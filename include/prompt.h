#ifndef PROMPT_H
#define PROMPT_H

extern char* prompt;

/* initialize the prompt variable during runtime */
void init_prompt();

/* add flag content like "err" or "nil" to the prompt variable */
void add_flag_to_prompt(char* prompt);

/* reset the prompt to the default prompt and removes the flag content  */
void reset_default_prompt();

/* simple prompt function to present the error code along with the prompt */
void display_prompt(int status);

#endif
