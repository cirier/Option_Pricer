#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <algorithm>
#include "AmericanCallOption.h"
#include "AmericanPutOption.h"
#include "EuropeanCallOption.h"
#include "EuropeanPutOption.h" 
#include "BinaryTree.h"
#include "CRRPricer.h"


int main() {
    AmericanCallOption callOption(1.0, 50.0);
    AmericanPutOption putOption(1.0, 50.0);
    EuropeanCallOption euroCallOption(1.0, 50.0);

    double spotPrice = 55.0;

    std::cout << "Call Option Payoff: " << callOption.payoff(spotPrice) << std::endl;
    std::cout << "Put Option Payoff: " << putOption.payoff(spotPrice) << std::endl;

    if (callOption.isAmericanOption()) {
        std::cout << "Call Option is American." << std::endl;
    }
    else {
        std::cout << "Call Option is not American." << std::endl;
    }

    if (euroCallOption.isAmericanOption()) {
        std::cout << "European Call Option is American." << std::endl;
    }
    else {
        std::cout << "European Call Option is not American." << std::endl;
    }


    BinaryTree<int> tree(2);
    tree.setNode(0, 0, 10);
    tree.setNode(1, 0, 20);
    tree.setNode(1, 1, 30);
    tree.setNode(2, 0, 40);
    tree.setNode(2, 1, 50);
    tree.setNode(2, 2, 60);

    std::cout << "\nValues in the tree:" << std::endl;
    tree.display();

    int value = tree.getNode(1, 1);
    std::cout << "Value at position (1, 1): " << value << std::endl;

    tree.setDepth(3);

    tree.setNode(3, 0, 70);
    tree.setNode(3, 1, 80);
    tree.setNode(3, 2, 90);
    tree.setNode(3, 3, 100);

    std::cout << "\nValues in the tree after changing depth:" << std::endl;
    tree.display();


    CRRPricer americanCallPricer(&callOption, 3, 55.0, 0.1, 0.05, 0.06);  // Cr�� un pricer pour l'option call am�ricaine

    // Calcule le prix de l'option
    double americanCallPrice = americanCallPricer();
    std::cout << "\nAmerican Call Option Price: " << americanCallPrice << std::endl;

    // Acc�de aux conditions d'exercice pour l'option de call am�ricaine
    BinaryTree<bool> exerciseConditions = americanCallPricer.getExerciseConditions();

    /*
    EuropeanPutOption euroPutOption(1.0, 45.0);  // Cr�� une option de put europ�enne
    CRRPricer europeanPutPricer(&euroPutOption, 4, 40.0, 0.1, 0.05, 0.06);  // Cr�� un pricer pour l'option de put europ�enne

    // Calcule le prix de l'option
    double europeanPutPrice = europeanPutPricer();
    std::cout << "European Put Option Price: " << europeanPutPrice << std::endl;
    */
    /*
    exerciseConditions = americanCallPricer.getExerciseConditions();
    exerciseConditions.display();  // Affiche les conditions d'exercice dans la console

    */
    americanCallPricer.setDepth(5);  // Modifie la profondeur de l'arbre
    double updatedPrice = americanCallPricer();  // Recalcule le prix avec une meilleure pr�cision

    CRRPricer americanCallPricer2(&callOption, 3, 55.0, 0.06, 0.1);  // Exemple d'usage avec r et la volatilit�
    // Calcule le prix de l'option
    americanCallPrice = americanCallPricer2();
    std::cout << "American Call Option Price: " << americanCallPrice << std::endl;



    // Cr�� une option de put am�ricaine avec un prix d'exercice de 50
    AmericanPutOption putOption2(1.0, 50.0);

    // Affiche le payoff initial pour un prix du sous-jacent de 55
    spotPrice = 55.0;
    std::cout << "\nPut Option Payoff at spot price " << spotPrice << " and payoff " << putOption2.payoff(spotPrice) << std::endl;

    // Cr�� un pricer pour l'option de put am�ricaine
    CRRPricer americanPutPricer(&putOption2, 3, spotPrice, 0.1, 0.05, 0.06);

    // Calcule le prix de l'option (conditions d'exercice incluses)
    double americanPutPrice = americanPutPricer();

    // Acc�de aux conditions d'exercice pour l'option de put am�ricaine
    exerciseConditions = americanPutPricer.getExerciseConditions();

    // Affiche les conditions d'exercice dans la console
    std::cout << "Exercise Conditions:" << std::endl;
    exerciseConditions.display();

    return 0;
}
