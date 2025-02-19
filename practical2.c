#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_STATES 100
#define MAX_SYMBOLS 100
#define MAX_LENGTH 100

int num_inputs, num_states, initial_state, num_accepting_states;
int accepting_states[MAX_STATES];
char input_symbols[MAX_SYMBOLS];
int transition_table[MAX_STATES][MAX_SYMBOLS];

// Function to get symbol index
int get_symbol_index(char symbol) {
    for (int i = 0; i < num_inputs; i++) {
        if (input_symbols[i] == symbol)
            return i;
    }
    return -1;
}

// Function to check if a state is an accepting state
bool is_accepting_state(int state) {
    for (int i = 0; i < num_accepting_states; i++) {
        if (accepting_states[i] == state)
            return true;
    }
    return false;
}

// Function to simulate the finite automaton
void validate_string() {
    char input_string[MAX_LENGTH];
    printf("\nEnter input string: ");
    scanf("%s", input_string);

    int current_state = initial_state;
    bool valid = true;

    for (int i = 0; input_string[i] != '\0'; i++) {
        int symbol_index = get_symbol_index(input_string[i]);
        if (symbol_index == -1) {
            printf("Invalid String\n");
            return;
        }
        current_state = transition_table[current_state][symbol_index];
    }

    if (is_accepting_state(current_state)) {
        printf("Valid String\n");
    } else {
        printf("Invalid String\n");
    }
}

int main() {
    printf("Number of input symbols: ");
    scanf("%d", &num_inputs);
    
    printf("Input symbols (space-separated): ");
    for (int i = 0; i < num_inputs; i++) {
        scanf(" %c", &input_symbols[i]);
    }
    
    printf("Enter number of states: ");
    scanf("%d", &num_states);
    
    printf("Initial state: ");
    scanf("%d", &initial_state);
    
    printf("Number of accepting states: ");
    scanf("%d", &num_accepting_states);
    
    printf("Accepting states (space-separated): ");
    for (int i = 0; i < num_accepting_states; i++) {
        scanf("%d", &accepting_states[i]);
    }
    
    printf("\nEnter the transition table:\n");
    for (int i = 1; i <= num_states; i++) {
        for (int j = 0; j < num_inputs; j++) {
            printf("State %d on input '%c' transitions to: ", i, input_symbols[j]);
            scanf("%d", &transition_table[i][j]);
        }
    }
    
    validate_string();
    return 0;
}
