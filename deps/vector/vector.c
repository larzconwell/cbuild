#include <stdlib.h>
#include <stdarg.h>

#include "vector.h"

vector_t *vector_new(vector_t *vec, size_t cap) {
  if (cap == 0) {
    cap++;
  }
  vec->data = malloc(sizeof(*vec->data) * cap);
  if (vec->data == NULL) {
    return NULL;
  }

  vec->len = 0;
  vec->cap = cap;
  vec->__init_cap = cap;
  return vec;
}

vector_t *vector_reset(vector_t *vec) {
  void **new = realloc(vec->data, sizeof(*vec->data) * vec->__init_cap);
  if (new == NULL) {
    return NULL;
  }

  vec->data = new;
  vec->cap = vec->__init_cap;
  vec->len = 0;
  return vec;
}

void vector_free(vector_t *vec) {
  if (vec->data != NULL) {
    free(vec->data);
  }
}

vector_t *vector_reserve(vector_t *vec, size_t size) {
  void **new = realloc(vec->data, sizeof(*vec->data) * (vec->cap + size));
  if (new == NULL) {
    return NULL;
  }

  vec->data = new;
  vec->cap += size;
  return vec;
}

vector_t *vector_resize(vector_t *vec, size_t size) {
  if (size == vec->len) {
    return vec;
  } else if (size > vec->len) {
    // Since we're making it bigger, we can just set the index to get the
    // size what we need.
    if (vector_set(vec, size-1, NULL) == NULL) {
      return NULL;
    }
  } else {
    while (vec->len > size) {
      vec->len--;
    }
  }

  return vec;
}

vector_t *vector_push(vector_t *vec, void *val) {
  // If we've reached the cap, double it for future pushes.
  if (vec->len >= vec->cap) {
    if (vector_reserve(vec, vec->cap) == NULL) {
      return NULL;
    }
  }

  vec->data[vec->len++] = val;
  return vec;
}

void *vector_pop(vector_t *vec) {
  if (vec->len == 0) {
    return NULL;
  }

  return vec->data[--vec->len];
}

void *vector_get(vector_t *vec, size_t idx) {
  if (idx >= vec->len) {
    return NULL;
  }

  return vec->data[idx];
}

vector_t *vector_set(vector_t *vec, size_t idx, void *val) {
  // Make sure we set the items before the idx that aren't set.
  while (idx >= vec->len) {
    if (vector_push(vec, NULL) == NULL) {
      return NULL;
    }
  }

  vec->data[idx] = val;
  return vec;
}

vector_t *vector_slice(vector_t *vec, vector_t *out, size_t start, size_t end) {
  if (start >= vec->len || end > vec->len || end <= start || out == NULL) {
    return NULL;
  }
  size_t size = end - start;

  // Make sure we can add items.
  if (out->data == NULL) {
    if (vector_new(out, size) == NULL) {
      return NULL;
    }
  }

  for (size_t i = start; i < end; i++) {
    if (vector_push(out, vec->data[i]) == NULL) {
      return NULL;
    }
  }

  return out;
}

int vector_index(vector_t *vec, void *val) {
  for (int i = 0; (size_t)i < vec->len; i++) {
    if (vec->data[i] == val) {
      return i;
    }
  }

  return -1;
}

int vector_last_index(vector_t *vec, void *val) {
  for (int i = vec->len-1; i >= 0; i--) {
    if (vec->data[i] == val) {
      return i;
    }
  }

  return -1;
}

vector_t *vector_concat(vector_t *out, size_t num, ...) {
  va_list list;
  va_start(list, num);

  for (size_t i = 0; i < num; i++) {
    vector_t *vec = va_arg(list, vector_t *);

    if (vector_reserve(out, vec->len) == NULL) {
      va_end(list);
      return NULL;
    }

    for (size_t j = 0; j < vec->len; j++) {
      if (vector_push(out, vector_get(vec, j)) == NULL) {
        va_end(list);
        return NULL;
      }
    }
  }

  va_end(list);
  return out;
}
