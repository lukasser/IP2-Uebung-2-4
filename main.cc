/* 
 * This is the main program for Uebung2_4 - Messdatenerfassung.
 * See COPYING for copyright information.
 */

#include <iostream>
#include "binary_tree.h"
#include "main.h"

using namespace std;

int
main(void)
{

    tree *measurements = new tree; // tree to hold the values
    unsigned int total = 0;  // total number of stored values
    char choice;

    /*  Main Menu loop */
    do {

        cout << "\n----- Menu -----\n"
         << "\t(a) Messwert eingeben\n"
		 << "\t(b) Messwerte ausgeben\n"
		 << "\t(c) Messwert loeschen\n"
         << "\t(d) Messwert suchen\n"
         << "\t(e) Durchschnittswert errechnen\n"
		 << "\t(f) Datenstand anzeigen\n"
		 << "\t(q) Program beenden\n   >> ";
        cin >> choice;
		
        switch (choice) {
            case 'A':
            case 'a':
                addValue(measurements, total);
                total++;
				break;
				
            case 'B':
            case 'b':
                showValues(measurements);
				break;
				
            case 'C':
            case 'c':
                delValue(measurements);
                total--;
				break;

            case 'D':
            case 'd':
                searchValue(measurements);
                break;

            case 'E':
            case 'e':
                calcAvg(measurements, total);
                break;

            case 'F':
            case 'f':
                print_tree(measurements->root, total);
                break;

            case 'Q':
            case 'q': break;
				
            default: cout << "Fehlerhafte Wahl!\n";
        }
		
    } while (choice != 'q' && choice != 'Q');

    // Delete Tree
    destroy_nr(measurements);

    return 0;
}

/* Add a value to measurements */
void
addValue(tree *meas, unsigned int id)
{
    double value;
    
    cout << "Bitte Messwert eingeben: ";
    cin >> value;
    
    if (insert_nr(meas, value, id) != 1)
        cout << "ERROR\n\n";
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
void
delValue(tree *meas)
{
    unsigned int id;
    
    cout << "Bitte ID eingeben: ";
    cin >> id;

    if (remove(meas, id) != 1)
        cout << "ERROR\n\n";
}

/* Search for a value */
void
searchValue(tree *meas)
{
    double value = 0.0;
    node *it = NULL;

    cout << "Bitte Wert eingeben: ";
    cin >> value;
    
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
calcAvg(tree *meas, int total)
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

/* sum all values in tree */
void
sumVals(node *root, double *sum)
{
    if (root != NULL) {
        sumVals(root->link[0], sum);
        sumVals(root->link[1], sum);
        *sum += root->data;
    }
}
