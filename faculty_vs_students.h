#include <iostream>
#include <ctime>
#include <cstdlib>
#include <array>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

class region
{
public:
    //attributes
    //Compartments.We defined a total of 8 model compartments, divided into three pools :

    //• Active transmissionand testing pool.Everyone is in this pool at time 0. All transmission of
    //    infection takes place between individuals in this pool.This is also the pool in which screening
    //    for infection takes place.
    double  uninfected; //U: Uninfected, susceptible individuals
    double vaccinated_uninfected; //VU
    double  exposed_asymptomatic; //E: Exposed, asymptomatic, non - infectious
    double vaccinated_exposed_asymptomatic; // VE
    double  asymptomatic_infected; //A: Infected, asymptomatic
    double vaccinated_asymptomatic_infected; //VA
    double recovered_unknown; //RU: recovered but does not know
    double vaccinated_recovered_unknown; //VRU

    double current_VA; //VA(t)
    double current_VE; //VE(t)
    double current_VU; //VU(t)
    double previous_VU; //VU(t-1)
    double previous_VA; //VA(t-1)
    double previous_RU; //RU(t-1)

     // practical variables
    double previous_asymptomatic_infected; //A(t-1)
    double current_asymptomatic;  //A(t)
    double current_exposed_asymptomatic; //E(t)
    double previous_uninfected; //U(t-1)
    double current_uninfected; //U(t)
    //        Individuals in the Exposed compartment are assumed to be neither infectious nor symptomatic.
    //        (We also assume that these individuals will invariably test negative, if screened.)
    //        Note that, without testing, individuals in these three compartments are indistinguishable from
    //        one another.

    //        • Isolation pool.Individuals in this pool are assumed to be isolated from the active transmission
    //        pooland from one another.It is assumed that transmission is not possible within this pool.
    double symptomatic_infected;//S: Infected, symptomatic(true) positive test result
    double true_positive;//TP: Infected, asymptomatic, (true) positive test result
    double false_positive;//FP: Uninfected, false positive result
    double false_positive_VU; // FPVU: Vaccinated, uninfected, detected, false positive
    double false_positive_RU; // FPRU: Recovered unknown, detected, false positive

    //        • Removed pool.Individuals in this pool are presumed to be immune for the duration of the 80 -
    //        day semester and therefore assumed to play no role either in the transmission of infection or in
    //        testing activities.They are removed from the active population and do not figure in the
    //        transmission equations that follow.
    double immune; // R:Immune (either immune because of recovering or from vaccine)

    double dead; // D: Dead
    double hospitalized; // H: Hospitalized
    //double cumul_infected; //cumul of A and S
    //double cumul_TP;       //cumul True Positives
    double cumul_asymptomatic;

    double cumul_vaccines_for_uninfected;
    double cumul_vaccines_for_exposed;
    double cumul_vaccines_for_asymptomatic;
    double cumul_vaccines_for_recovered_unknown;
    double cumul_total_vaccines_given;

    double cumul_pcr_uninfected;
    double cumul_pcr_exposed;
    double cumul_pcr_asymptomatic;
    double cumul_pcr_recovered_unknown;
    double cumul_pcr_VA;
    double cumul_pcr_VE;
    double cumul_pcr_VU;
    double cumul_pcr_VRU;

  
    double current_RU; //RU(t)
    double current_immune; //I(t)
    
    double max_vaccinated_got_infected;
    double max_unvaccinated_got_infected;
    double max_sum_infections_both_groups;
    double max_sum_hospitalized_both_groups;
    double day_max_vaccinated_got_infected;
    double day_max_unvaccinated_got_infected;
    double day_max_sum_infections_both_groups;
    double day_max_sum_hospitalized_both_groups;
    double vaccinated_got_infected;
    double unvaccinated_got_infected;
    double cumul_vaccinated_got_infected;
    double cumul_unvaccinated_got_infected;
    //double max_sum_infections;
    //double day_max_sum_infections;

    double indicator;  //exogenous shock;

    double population_size;
    unsigned int ID;

    double lambda_t; //rate of vaccination
    double num_vaccines_per_day; //number of vaccines a region gets per day

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    //FACULTY
    double  uninfected_f; //U: Uninfected, susceptible individuals
    double vaccinated_uninfected_f; //VU
    double  exposed_asymptomatic_f; //E: Exposed, asymptomatic, non - infectious
    double vaccinated_exposed_asymptomatic_f; // VE
    double  asymptomatic_infected_f; //A: Infected, asymptomatic
    double vaccinated_asymptomatic_infected_f; //VA
    double recovered_unknown_f; //RU: recovered but does not know
    double vaccinated_recovered_unknown_f; //VRU

    double current_VA_f; //VA(t)
    double current_VE_f; //VE(t)
    double current_VU_f; //VU(t)
    double previous_VU_f; //VU(t-1)
    double previous_VA_f; //VA(t-1)
    double previous_RU_f; //RU(t-1)

     // practical variables
    double previous_asymptomatic_infected_f; //A(t-1)
    double current_asymptomatic_f;  //A(t)
    double current_exposed_asymptomatic_f; //E(t)
    double previous_uninfected_f; //U(t-1)
    double current_uninfected_f; //U(t)

    double symptomatic_infected_f;//S: Infected, symptomatic(true) positive test result
    double true_positive_f;//TP: Infected, asymptomatic, (true) positive test result
    double false_positive_f;//FP: Uninfected, false positive result
    double false_positive_VU_f; // FPVU: Vaccinated, uninfected, detected, false positive
    double false_positive_RU_f; // FPRU: Recovered unknown, detected, false positive

  
    double immune_f; // R:Immune (either immune because of recovering or from vaccine)

    double dead_f; // D: Dead
    double hospitalized_f; // H: Hospitalized

    double cumul_asymptomatic_f;

    double cumul_vaccines_for_uninfected_f;
    double cumul_vaccines_for_exposed_f;
    double cumul_vaccines_for_asymptomatic_f;
    double cumul_vaccines_for_recovered_unknown_f;
    double cumul_total_vaccines_given_f;

    double cumul_pcr_uninfected_f;
    double cumul_pcr_exposed_f;
    double cumul_pcr_asymptomatic_f;
    double cumul_pcr_recovered_unknown_f;
    double cumul_pcr_VA_f;
    double cumul_pcr_VE_f;
    double cumul_pcr_VU_f;
    double cumul_pcr_VRU_f;

    double current_RU_f; //RU(t)
    double current_immune_f; //I(t)

   // double max_vaccinated_got_infected_f;
    //double max_unvaccinated_got_infected_f;
    double max_sum_infections_f;
    //double max_hospitalized_f;
    //double day_max_vaccinated_got_infected_f;
    //double day_max_unvaccinated_got_infected_f;
    double day_max_sum_infections_f;
    //double day_max_hospitalized_f;
    double vaccinated_got_infected_f;
    double unvaccinated_got_infected_f;
    double cumul_vaccinated_got_infected_f;
    double cumul_unvaccinated_got_infected_f;

    double cumul_hospitalization;
    double cumul_hospitalization_f;
    double cumul_hospitalization_both_groups;
    double cumul_deaths;
    double cumul_deaths_f;
    double cumul_deaths_both_groups;


    double ratio_students;
    double ratio_faculty;
};