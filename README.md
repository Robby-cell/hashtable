# hashtable
my take on a hashtable in c

```c
struct HashMap *map = new_map(5); // new map with capacity of 5.
/// map is created by default with item capacity as 2x the "capacity"
/// this is to avoid overlaps as much as possible. a little overhead
/// for a performance gain most of the time

int value = 7;
entry(map, "key", value);
```
- this will resize the "items" field if the entries are greater than or equal to capacity

```c
struct item* retrieved = get(map, "key");
```
- retrieved value will either be a ptr to the item with the matching key or NULL
