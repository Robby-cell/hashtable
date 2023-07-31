#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/map.h"

u64 hash(char *key, u64 capacity) {
  u64 hash_total = 0;
  const u64 len = strlen(key);
  for (u64 i = 0; i < len; ++i) {
    hash_total += (key[i] * (i + 1));
  }
  u64 out = hash_total % (2 * capacity);
  return out;
}

///
/// linear search will find
/// item in linear time:
///   O(N)
///
struct item *linear_search(struct HashMap *hash_map, const char *key) {
  for (u64 i = 0; i < hash_map->capacity; ++i) {
    if (hash_map->items[i].key != NULL) {
      if (strcmp((const char *)hash_map->items[i].key, key) == 0) {
        return &hash_map->items[i];
      }
    }
  }

  return NULL;
}

struct item *get(struct HashMap *map, char *key) {
  u64 index = hash(key, map->capacity);

  struct item *guess = &map->items[index];
  if (guess->key != NULL && strcmp(guess->key, key) == 0) {
    // best case, we get it first try
    return guess;
  }

  if (index >= map->capacity * 2)
    return NULL;
  for (u64 i = index + 1; i < map->capacity * 2; ++i) {
    guess = &map->items[i];

    if (guess->key == NULL)
      continue;
    if (strcmp(guess->key, key) == 0) {
      // we check up to the end of the map
      return guess;
    }
  }

  for (u64 i = 0; i < index; ++i) {
    guess = &map->items[i];

    if (guess->key == NULL)
      continue;
    if (strcmp(guess->key, key) == 0) {
      // then we check the other bit, because
      // we add the entry after if it cant be added
      // where we want to add it
      return guess;
    }
  }

  return NULL;
}

void entry(struct HashMap *map, char *key, int value) {
  if (get(map, key) != NULL)
    return;
  if (map->capacity <= map->entries) {
    void *new_items;
    new_items = realloc((void *)map->items,
                        2 * (map->capacity + 1) * sizeof(struct item));
    if (new_items == NULL) {
      fputs("Could not reallocate.", stderr);
      return;
    }
    map->capacity += 1;

    map->items = (struct item *)new_items;
  }

  // map->items[map->entries + 1] = (struct item){.key = key, .value = value};
  u64 insert_index = hash(key, map->capacity);
  if (map->items[insert_index].key == NULL) {
    map->items[insert_index] = (struct item){.key = key, .value = value};
    map->entries += 1;
    return;
  } else {
    for (u64 i = insert_index; i < map->capacity; ++i) {
      if (map->items[i].key == NULL) {
        // problem
        map->items[i] = (struct item){.key = key, .value = value};
        map->entries += 1;
        return;
      }
    }

    for (u64 i = 0; i < insert_index; ++i) {
      if (map->items[i].key == NULL) {
        // problem
        map->items[i] = (struct item){.key = key, .value = value};
        map->entries += 1;
        return;
      }
    }
  }

  printf("could not insert k-v: %s : %d\n", key, value);
}

struct HashMap *new_map(u64 capacity) {
  struct HashMap *map =
      (struct HashMap *)malloc(sizeof(struct HashMap));
  if (map == NULL) return NULL;
  
  *map = (struct HashMap){.capacity = capacity, .entries = 0};
  map->items = (struct item *)malloc(2 * capacity * sizeof(struct item));

  return map;
}

void destroy_map(struct HashMap *map) {
  if (map != NULL) {
    if (map->items != NULL)
      free(map->items);
    free(map);
  }
}
