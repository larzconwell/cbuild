#ifndef H_VECTOR
#define H_VECTOR 1

#include <stddef.h>

// struct vector contains fields that control the data in a vector.
typedef struct vector {
  size_t len;
  size_t cap;
  void **data;

  size_t __init_cap;
} vector_t;

// vector_new allocates and reserves space for a number of values. NULL is
// returned if allocation fails.
vector_t *vector_new(vector_t *, size_t);

// vector_reset resets the space to the inital space given. NULL is returned
// if resetting failed.
vector_t *vector_reset(vector_t *);

// vector_free fress the data in a vector.
void vector_free(vector_t *);

// vector_reserve reserves a number of spaces for future user. NULL is returned
// if the spaces can't be allocated.
vector_t *vector_reserve(vector_t *, size_t);

// vector_resize sets the length of the vector to a given size, adding items
// if needed.
vector_t *vector_resize(vector_t *, size_t);

// vector_push adds a value to the data, allocating extra space if necessary.
// NULL is returned if the item can't be appended.
vector_t *vector_push(vector_t *, void *);

// vector_pop removes a value from the end of the list. NULL is returned if
// there's no items in the list.
void *vector_pop(vector_t *);

// vector_get retrieves the value at a given index, NULL is returned if the index
// doesn't exist.
void *vector_get(vector_t *, size_t);

// vector_set sets the value at the given index, filling in any spaces before it
// that aren't used. NULL is returned if setting the value fails.
vector_t *vector_set(vector_t *, size_t, void *);

// vector_slice adds items from a given range to another vector. NULL is returned
// if the vector can't be sliced, otherwise the vector slice is returned.
vector_t *vector_slice(vector_t *, vector_t *, size_t, size_t);

// vector_index returns the index of a value, or -1 if it can't be found.
int vector_index(vector_t *, void *);

// vector_last_index returns the index of a value starting from the end of the
// list, or -1 if it can't be found.
int vector_last_index(vector_t *, void *);

// vector_concat creates a vector from a number of vectors adding the items from
// each into the first one. NULL is returned if adding to the vector fails, otherwise
// the first vector given is returned with the items added.
vector_t *vector_concat(vector_t *, size_t num, ...);

#endif
