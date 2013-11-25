// Program: CS242 Project 2
// Author: Scott Walker
// Date: Fall 2013
// Description: This program will simulate coin flips and display the
// actual 'random' results agains what results would be expected by
// doing a Bernoulli Trial.

#include <iostream>
#include <cstdlib>
#include <vector>

const char Coin[2] = {'H', 'T'};

using namespace std;

void PrintIntro(ostream & output, istream & input, int & flip_count, int &
	flip_simulate);
void Simulate(const int flip_count, const int flip_simulate, 
	vector <int> & result_count);
void Expected_Results(const int flip_count, const float success_prob,
	const int flip_simulate, const vector <int> result_count);
double Bernoulli_Trial(const int flip_count, const int p, 
	const float success_prob);
double Combination(int n, int k);
double Pow(const float base, const int power);


int main()
{
    int flip_count, flip_simulate;
    float success_prob = 0.5;
    vector <int> result_count;
    PrintIntro(cout, cin, flip_count, flip_simulate);
    for (int i = 0; i < flip_count + 1; i++)
    {
	result_count.push_back(0);
    }
    Simulate(flip_count, flip_simulate, result_count);
    Expected_Results(flip_count, success_prob, flip_simulate, result_count);

    return 0;
}

double Pow(float base, const int power)
{
    // This function raises the parameter base to the power of the
    // parameter power.
    // Parameters: the base of the power function, the power of the power
    // function.

    if (power == 0)
    {
	return 1;
    }
    double result = base;
    for (int i = 1; i < power; i++)
    {
	result *= base;
    }
    return result;
}

double Combination(int n, int k)
{
    // This function does a combination operation using a population size
    // n and choosing k times from that population.
    // Parameters: the total number of choices n, the number of times to 
    // choose k.

    // Since these variables are used for factorials, they must be able to
    // hold very large numbers.
    unsigned long long int top = 1LL, left = 1LL, right = 1LL;
    // Each of these loops performs a factorial as part of the combination
    // formula. (N!/((N-K)!K!))
    for (int i = n; i > 0; i--)
    {
	top *= i;
    }
    for (int i = (n - k); i > 0; i--)
    {
	left *= i;
    }
    for (int i = k; i > 0; i--)
    {
	right *= i;
    }
    return top / (left * right);
}

double Bernoulli_Trial(const int flip_count, const int p,
	const float success_prob)
{
    // This function performs a Bernoulli Trial which calculates the
    // expected outcome of many chance trials.
    // Parameters: the number of trials, the number of times to choose,
    // the probability of success.

    double combination;
    double success, failure;
    combination = Combination(flip_count, p);
    success = Pow(success_prob, p);
    failure = Pow(1 - success_prob, flip_count - p);
    return combination * success * failure;
}

void Expected_Results(const int flip_count, const float success_prob,
	const int flip_simulate, const vector <int> result_count)
{
    // This function prints the results that are expected from simulating
    // the probability by using a Bernoulli Trial.
    // Parameters: the number of times to simulate the probability, the
    // probability of the favored condition, the number of times the
    // simulation will be run, and a container for all results that may
    // be possible.

    for (int i = 0; i <= flip_count; i++)
    {
	 cout << i << " heads: " << result_count[i] << " (expected " << 
		Bernoulli_Trial(flip_count, i, success_prob) * 
		flip_simulate << ")" << endl;
    }
}

void Simulate(const int flip_count, const int flip_simulate, 
	vector <int> & result_count)
{
    // This function performs the simulation of the probability.
    // Parameters: the number of times to perform a probability, the number
    // of times to simulate the probabilities, and a container for all of
    // the possible results.
   
    int flip, num_of_heads;
    srand(time(NULL));
    srand(rand());
    srand(rand());
    // These nested loops perform 'random' simulations of flipping a coin.
    // The number of heads tallied in the vector of total outcomes so that
    // the results can be compared to a Bernoulli Trial.
    for (int i = 0; i < flip_simulate; i++)
    {
	num_of_heads = 0;
        for (int j = 0; j < flip_count; j++)
	{
	    flip = rand() % 2;
	    cout << Coin[flip];
	    if (flip == 0)
	    {
		num_of_heads++;
	    }
	}
	cout << " (" << num_of_heads << " heads)" << endl;
	result_count[num_of_heads] = result_count[num_of_heads] + 1;
    }
    cout << endl;
}

void PrintIntro(ostream & output, istream & input, int & flip_count, int &
	flip_simulate)
{
    // This function prints the introduction to ask the user for input.
    // Parameters: the output stream, the input stream, the number of times
    // to flip in each simulaton from main, the number of times the
    // simulation will be run from main.
    
    output << "Number of times to flip: ";
    input >> flip_count;
    output << "Number of times to simulate " << flip_count <<
	    " flips: ";
    input >> flip_simulate;
    output << endl;
}
