#ifndef _MARKOV_CHAIN_H
#define _MARKOV_CHAIN_H

#include "linked_list.h"
#include <stdio.h>  // For printf(), sscanf()
#include <stdlib.h> // For exit(), malloc()
#include <stdbool.h> // for bool

#define ALLOCATION_ERROR_MASSAGE \
"Allocation failure: Failed to allocate new memory\n"


/***************************/
/*        TYPEDEFS         */
/***************************/
typedef void (*print_func_def)(void *data);

typedef int (*comp_func_def)(void *first, void *second);

typedef void (*free_data_def)(void *data);

typedef void *(*copy_func_def)(void *data);

typedef bool (*is_last_def)(void *data);

/***************************/
/*        STRUCTS          */
/***************************/

typedef struct MarkovNode {
    void *data;
    struct MarkovNodeFrequency *frequency_list;
    int frequency_list_length;
    int total_frequencies;

} MarkovNode;

typedef struct MarkovNodeFrequency {
    struct MarkovNode *markov_node;
    int frequency; // appearances of this node after the node that holds
    // this pointer
} MarkovNodeFrequency;

/* DO NOT ADD or CHANGE variable names in this struct */
typedef struct MarkovChain {
    LinkedList *database;

    // pointer to a func that receives data from a generic type and prints it
    // returns void.
    print_func_def print_func;

    // pointer to a func that gets 2 pointers of generic data type(same one)
    // and compare between them */
    // returns: - a positive value if the first is bigger
    //          - a negative value if the second is bigger
    //          - 0 if equal
    comp_func_def comp_func;

    // a pointer to a function that gets a pointer of generic data type and
    // frees it.
    // returns void.
    free_data_def free_data;

    // a pointer to a function that  gets a pointer of generic data type
    // and returns a newly allocated copy of it
    // returns a generic pointer.
    copy_func_def copy_func;

    //  a pointer to function that gets a pointer of generic data type and
    //  returns:
    //      - true if it's the last state.
    //      - false otherwise.
    is_last_def is_last;
} MarkovChain;

/**
 * Get one random state from the given markov_chain's database.
 * @param markov_chain
 * @return MarkovNode of the chosen state that is not a "last state" in
 * sequence.
 */
MarkovNode *get_first_random_node(MarkovChain *markov_chain);

/**
 * Choose randomly the next state, depend on it's occurrence frequency.
 * @param cur_markov_node MarkovNode to choose from
 * @return MarkovNode of the chosen state
 */
MarkovNode *get_next_random_node(MarkovNode *cur_markov_node);

/**
 * Receive markov_chain, generate and print random sequences out of it. The
 * sequence most have at least 2 words in it.
 * @param markov_chain
 * @param first_node markov_node to start with, if NULL-
 * choose a random markov_node
 * @param  max_length maximum length of chain to generate
 */
void generate_random_sequence(MarkovChain *markov_chain, MarkovNode *
first_node, int max_length);

/**
 * Free markov_chain and all of it's content from memory
 * @param chain_ptr markov_chain to free
 */
void free_markov_chain(MarkovChain **chain_ptr);

/**
 * Add the second markov_node to the frequency list of the first markov_node.
 * If already in list, update it's frequency value.
 * @param first_node
 * @param second_node
 * @param markov_chain
 * @return success/failure: 0 if the process was successful, 1 if in
 * case of allocation error.
 */
int add_node_to_frequency_list(MarkovNode *first_node, MarkovNode
*second_node, MarkovChain *markov_chain);

/**
* Check if data_ptr is in database. If so, return the markov_node wrapping
 * it in
 * the markov_chain, otherwise return NULL.
 * @param markov_chain the chain to look in its database
 * @param data_ptr the state to look for
 * @return Pointer to the Node wrapping given state, NULL if state not in
 * database.
 */
Node *get_node_from_database(MarkovChain *markov_chain, void *data_ptr);

/**
* If data_ptr in markov_chain, return it's node. Otherwise, create new
 * node, add to end of markov_chain's database and return it.
 * @param markov_chain the chain to look in its database
 * @param data_ptr the state to look for
 * @return node wrapping given data_ptr in given chain's database
 */
Node *add_to_database(MarkovChain *markov_chain, void *data_ptr);

#endif /* MARKOV_CHAIN_H */
