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

///
/// returns a hash of the key
///
u64 hash(char *key, u64 capacity);

///
/// linear search will find
/// item in linear time:
///   O(N)
///
struct item *linear_search(struct HashMap *hash_map, const char *key);

///
/// an attempt at grabbing the value first try;
/// should practically be constant for larger map samples
///
struct item *get(struct HashMap *map, char *key);

///
/// insert a value with a particular key if 
/// the key is not already in the map
///
void entry(struct HashMap *map, char *key, int value);

///
/// returns a new map
///
struct HashMap *new_map(u64 capacity);

///
/// free the allocated memory for the map
///
void destroy_map(struct HashMap *map);


void get_or_put(struct HashMap*, char*, int);

void insert(struct HashMap*, char*, int);


#endif // _MAP_H_
