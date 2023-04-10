#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define HASHSIZE 101

struct nlist {
  struct nlist *next; /* next entry to the chain */
  char *name;         /* defined name */
  char *defn;         /* replacement text */
};

static struct nlist *hashtab[HASHSIZE];

/* from hash value for string s */
unsigned hash(char *s) { // 3 calculate hash value
  unsigned hashval;
  for (hashval = 0; *s != '\0'; s++)
    hashval = *s + 31 * hashval; /* "hello": 0 to 104 to 3325 to 103183 to
                                  3198781 to 99162322 */
  return hashval % HASHSIZE;     //  99162322 % by 101, result 17
}

/* look for s in hashtable */
struct nlist *lookup(char *s) {
  struct nlist *np;
  for (np = hashtab[hash(s)]; np != NULL; // 2) find what is hash(s)) returned
                                          // np = hashtab[17], which is NULL
       np = np->next)
    if (strcmp(s, np->name) == 0)
      return np; // found;
  return NULL;   // NOT FOUND
}

/* put (name, defn) in hashtable */
struct nlist *install(char *name, char *defn) {
  struct nlist *np;
  unsigned hashval;

  if ((np = lookup(name)) ==
      NULL) { // not found  /* 1 -> find what is lookup(name)) returned  np =
              // lookup(NULL) == NULL: TRUE */
    np = (struct nlist *)malloc(sizeof(*np));
    if (np == NULL || (np->name = strdup(name)) == NULL)
      return NULL;
    hashval = hash(name);
    np->next = hashtab[hashval];
    hashtab[hashval] = np;
  } else                    // already there
    free((void *)np->defn); // free previous defn

  if ((np->defn = strdup(defn)) == NULL)
    return NULL;
  return np;
}

void undef(char *key) {
  int h;
  struct nlist *prev, *np;

  prev = NULL;
  h = hash(key);
  for (np = hashtab[h]; np != NULL; np = np->next) {
    if (strcmp(key, np->name) == 0) // FOUND
      break;
    prev = np;
  }
  if (np != NULL) {
    if (prev == NULL) // if no prev, becomes the next link
      hashtab[h] = np->next;
    else // prev.next becomes np.next, cutting np off the chain.
      prev->next = np->next;

    free((void *)np->name);
    free((void *)np->defn);
    free((void *)np);
  }
}

int main() {
  install("hello",
          "world"); // 0) got to install(name = "hello", defn = "world")
  install("great", "big");
  install("funny", "laugh");
  install("heli", "copter");

  printf("lookup: %s\n", lookup("hello")->defn); // prints world

  printf("17 is the hash result of hello. hashtab[17]->defn: %s\n",
         hashtab[17]->defn); // prints world


  undef("hello");
  if (lookup("hello") == NULL)
    printf("undef: TRUE\n");

  return 0;
}