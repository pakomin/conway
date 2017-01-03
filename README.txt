
2 Folders:
1. Entire Civilations: Fitness Function: Sum of life cells over k units of time
2. AT_instant_K:       Fitness function: Total life count at final moment k.

---------------------------------------------------------------------------------------
Each of the above folder has 4 code files(execute by):
---------------------------------------------------------------------------------------
g++ filename.cpp
./a.out
---------------------------------------------------------------------------------------

1. classic_k.cpp      or     classic_t.cpp
Simple execution of GA for grid over time bound.

Recommended Grid Sizes, Timebounds: 
(8*8,200)
(10*10, 100)
(12*12,100)
(15*15,100)

---------------------------------------------------------------------------------------

2. cancer_k.cpp       or     cancer_t.cpp
Execution of grid with random cancer cell spawn
Recommended Grid Sizes, Timebounds: 
(10*10,30)
(10*10,50)
(10*10,100)
(12*12,100)
---------------------------------------------------------------------------------------

3. spawn_k.cpp        or     spawn_t.cpp
AI is allowed to spawn cells at determinate locations at each generation
Recommended Grid Sizes, Timebounds:
(8*8,200)
(10*10, 100)
(12*12,100)
(15*15,100)
---------------------------------------------------------------------------------------

4. extinction_k.cpp   or     extinction_t.cpp
Extinction event that wipes of 3/4th of the quadrants (asteroid impact) in a time period
Recommended Grid Sizes, Timebounds, begin,end:
(8*8,50,5,20)
(10*10, 50,2,10)
(12*12,50,15,35)
(15*15,1,5)
---------------------------------------------------------------------------------------

5. mutate2_k.cpp   or     mutate2_t.cpp
Simple execution of GA for grid over time bound but with slightly different mutate.

Recommended Grid Sizes, Timebounds: 
(8*8,200)
(10*10, 100)
(12*12,100)
(15*15,100)

---------------------------------------------------------------------------------------



General:
Recommended grid sizes: 10*10 to 15*15 or if you have time then 20*20
REcommended end of time : 100 (more than sufficient as each generation tends to stabilize much before)
---------------------------------------------------------------------------------------



Customizability:
1. Change MAX_ITER       :  to modify the number of iterations allowed for GA
2. Change TIME_END       :  to modify default runtime for each generation
3. Change POPULATION_SIZE:  to modify population alloted to AI
4. Change ELITE_RATE     :  to modify the elitism shown by AI
5. Change MUTATION_RATE  :  to modify mutation rate
6. Comment out mutation methods in mate1 function to try out different mutation ways

