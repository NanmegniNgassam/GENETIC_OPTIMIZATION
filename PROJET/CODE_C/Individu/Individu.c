/**
 * @name NANMEGNI_NGASSAM
 * @date 07/11/2022
 * @file Individu.c
 * @brief Method's implementation of the abstract data type Individual
 */
#include"Individu.h"

//IMPLEMENTATION DES CONSTRUCTEURS

//add a bit to the start of a sequence of bits (Individual)
Individu addHead(Individu i, Bit b)
{
  BitIndividu *temp;
  temp = (BitIndividu*)malloc(sizeof(BitIndividu));

  temp ->bitValue = b;
  temp ->nextBit = i;
  return temp;
}

//add a bit to the end of a sequence of bits (Individual)
Individu addTail(Individu i, Bit b)
{
  BitIndividu *temp;
  temp = (BitIndividu*)malloc(sizeof(BitIndividu));
  temp ->bitValue = b;
  temp ->nextBit = NULL;

  if( isEmpty(i))
  {
    return temp;
  }
  else
  {
    Individu current = i;
    while ((current ->nextBit) != NULL)
    {
      current = current ->nextBit;
    }

    current ->nextBit = temp;
    return i;
  }
}

//delete a bit to the start of a sequence of bits (Individual)
Individu deleteHead(Individu i)
{
  if(isEmpty(i))
  {
    return i;
  }
  else
  {
    BitIndividu *temp;
    temp = i;
    i = i->nextBit;
    free(temp);
    temp = NULL;
    return i;
  }
}

//delete a bit to the end of a sequence of bits (Individual)
Individu deleteTail(Individu i)
{
  if (isEmpty(i) || isEmpty(i->nextBit))
  {
    if (isEmpty(i->nextBit))
    {
      free(i);
      i = NULL;
    }
    return NULL;
  }
  else
  {
    BitIndividu *current;
    current = i;
    while (((current->nextBit)->nextBit) != NULL)
    {
      current = current ->nextBit;
    }
  
    free(current->nextBit);
    current ->nextBit = NULL;
    return i;
  } 
}

//return a sequence of bits private from its first bit
Individu remain(Individu i)
{
  if (isEmpty(i))
  {
    return i;
  }
  else
  {
    return i->nextBit;
  }
}

//return recursively an Individual with random bits in its sequence
Individu RrandomInit( int nbOfBits)
{
  
  if(nbOfBits <= 0)
  {
    return NULL;
  }
  else
  {
    return addHead(RrandomInit(nbOfBits - 1), aleaBinVal());
  }
}

//return an Individual with random bits in its sequence
//Explications nombre de bits c'est quoi?
Individu randomInit( int nbOfBits)
{
  int turn = nbOfBits;
  Individu indiv = NULL;
  while (turn >= 1)
  {
    indiv = addHead(indiv, aleaBinVal());
    turn--;
  }
  return indiv;
}

//return an individual issued from a random mixing of two individuals
Individu RIndivCrossing(Individu i, Individu j)
{
  if(isEmpty(i) && isEmpty(j))
  {
    return i;
  }
  else
  {
    // generation of a value included between 1 and 100 and compare it with a crossing probability setting up as a constant(0.01)
    int random = rand()%100 + 1;
    if (random <= 100*P_CROSSING)
    {
      return addHead(RIndivCrossing(remain(i), remain(j)) , i->bitValue);
    }
    else
    {
      return addHead(RIndivCrossing(remain(i), remain(j)) , j->bitValue);
    }
  }
}


//IMPLEMENTATION OF GETTERS AND ACCESS FUNCTIONS

//emptytest to know if an individual is null or not
Bool isEmpty(Individu i)
{
  if(i == NULL)
    return true;
  else
    return false;
}

//returns from an Individual, the decimal value associated to its binary sequence
int RtoDecimal(Individu i)
{
  if(isEmpty(i))
  {
    return 0;
  }
  else
  {
    return ((i->bitValue) + 2*(RtoDecimal(i->nextBit)));
  }
}

//returns from an individual its quality_factor
float qualityFactor(Individu i) // X = (value / 2^LONG_INDIV)*(B-A) + A
{
  int value = RtoDecimal(i);
  float temp = value/(power(2,LONG_INDIV));
  temp = temp*(B-A);
  temp = temp + A; //(value / 2^LONG_INDIV)*(B-A) + A
  return temp;
}

//returns from an indivdual, its quality -- f(x) = -X^2 // X = i's quality factor
float quality(Individu i)
{
  float temp = qualityFactor(i);
  //return -logf(temp); //f(x) = -X^2
  return -power(temp,2);
}

//displays the bit sequence of an individual as 1 0 1 0 0 1 1 ... 1 followed by some of its features
void displayIndiv(Individu indiv)
{
  Individu current = indiv;
  printf("Indiv : ");
  while (current != NULL)
  {
    printf("%d ", (current->bitValue));
    current = current->nextBit;
  }
  printf(" (%d) ", RtoDecimal(indiv));
  printf(" | (%f)\n", quality(indiv));
}