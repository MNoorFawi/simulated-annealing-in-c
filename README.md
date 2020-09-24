# simulated-annealing-in-c
Simple implementation of simulated annealing optimization algorithm in C

Compile:
```bash
gcc sim_alg.c -o sim_alg -lm
gcc alg_num.c -o alg_num -lm
```
##### '-lm' to include 'math' library

Run:
```bash
./sim_alg

        The algorithm should construct the target sentence which is:
                I FEEL HOMESICK AND I WANT TO GO TO EGYPT
        from the alphabet

current cost is: 39.000000
current solutions is: WKVVYFJUHOMQINZYRTDQAGDVEKDC FNWQHRON HUO

current cost is: 38.000000
current solutions is: WKVVYFJUHOMQICZYRTDQAGDVEKDC FNWQHRON HUO

...
...
...

current cost is: 1.000000
current solutions is: I FEYL HOMESICK AND I WANT TO GO TO EGYPT

current cost is: 0.000000
current solutions is: I FEEL HOMESICK AND I WANT TO GO TO EGYPT
```

Now the other algorithm
```
./alg_num

        Target is an array of length 4 unique values
        sum should be 13
        from numbers between 1 and 20

current cost is: 45.000000
current solution is:
17 8 16 4

current cost is: 44.000000
current solution is:
17 8 15 4

...
...

current cost is: 12.000000
current solution is:
1 2 6 3

current cost is: 13.000000
current solution is:
1 2 6 4
```
