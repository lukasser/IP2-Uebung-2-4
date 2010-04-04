/* 
 * This is the implementation for Uebung2_4 - Messdatenerfassung.
 * See COPYING for copyright information.
 */

#include <iostream>
#include "math.h"
#include "binary_tree.h"
#include "app.h"
using namespace std;

/* Add a value to measurements */
bool
addValue(tree *meas, unsigned int id)
{
    double value;
    
    cout << "Bitte Messwert eingeben: ";
    cin >> value;
    
    if (insert_nr(meas, value, id))
        return true;

    return false;
}

/* Print values (in/pre/post) */
void
showValues(tree *meas)
{
    char choice;

    cout << "\nMesswerte ausgeben\n"
         << "(a) Pre-Order, (b) In-Order, (c) Post-Order\n"
         << "> ";
    cin >> choice;

    switch (choice) {
        case 'a':
            preorder(meas);
            break;
        case 'b':
            inorder(meas);
            break;
        case 'c':
            postorder(meas);
            break;
        default: 
            cout << "Fehler!\n";
            break;
    }
}

/* Delete a value from measurements */
bool
delValue(tree *meas)
{
    unsigned int id;
    
    cout << "Bitte ID eingeben: ";
    cin >> id;

    if (remove(meas, id))
        return true;

    return false;
}

/* Search for a value */
void
searchValue(tree *meas)
{
    double value = 0.0;
    node *it = NULL;

    cout << "Bitte Wert eingeben: ";
    cin >> value;
    
    // or find(meas, value);
    it = find_nr(meas, value);
    
    if (it == NULL) {
        cout << "Wert nicht gefunden!";
    } else {
        cout << "Wert gefunden: " 
             << "ID: " << it->id << " Wert: " << it->data << endl;
    }
}

/* Calculate & print the average of measurements */
void
avg(tree *meas, int total)
{
    if (total <= 0) {
        cout << "Keine Daten vorhanden!\n";
        return;
    }
    
    double sum = 0.0;
    sumVals(meas->root, &sum);
    
    cout << "\nDer Durchschnitt der Messwerte betraegt: "
         << sum/total << endl; // type conversion??
}

/* Calculate & print the standard deviation of measurements */
void
stdDev(tree *meas, int total)
{
    if (total <= 0) {
        cout << "Keine Daten vorhanden!\n";
        return;
    }
    
    double sumValues; // sum of values
    double sum;  // sum of squared diffs
    double dev;       // standard deviation
    double mean;     // mean of values

    sum = dev = mean = sumValues = 0.0;

    sumVals(meas->root, &sumValues);
    mean = sumValues / total;
    sumSqrd(meas->root, &sum, mean);
     
    dev = sqrt((sum/total));

    cout << "\nDie Standardabweichung der Messwerte betraegt: "
         << dev << endl; // type conversion??

}

/* sum all sqred diffs */
void
sumSqrd(node *root, double *sum, double mean)
{
    if (root != NULL) {
        sumSqrd(root->link[0], sum, mean);
        *sum += pow((root->data - mean), 2);
        sumSqrd(root->link[1], sum, mean);
    }
}

/* sum all values in tree */
void
sumVals(node *root, double *sum)
{
    if (root != NULL) {
        sumVals(root->link[0], sum);
        *sum += root->data;
        sumVals(root->link[1], sum);
    }
}
