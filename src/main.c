#include <memory.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// implement your own hashtable
typedef unsigned long u64;

#define LENGTH(array, member) sizeof(array) / sizeof(member)

struct item {
  char *key;
  int value;
};

struct HashMap {
  struct item *items;
  u64 capacity;
  u64 entries;
};

u64 hash(char *key, u64 capacity) {
  int hash_total = 0;
  const u64 len = strlen(key);
  for (u64 i = 0; i < len; ++i) {
    hash_total += (int)key[i];
  }
  // u64 out = (u64)1;
  int out = (int)hash_total % (int)(2 * capacity);
  return (u64)out;
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
    return guess;
  }

  if (index >= map->capacity * 2)
    return NULL;
  for (u64 i = index + 1; i < map->capacity * 2; ++i) {
    guess = &map->items[i];

    if (guess->key == NULL)
      continue;
    if (strcmp(guess->key, key) == 0) {
      return guess;
    }
  }

  for (u64 i = 0; i < index; ++i) {
    guess = &map->items[i];

    if (guess->key == NULL)
      continue;
    if (strcmp(guess->key, key) == 0) {
      return guess;
    }
  }

  return NULL;
}

void entry(struct HashMap *map, char *key, int value) {
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
      if (&map->items[i] == NULL) {
        // problem
        map->items[i] = (struct item){.key = key, .value = value};
        map->entries += 1;
        break;
      }
    }
  }

  printf("could not insert k-v: %s : %d\n", key, value);
}

struct HashMap *new_map(u64 capacity) {
  struct HashMap *map =
      (struct HashMap *)malloc(capacity * sizeof(struct HashMap));
  *map = (struct HashMap){.capacity = capacity, .entries = 0};
  map->items = (struct item *)malloc(2 * capacity * sizeof(struct item));

  for (u64 i = 0; i < capacity; ++i) {
    struct item assign = {
        .key = NULL,
        .value = 0,
    };
    map->items[i] = assign;
  }
  return map;
}

int main(int argc, char **argv) {
  struct HashMap *map = NULL;
  map = new_map(3);

  char *key = "john";
  entry(map, key, 44);

  key = "billy";
  entry(map, key, 46);

  key = "gary";
  entry(map, key, 35);

  key = "robert";
  entry(map, key, 89);

  // struct item *retd = linear_search(map, "john");
  // if (retd->key != NULL) {
  //   printf("key: %s\nvalue: %d\n", retd->key, retd->value);
  // }

  struct item *with_get = get(map, "john");
  if (with_get != NULL) {
    printf("key: %s\nvalue: %d\n", with_get->key, with_get->value);
  }

  with_get = get(map, "billy");
  if (with_get != NULL) {
    printf("key: %s\nvalue: %d\n", with_get->key, with_get->value);
  }

  with_get = get(map, "gary");
  if (with_get != NULL) {
    printf("key: %s\nvalue: %d\n", with_get->key, with_get->value);
  }

  with_get = get(map, "robert");
  if (with_get != NULL) {
    printf("key: %s\nvalue: %d\n", with_get->key, with_get->value);
  }

  if (map->items != NULL)
    free(map->items);
  if (map != NULL)
    free(map);

  return 0;
}
