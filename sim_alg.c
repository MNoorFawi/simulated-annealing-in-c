#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char target[] = "I FEEL HOMESICK AND I WANT TO GO TO EGYPT";
char domain[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";

#define CHOICE (sizeof(domain) - 1)
#define STRLEN (sizeof(target) - 1)

// returns random integer from 0 to n - 1
int rand_int(int n) {
  int r, rand_max = RAND_MAX - (RAND_MAX % n);
  while ((r = rand()) >= rand_max);
  return r / (rand_max / n);
}

// number of different chars between a and b to calculate the cost
int cost(char * a, char * b) {
  int i, sum = 0;
  for (i = 0; a[i]; i++)
    sum += (a[i] != b[i]);
  return sum;
}

void simulated_annealing(char * current_sol, int( * cost_func)(char * , char * ),
  float temp, float cool) {
  int i;
  double current_cost, new_cost, p;
  char new_sol[STRLEN];
  for (i = 0; target[i]; ++i)
    current_sol[i] = domain[rand_int(CHOICE)];

  while (temp > 0.01) {
    i = rand_int(STRLEN);
    strcpy(new_sol, current_sol);
    new_sol[i] = domain[rand_int(CHOICE)];

    current_cost = cost_func(target, current_sol);
    new_cost = cost_func(target, new_sol);
    p = exp((-new_cost - current_cost) / temp);

    if (new_cost < current_cost || rand() < p) {
      strcpy(current_sol, new_sol);
      printf("\ncurrent cost is: %f\ncurrent solutions is: %s\n", new_cost, current_sol);
    }

    temp = temp * cool;
  }
}

int main() {
  printf("\n\tThe algorithm should construct the target sentence which is:\n\t\t%s\n\tfrom the alphabet\n",
    target);
  char * current_sol = (char * ) malloc(STRLEN * sizeof(char));
  simulated_annealing(current_sol, cost, 1000.0, 0.999);
  return 0;
}
