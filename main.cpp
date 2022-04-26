#include <iostream>
#include <cstring>

using namespace std;

void print(int array[], int n);
void recursive(int values[], int n, int maxValues[], int minValue, int capacity, int current[], int sum, int position);

/*  Input:
    At least two numbers: first maximum capacity, then each Xi capacity 
*/
int main(int argc, char* argv[])
{
    if (argc < 3) {
        cout<<"invalid input"<<endl;
        return 1;
    }

    // get capacity
    int capacity = 0;
    int multiplier=1;
    for (int i=strlen(argv[1])-1; i>=0; i--) {
        capacity += (((int) argv[1][i]) - '0') * multiplier;
        multiplier*=10;
    }

    // get values
    int valuesCount = argc-2;
    int values[valuesCount];
    for (int i=0; i<valuesCount; i++) {
        int number = 0;
        int multiplier=1;
        for (int j=strlen(argv[i+2])-1; j>=0; j--) {
            number += (((int) argv[i+2][j]) - '0') * multiplier;
            multiplier*=10;
        }
        values[i] = number;
    }

    // get maxAmounts and minValue
    int minValue = values[0];
    int maxAmounts[valuesCount];
    for (int i=0; i<valuesCount; i++) {
        maxAmounts[i] = 0;
        while ((maxAmounts[i] + 1) * values[i] <= capacity) {
            maxAmounts[i]++;
        }
        if (values[i] < minValue) {
            minValue = values[i];
        }
    }

    // start with intinal set of parameters
    int current[valuesCount];
    recursive(values, valuesCount, maxAmounts, minValue, capacity, current, 0, 0);
}

void print(int array[], int n) {
    for (int i=0; i<n; i++)
        cout<<array[i]<<"\t";
    cout<<endl;
}

void recursive(int values[], int n, int maxValues[], int minValue, int capacity, int current[], int sum, int position) {
    // break if sum is already bigger than capacity
    if (sum > capacity) {
        return;
    }

    if (position == n) {
        // no non-full containers
        if (capacity - sum > minValue) {
            return;
        }
        print(current, n);
        return;
    }

    int copy[n];
    for (int i=0; i<=maxValues[position]; i++) {
        // fill copy for current run with previous data
        for (int j=0; j<position; j++) {
            copy[j] = current[j];
        }
        // current position
        copy[position] = i;
        // override following values (from previous runs - array is sent via reference)
        for (int j=position+1; j<n; j++) {
            copy[j] = 0;
        }

        recursive(values, n, maxValues, minValue, capacity, copy, sum + (i * values[position]), position + 1);
    }
}