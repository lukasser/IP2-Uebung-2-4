/* 
 * This is the main program for Uebung2_4 - Messdatenerfassung.
 *
 */

#include <iostream>
#include "binary_tree.h"
#include "uebung2_4.h"

using namespace std;

int
main(void) {

    tree *measurements = new tree; // tree to hold the values
    int total = 0;  // total number of stored values
    char choice;

    /*  Main Menu loop */
    do {

        cout << "\n========================================\n"
         << "(a) Messwert eingeben\n"
		 << "(b) Messwerte ausgeben\n"
		 << "(c) Messwert loeschen\n"
         << "(d) Durchschnittswert errechnen\n\n"
		 << "(e) Datenstand anzeigen\n"
		 << "(q) Program beenden\n   >> ";
        cin >> choice;
		
        switch (choice) {
            case 'A':
            case 'a':
                addValue(measurements);
                total++
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
                print_tree(measurements);
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
addValue(tree *meas) {
    int value;
    
    cout << "\nMesswert hinzufuegen\n"
        << "Bitte Messwert eingeben: ";
    cin >> value;

    if (insert_nr(meas, value) != 1)
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
    int value;
    
    cout << "\nMesswert loeschen\n"
         << "Bitte Messwert eingeben: ";
    cin >> value;

    if (remove(meas, value) != 1)
        cout << "ERROR\n\n";
}

/* Calculate & print the average of measurments */
void
calcAvg(tree *meas, int total) {
    if (total <= 0) {
        return;
    }
    
    int vals = 0;
    vals = sumVals(meas);

    cout << "\nDer Durchschnitt der Messwerte betraegt: "
         << vals/total << endl;
}

/* sum all values in tree */
int
sumVals(node *root) {
    static int sum = 0;

    if (root != NULL) {
        sumVals(root->link[0]);
        sumVals(root->link[1]);
        sum += root->data;    
    }

    return sum;
}
