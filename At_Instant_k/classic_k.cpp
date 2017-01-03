
#include "GameOfLife.hpp"
using namespace std;

#define MAX_SIZE 1000
#define TIME_END 1000

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <time.h>
#include <math.h>

#define POPULATION_SIZE 100
#define MAX_ITER 100
#define ELITE_RATE 0.10f
#define MUTATION_RATE 0.25f
#define MUTATION RAND_MAX * MUTATION_RATE
#define GA_TARGET std::string("Hello World. How are you?")

struct colony{
    vector<bool> gen[MAX_SIZE];
    unsigned int fitness;
    long long int init_alive;
};


long long int col_target1;
long long int col_target2;

long long int alive=0;

struct ga_struct
{
    string str;
    unsigned int fitness;
};

long long int ROW_NUMBER;
long long int COL_NUMBER;
long long int rows,cols;
colony prot;


typedef vector<ga_struct> ga_vector;
typedef vector<colony*> col_vector;


void copy(vector<bool> source[MAX_SIZE], vector<bool> dest[MAX_SIZE])
{
    int i, j;
    for (i = 0; i < ROW_NUMBER; i++)
        for (j = 0; j < COL_NUMBER; j++)
            dest[i][j] = source[i][j];
}


bool compare(vector<bool> array1[MAX_SIZE], vector<bool> array2[MAX_SIZE])
{
    bool flag=true;
    int i, j;
    for (i = 0; i < ROW_NUMBER; i++)
        for (j = 0; j < COL_NUMBER; j++)
            if (array1[i][j] != array2[i][j])
                flag=false;
    
    return flag;
}

long long int printArr(vector<bool> array[MAX_SIZE], int genCount)
{
    long long int alive_now=0;
    int i, j;
    printf("\n");
    for (i = 1; i < ROW_NUMBER - 1; i++)
    {   printf("  ");
        for (j = 1; j < COL_NUMBER - 1; j++)
        {
            if (array[i][j]){
                cout<<"#"<<" ";
                alive_now++;                
            }
            else{
                cout<<"."<<" ";
            }
        }
        cout<<"\n";
    }
    printf("--------------------------------\n GENERATION %d : Life Count: %lld\n--------------------------------\n ",genCount,alive_now);
    printf("\n");
    return alive_now;
}

long long int getalivecells(vector<bool> array[MAX_SIZE], int genCount)
{
    long long int alive_now=0;
    int i, j;
    for (i = 1; i < ROW_NUMBER - 1; i++)
    {   for (j = 1; j < COL_NUMBER - 1; j++)
        {
            if (array[i][j]){
                alive_now++;                
            }
            else{
            }
        }       
    }
    return alive_now;
}



pair<bool,long long int> life_state(vector<bool> arr[MAX_SIZE])
{
    pair<char, double> twoValues;

    long long int aliven=0;
    int flag=false;
    int i, j, count;
    bool prev_row[COL_NUMBER];
    bool this_row[COL_NUMBER];
    bool prev=false;
    
    for(i=0;i<COL_NUMBER;i++)
    {
        prev_row[i]=arr[0][i];
        this_row[i]=arr[1][i];
    }
    
    for (i = 1; i < ROW_NUMBER - 1; i++)
    {
        for (j = 1; j < COL_NUMBER-1; j++)
        {
            count =
            (int)prev_row[j - 1]              //arr[i-1][j-1]
            + (int)prev_row[j]                  //arr[i-1][j]
            + (int)prev_row[j + 1]              //arr[i-1][j+1]
            + (int)prev                         //arr[i][j-1]
            + (int)arr[i][j + 1]                //the unchanged arr variables
            + (int)arr[i + 1][j - 1]
            + (int)arr[i + 1][j]
            + (int)arr[i + 1][j + 1];
            
            prev=arr[i][j];                 //maintaining temp vars
            prev_row[j-1]=this_row[j-1];
            this_row[j-1]=arr[i+1][j-1];
            
            
            if (count < 2 || count > 3)
                arr[i][j] = false;
            
            if (count == 3)
                arr[i][j] = true;
            
            if(arr[i][j]!=prev)
                flag=true;
            
            if(arr[i][j])
                aliven++;
        }
        prev=false;
        prev_row[COL_NUMBER-2]=this_row[COL_NUMBER-2];
        this_row[COL_NUMBER-2]=arr[i+1][COL_NUMBER-2];
    }
    twoValues.first=flag;
    twoValues.second=aliven;
    return twoValues;
}

long long int debugscore=0;
long long int run_simulation(vector<bool> gen0[MAX_SIZE],long long int endoftime=100)
{
    int i, j;
    char run_again;
    string sanity_check;
    bool change = false;
    
    long long int overallscore=0;
    long long int finalscore=0;
   // system("clear");
    int genCount = 0;
    do
    {
       // system("sleep 0.1");
       // system("clear");
        pair<bool,long long int> anspair=life_state(gen0);
        change  =anspair.first;
        finalscore=anspair.second;       
        overallscore+=finalscore;

        /*
        if(genCount>1 && genCount%100==0)
        {
            printf("\nContinue Simulation?:");
            cin>>run_again;
            if(run_again!='y')
                break;
        }
        */
        genCount++;
    }
    while (genCount<endoftime);//upper limit is endofline. change it to user inpt.
 //   if(overallscore>debugscore)
  //      debugscore=overallscore;
    //printf("Debug score:%lld\n",debugscore);
    
    return finalscore ;//overallscore
}

long long int initialize(vector<bool> arr[MAX_SIZE])
{

    int i,j;
    int randtemp;
    long long int thisalive=0;
    for(i=0;i<ROW_NUMBER;i++)
    {

        arr[i].clear();
        for(j=0;j<COL_NUMBER;j++)
        {
            if(i==0||j==0||i==ROW_NUMBER-1||j==COL_NUMBER-1)//setting borders to permanently false
            {
                arr[i].push_back(false);
            }
            else                                            //randomly deciding what the initial cells will be
            {
                randtemp= rand()%2;
                if(randtemp==1)
                {
                    arr[i].push_back(true);
                    thisalive++;
                }
                else
                {
                    arr[i].push_back(false);
                }
                
            }
        }
    }
    return thisalive;
}

long long int upperbound;


void userinteract()
{
    //    long long int n,m;
    
    char run_again;
    //struct organism* prototype=(organism*)malloc(sizeof(organism));
    //organism prot;

    

    printf("Enter Grid Size:   ");
    scanf("%lld %lld",&ROW_NUMBER,&COL_NUMBER);
    printf("Enter End of Time: ");
    scanf("%lld",&upperbound);
    if(upperbound==-1)
        upperbound=TIME_END;
    
    col_target1=ROW_NUMBER*COL_NUMBER*upperbound;
    col_target2=ROW_NUMBER*COL_NUMBER;
    ROW_NUMBER+=2;
    COL_NUMBER+=2;
    //initialize(prototype->gen0);
    //run_simulation(prototype->gen0,upper_bound);
    
//    initialize(prot.gen);
//    run_simulation(prot.gen,upper_bound);

}






void init_population1(col_vector &population, col_vector &buffer)
{
//    int tsize = GA_TARGET.size();
    int i, j;
    for (i = 0; i < POPULATION_SIZE; i++)
    {

        colony* col=(colony*)malloc(sizeof(colony));

        col->fitness = 0;
        //citizen.str.erase();
        long long int gotalive=initialize(col->gen);
        col->init_alive=gotalive;

//        printf("do: %lld\n",col.init_alive);
        population.push_back(col);
        buffer.push_back(col);
        
    }
   // buffer.resize(POPULATION_SIZE);
}


void calculate_fitness1(col_vector &population)
{
    
 //   string target = GA_TARGET;
//    int tsize = target.size();
    unsigned int fitness;
    colony* temp=(colony*)malloc(sizeof(colony));
    int i, j;
    for (i = 0; i < POPULATION_SIZE; i++)
    {
        fitness = 0;

        *temp = *(population[i]);

        fitness=run_simulation(temp->gen,upperbound);
      //  cout<<"Fitness= "<<fitness<<endl;
        population[i]->fitness = fitness;
    }
}


struct Comparator
{
    bool operator()(colony *x, colony *y)
    {
        return (x->fitness) > (y->fitness)  ;
    }
};


bool fitness_sort1(colony *x, colony *y)
{
    return (x->fitness) > (y->fitness);
}


inline void sort_by_fitness1(col_vector &population)
{
  //  printf("begin sorting %lu\n",(population).size());
    sort(population.begin(), population.end(), Comparator());
  //  printf("end sorting\n");

}



void elitism1(col_vector &population, col_vector &buffer, int esize)
{
    int i;
    colony* temp=(colony*)malloc(sizeof(colony));
        
    for (i = 0; i < esize; i++)
    {
     //   buffer[i].gen = population[i].gen;
    //    buffer[i].fitness = population[i].fitness;
        *temp=*population[i];
        buffer[i]=temp;

    }
}



void mutate1(colony *member)
{

    int ipos = (rand() %  (ROW_NUMBER-2)) +1;
    int jpos = (rand() % (COL_NUMBER-2)) +1;
//    int delta = (rand() % 90) + 32;
    
    member->gen[ipos][jpos] = !(member->gen[ipos][jpos]);

}

void mutate2(colony *member)
{
    int ipos = (rand() % (ROW_NUMBER-2)) +1;
    int jpos = (rand() % (COL_NUMBER-2)) +1;
//    int delta = (rand() % 90) + 32;
    for(jpos=1;jpos<COL_NUMBER-1;jpos++)
        member->gen[ipos][jpos] = !(member->gen[ipos][jpos]);
}


void mate1(col_vector &population, col_vector &buffer)// this is where the fucking happens
{
    int esize = POPULATION_SIZE * ELITE_RATE;
    int tsize = ROW_NUMBER, spos, i1, i2, i;
    

    //elitism1(population, buffer, esize);
    //int i;       
    for (i = 0; i < esize; i++)
    {
    //    buffer[i]=(colony*)malloc(sizeof(colony));
        *buffer[i]=*population[i];;

    }

    
    for (i = esize; i < POPULATION_SIZE; i++)
    {
     //   buffer[i]=(colony*)malloc(sizeof(colony));
       
        i1 = rand() % (POPULATION_SIZE / 2);
        i2 = rand() % (POPULATION_SIZE / 2);
        spos = rand() % tsize;
        int j;

        for(j=0;j<spos;j++)
        {
            (*buffer[i]).gen[j]=(*population[i1]).gen[j];
        }
        
        for(;j<ROW_NUMBER;j++)
        {
            (*buffer[i]).gen[j]=(*population[i2]).gen[j];
        }
        
        if (rand() < MUTATION)
        {
             //   mutate1(*buffer[i]);                
        int ipos = (rand() % (ROW_NUMBER-3)) +1;
        int jpos = (rand() % (COL_NUMBER-3)) +1;
       // printf("%d %d ",ipos,jpos);
            //mutate method 1
            (*buffer[i]).gen[ipos][jpos] = !((*buffer[i]).gen[ipos][jpos]);
        
            //mutate method 2
          //  for(jpos=1;jpos<COL_NUMBER-1;jpos++)
            //    (*buffer[i]).gen[ipos][jpos] = !((*buffer[i]).gen[ipos][jpos]);

        }
             
    }
    
    
}



inline void swap1(col_vector *&population, col_vector *&buffer)
{
    col_vector *temp = population;
    population = buffer;
    buffer = temp;
}



inline void print_best1(col_vector &ga,int i)
{
    //cout<<"String: "<< ga[0].str<<"\n";
    
  //  printArr(ga[0]->gen,0);
    cout<<"Iteration# "<<i<<" - Fitness value: "<< (*ga[0]).fitness<<"\n";
}


ga_vector init_pop, init_buffer, *population1, *buffer1;

col_vector init_cols, init_buffers, *colonies1, *buffers1;
void printsidebyside(vector<bool> gen1[MAX_SIZE],vector<bool> gen2[MAX_SIZE], long long int genCount)
{
    long long int alive_now1=0;
    long long int alive_now2=0;
    int i, j;
    
    printf("Grid: %lld*%lld     TimeBound:%lld",ROW_NUMBER-2,COL_NUMBER-2,upperbound);
    printf("\n------------------------------------------\nLeft: Best result with initial random colonies\n------------------------------------------\nRight: Best result obtained by AI after %d iterations\n------------------------------------------\n ",MAX_ITER);
   
    printf("\n");
    for (i = 1; i < ROW_NUMBER -1; i++)
    {   printf("  ");
        for (j = 1; j < COL_NUMBER -1; j++)
        {
            if (gen1[i][j]){
                cout<<"#"<<" ";
                alive_now1++;                
            }
            else{
                cout<<"."<<" ";
            }
        }
        cout<<"\t";
        printf("  ");
        for (j = 1; j < COL_NUMBER -1; j++)
        {
            if (gen2[i][j]){
                cout<<"#"<<" ";
                alive_now2++;                
            }
            else{
                cout<<"."<<" ";
            }
        }
        printf("\n");
    }
    printf("\n--------------------------------\nGENERATION: %lld : \nMaximizing life at final instant \n\n-> Current Life Count (L,R): %lld - %lld\n--------------------------------\n ",genCount,alive_now1, alive_now2);
    
}
void runsidebyside(colony* a, colony*b,long long int endoftime)
{

    int i, j;
    char run_again;
    string sanity_check;
    bool change1 = false;
    bool change2 = false;
    long long int overallscore1=0;
    long long int finalscore1=0;
   // system("clear");
    long long int overallscore2=0;
    long long int finalscore2=0;
    int genCount = 0;
    pair<bool,long long int> anspair;
    do
    {
       if(change1 || change2){
        system("sleep 0.1");      
       }
        system("clear");
        
        anspair=life_state(a->gen);
        change1  =anspair.first;
        finalscore1=anspair.second;       
        overallscore1+=finalscore1;

        anspair=life_state(b->gen);
        change2  =anspair.first;
        finalscore2=anspair.second;       
        overallscore2+=finalscore2;

        printsidebyside(a->gen,b->gen,genCount);
        printf("\n   Overall Life Sum   (L,R): %lld - %lld\n--------------------------------\n ",overallscore1, overallscore2);
    
        printf("\n");

        /*
        if(genCount>1 && genCount%100==0)
        {
            printf("\nContinue Simulation?:");
            cin>>run_again;
            if(run_again!='y')
                break;
        }
        */
        genCount++;
    }
    while (genCount<endoftime);

    long long int alive_now1=0;
    long long int alive_now2=0;
  
    printf("\n");

}
int main()
{


  //  srand(time(NULL));
    userinteract();
    srand(unsigned(time(NULL)));
    init_population1(init_cols, init_buffers);    
  //  init_population(init_pop, init_buffer);
    colonies1 = &init_cols;
    buffers1 = &init_buffers;
    int i=0;
    long long int firstfitness=0;
    colony* first_best_colony=(colony*)malloc(sizeof(colony));
    for (i = 0; i < MAX_ITER; i++)
    {
        //printf("ITERATION %d\n\n\n\n",i);
   
          //printf("Calculating fitness of colonies\n");
          calculate_fitness1(*colonies1);
          //printf("Sorting fitness of colonies\n");
          sort_by_fitness1(*colonies1);
     //     int j;
        /*
          for(j=0;j<POPULATION_SIZE;j++)
          {
            printf("Fitness= %u\n",init_cols[j].fitness);
          }
          */
      //  printf("Printing the best colony fitness\n");

        print_best1(*colonies1,i);
        if(i==0)
        {  
            *first_best_colony= *(*colonies1)[0];
        }

        //if ((*population1)[0].fitness == 0)
        //{
        //    break;
        //}
       // printf("Mating colonies\n");

          mate1(*colonies1,*buffers1);
       // printf("Swapping colonies\n");

          swap1(colonies1,buffers1);
        
     //   printf("\nDone with iteration:%d\n",i);
    }

    runsidebyside(first_best_colony,(*colonies1)[0],upperbound);
    return 0;
 
}
