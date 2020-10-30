#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// the domain which is the numbers we are going to choose from
int domain[20] = {
  1,
  2,
  3,
  4,
  5,
  6,
  7,
  8,
  9,
  10,
  11,
  12,
  13,
  14,
  15,
  16,
  17,
  18,
  19,
  20
};

#define CHOICE 20 // length of the domain
#define TARGET 13 // the target
#define LEN 4 // the length of the desired array
#define simulated_annealing(...) siman_wrapper((func_args) {__VA_ARGS__}) // macro for named args in a func

// returns random integer from 0 to n - 1
int rand_int(int n) {
  int r, rand_max = RAND_MAX - (RAND_MAX % n);
  while ((r = rand()) >= rand_max);
  return r / (rand_max / n);
}

// print array
void print_arr(int * a, int l) {
  int i = 0;
  for (; i < l; ++i)
    printf("%i ", a[i]);
}

// the cost func here is to see if the array meets the target
int cost(int * a) {
  int i, sum = 0;
  for (i = 0; i < LEN; i++)
    sum += a[i];
  return sum;
}

// to ensure that all the values in the array are unique
int is_dup(int * a, int len) {
  int i, j;
  for (i = 0; i < len - 1; ++i) {
    for (j = i + 1; j < len; ++j) {
      if (a[i] == a[j])
        return 1; // duplicates is found
    }
  }
  return 0;
}

// simulated annealing algorithm
void siman(int * current_sol, int( * cost_func)(int * ), float temp, float cool) {
  int i, j;
  double current_cost, new_cost, p;
  int new_sol[LEN];

  // populate the initial solution randomly from the domain
  for (i = 0; i < LEN; ++i)
    current_sol[i] = domain[rand_int(CHOICE)];

  // loop until temperature is cooled down totally
  while (temp > 0.01) {
    // choose a random element to update each iteration
    i = rand_int(LEN);
    // copy current_sol into new_sol
    memcpy(new_sol, current_sol, sizeof(int) * LEN);
    // update an element randomly from domain
    new_sol[i] = domain[rand_int(CHOICE)];
    // if array has duplicates skip
    if (is_dup(new_sol, LEN))
      continue;

    // calculate cost of current solution and cost of new solution to compare
    current_cost = cost_func(current_sol);
    new_cost = cost_func(new_sol);
    // a probability to help not looping forever
    p = exp((-new_cost - current_cost) / temp);

    // check if new cost has narrower gap with TARGET than the current cost
    if (abs(TARGET - new_cost) < abs(TARGET - current_cost) || rand() < p) {
      // if so then update current_sol to be the new solution
      memcpy(current_sol, new_sol, LEN * sizeof(int));
      printf("\ncurrent cost is: %f\n", new_cost);
      puts("current solution is:");
      print_arr(current_sol, LEN);
      puts("");
    }
    // cool down
    temp = temp * cool;
  }
}

typedef struct {
  int* current_sol;
  int( * cost_func)(int * );
  float temp, cool;
}
func_args;

void siman_wrapper(func_args input) {
  float temp = input.temp ? input.temp : 100.0;
  float cool = input.cool ? input.cool : 0.99;
  printf("\n Temperature = %.2f & Cool = %.2f\n", temp, cool);
  return siman(input.current_sol, input.cost_func, temp, cool);
}

int main() {
  printf("\n\tTarget is an array of length %i unique values\n\tsum should be %i\n\tfrom numbers between 1 and %i\n",
    LEN, TARGET, CHOICE);
  // the array to be filled with possible answers
  int * current_sol = (int * ) malloc(LEN * sizeof(int));
  simulated_annealing(current_sol, cost);
  return 0;
}
