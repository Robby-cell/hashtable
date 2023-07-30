#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/map.h"

// implement your own hashtable
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

  destroy_map(map);

  return 0;
}
