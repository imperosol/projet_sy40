//
// Created by thgir on 27/11/2022.
//

/**
 * @file random.h
 */

#ifndef PROJET_PEAGE_RANDOM_H
#define PROJET_PEAGE_RANDOM_H

/**
 * Initialise la graine pour les tirages aléatoires
 */
void rnd_init();

/**
 * Génère un nombre réel suivant une loi exponentielle
 * d'espérance `expectancy`
 */
float rnd_exponential(float expectancy);

/**
 * Génère un nombre réel suivant une loi uniforme U(a, b)
 */
float rnd_uniform(float a, float b);

/**
 * Génère un nombre entier aléatoire suivant une loi de probabilité
 * uniforme, compris dans l'intervalle [a; b[
 */
int rnd_uniform_i(int a, int b);

/**
 * @fn rnd_normal
 * Génère un nombre réel alétoire suivant une loi de probabilité
 * normale \f$ \mathcal{N}(\text{expectancy}, \text{variance}) \f$
 */
float rnd_normal(float expectancy, float variance);


_Bool rnd_bernoulli(float expectancy);
unsigned int rnd_geometric(float expectancy);

#endif //PROJET_PEAGE_RANDOM_H
