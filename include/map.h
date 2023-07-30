#ifndef _MAP_H_
#define _MAP_H_

typedef unsigned long u64;

#ifndef LENGTH
#define LENGTH(array, member) sizeof(array) / sizeof(member)
#endif

struct item {
  char *key;
  int value;
};

struct HashMap {
  struct item *items;
  u64 capacity;
  u64 entries;
};

u64 hash(char *key, u64 capacity);

///
/// linear search will find
/// item in linear time:
///   O(N)
///
struct item *linear_search(struct HashMap *hash_map, const char *key);

struct item *get(struct HashMap *map, char *key);

void entry(struct HashMap *map, char *key, int value);

struct HashMap *new_map(u64 capacity);

void destroy_map(struct HashMap *map);

#endif
