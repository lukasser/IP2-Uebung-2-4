/* 
 * This is the main program for Uebung2_4 - Messdatenerfassung.
 *
 */

#include <iostream>
#include "binary_tree.h"
#include "main.h"

using namespace std;

int
main(void) {

    tree *measurements = new tree; // tree to hold the values
    unsigned int total = 0;  // total number of stored values
    char choice;

    /*  Main Menu loop */
    do {

        cout << "\n----- Menu -----\n"
         << "\t(a) Messwert eingeben\n"
		 << "\t(b) Messwerte ausgeben\n"
		 << "\t(c) Messwert loeschen\n"
         << "\t(d) Durchschnittswert errechnen\n"
		 << "\t(e) Datenstand anzeigen\n"
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
                calcAvg(measurements, total);
                break;

            case 'E':
            case 'e':
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
addValue(tree *meas, unsigned int id) {
    int value;
    
    cout << "Bitte Messwert eingeben: ";
    cin >> value;
    
    if (insert_nr(meas, value, id) != 1)
        cout << "ERROR\n\n";
}

/* Print values (in/pre/post) */
void
showValues(tree *meas) {
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
delValue(tree *meas) {
    unsigned int value;
    
    cout << "Bitte ID eingeben: ";
    cin >> value;

    if (remove(meas, value) != 1)
        cout << "ERROR\n\n";
}

/* Calculate & print the average of measurements */
void
calcAvg(tree *meas, int total) {
    if (total <= 0) {
        cout << "Keine Daten vorhanden!\n";
        return;
    }
    
    int sum = 0;
    sumVals(meas->root, &sum);
    
    cout << "\nDer Durchschnitt der Messwerte betraegt: "
         << (double)sum/total << endl;
}

/* sum all values in tree */
void
sumVals(node *root, int *sum) {
    if (root != NULL) {
        sumVals(root->link[0], sum);
        sumVals(root->link[1], sum);
        *sum += root->data;
    }
}
