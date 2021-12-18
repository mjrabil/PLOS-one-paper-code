
#include "faculty_vs_students_constants.h"
#include "faculty_vs_students.h"
#include <iostream>
#include <iomanip>
#include <array>

int main()
{
    //ofstream myfile;
    //ofstream myfile_1;
    //ofstream myfile_peak;
    ofstream myfile_infections;
    ofstream myfile_infections_table;
   // ofstream myfile_compartments;
    ofstream myfile_compartments_per_day;
    //  myfile.open("trial_mj.txt");
   // myfile_1.open("0.txt");
   // myfile_peak.open("Case_60_51_new.txt");
   // myfile_infections.open("TEST0_Case_omega_not_0.txt");
     myfile_infections_table.open("table_test.txt");
    //myfile_compartments.open("table_print_compartments_new.txt");
    //myfile_compartments_per_day.open("table_print_compartments_per_day_test_4.txt");


    //unsigned int vaccines_number_today;
    double counter_for_periods = 0;

    const int DAYS = 80;
    const int REPORTING_INTERVAL = 3; //every day and each interval is 8 hours (3 intervals/day)
    const int TOTAL_PERIODS_NUMBER = DAYS * REPORTING_INTERVAL; //number of periods/cycles we are running the simulation

    std::vector<region>	region_list;  // create your region_list

    region region1;
    region1.population_size = 5000; //fix num
    region1.ID = 1;
    region_list.push_back(region1);  // insert region1 to the region_list

    int disp_period_num = 0;   //counter, every 2 days
    unsigned int week = 1;     //counter for exogenous shock, X/week so X every 7 days (i.e. 7*3 cycles)

    double TAU; //rate at which individuals in the testing pool are screened for infection
    double OMEGA; //rate at which vaccinated individuals are screened for infection
    int NUM_VACCINES_PER_DAY;
    double ETA; //screening compliance rate
    double ALPHA; //vaccination compliance rate 

    //Vaccination array:
    int NUM_VACCINES_PER_DAY_array[] = {120 }; // {0, 30, 60, 120 };

    //Screening arrays:
    double TAU_array[] = { 0, 1.0 / (3 * 14.0), 1.0 / (3 * 7.0), 1.0 / (3 * 3.0), 1.0 / (3 * 2.0), 1.0 / (3 * 1.0) };

    double initial_KI_array[] = { 1500 };// {1500, 3000, 4500 }; //i.e. 30%, 60%, 90%
    double initial_KI_f_array[] = {136}; // {136, 273, 409}; //i.e. 30%, 60%, 90%

    //For sensitivity analysis later:
    double ETA_array[] = { 0.5 }; // { 0.5, 0.75, 0.95 };    //compliance to screening
    double ALPHA_array[] = { 0.5 };// { 0.5, 0.75, 0.95 };  //compliance to vaccination

    //Size of arrays:
    int TAU_array_size = sizeof(TAU_array) / sizeof(TAU_array[0]);
    int NUM_VACCINES_PER_DAY_array_size = sizeof(NUM_VACCINES_PER_DAY_array) / sizeof(NUM_VACCINES_PER_DAY_array[0]);
    int initial_KI_array_size = sizeof(initial_KI_array) / sizeof(initial_KI_array[0]);
    int initial_KI_f_array_size = sizeof(initial_KI_f_array) / sizeof(initial_KI_f_array[0]);
    int ETA_array_size = sizeof(ETA_array) / sizeof(ETA_array[0]);
    int ALPHA_array_size = sizeof(ALPHA_array) / sizeof(ALPHA_array[0]);

    //Use later for sensitivity analysis:
   // myfile_infections_table << "KI(0)\t" << "KI_f(0)\t" << "Scr compliance\t" << "vacc compliance\t" << "Freq. of TAU\t" << "Freq. of Omega\t" << "Vacc rate/day\t" << "#vacc std inf.\t" << "#unvacc std inf.\t" << "TOTAL std inf\t" << "#vacc fac inf.\t" << "#unvacc fac inf.\t" << "TOTAL fac inf\t" << "TOTAL inf\t" << endl;

    //Instead, use now:
   // myfile_infections_table << "KI(0)\t" << "KI_f(0)\t" << "Freq. of TAU\t" << "Freq. of Omega\t" << "Vacc rate/day\t" << "#vacc std inf.\t" << "#unvacc std inf.\t" << "TOTAL std inf\t" << "#vacc fac inf.\t" << "#unvacc fac inf.\t" << "TOTAL fac inf\t" << "TOTAL inf\t" << "Peak # Hosp\t" << "Peak Day Hosp\t" << "Peak # inf\t" << "Peak Day inf\t" << "Total Deaths\t" << "# Hosp Std\t" << "# Hosp Fac\t" << "Total Hosp\t" << endl;
    myfile_infections_table << "Scr compl\t" << "Vacc compl\t"<<"Freq. of TAU\t" << "Freq. of Omega\t" << "Vacc rate/day\t" << "#vacc std inf.\t" << "#unvacc std inf.\t" << "TOTAL std inf\t" << "#vacc fac inf.\t" << "#unvacc fac inf.\t" << "TOTAL fac inf\t" << "TOTAL inf\t" << "Peak # Hosp\t" << "Peak Day Hosp\t" << "Peak # inf\t" << "Peak Day inf\t" << "Total Deaths\t" << "# Hosp Std\t" << "# Hosp Fac\t" << "Total Hosp\t" << endl;

    // myfile_compartments << "KI(0)\t" << "KI_f(0)\t" << "Freq. of TAU\t" << "Freq. of Omega\t" << "Vacc rate/day\t" << "Unit\t" << "Uninfected\t" << "Asymptomatic\t" << "Exposed\t" << "False Positive\t" << "False Positive Vaccinated & Uninf.\t" << "False Positive Recovered & Unknown\t" << "Immune\t" << "Recovered & Unknown\t" << "Dead\t" << "Hospitalized\t" << "Symptomatic\t" << "True Positive\t" << "VU\t" << "VE\t" << "VA\t";
   // myfile_compartments << "Uninfected_f\t" << "Asymptomatic_f\t" << "Exposed_f\t" << "False Positive_f\t" << "False Positive Vaccinated & Uninf_f.\t" << "False Positive Recovered & Unknown_f\t" << "Immune_f\t" << "Recovered & Unknown_f\t" << "Dead_f\t" << "Hospitalized_f\t" << "Symptomatic_f\t" << "True Positive_f\t" << "VU_f\t" << "VE_f\t" << "VA_f\t" << endl;
    myfile_compartments_per_day << "Unit\t" << "Uninfected\t" << "Asymptomatic\t" << "Exposed\t" << "False Positive\t" << "False Positive Vaccinated & Uninf.\t" << "False Positive Recovered & Unknown\t" << "Immune\t" << "Recovered & Unknown\t" << "Dead\t" << "Hospitalized\t" << "Symptomatic\t" << "True Positive\t" << "VU\t" << "VE\t" << "VA\t";
    myfile_compartments_per_day << "Uninfected_f\t" << "Asymptomatic_f\t" << "Exposed_f\t" << "False Positive_f\t" << "False Positive Vaccinated & Uninf_f.\t" << "False Positive Recovered & Unknown_f\t" << "Immune_f\t" << "Recovered & Unknown_f\t" << "Dead_f\t" << "Hospitalized_f\t" << "Symptomatic_f\t" << "True Positive_f\t" << "VU_f\t" << "VE_f\t" << "VA_f\t" << "N\t"<<endl;



    for (int f = 0; f < initial_KI_f_array_size; f++)
    {
        for (int k = 0; k < initial_KI_array_size; k++)
        {
            for (int e = 0; e < ETA_array_size; e++)
            {
                for (int a = 0; a < ALPHA_array_size; a++)
                {
                    for (int p = 0; p < NUM_VACCINES_PER_DAY_array_size; p++)
                    {
                        for (int q = 0; q < TAU_array_size; q++)
                        {
                            NUM_VACCINES_PER_DAY = NUM_VACCINES_PER_DAY_array[p];
                            TAU = TAU_array[q];
                            OMEGA = 0;// TAU; //or = 0; (MANUALLY!!!!!!!!!!!!!) for the vaccinated individuals are not screened but only the unvaccinated ones 
                            ETA = ETA_array[e];
                            ALPHA = ALPHA_array[a]; 

                            if (TAU != 0 && OMEGA != 0 && NUM_VACCINES_PER_DAY != 0) myfile_infections << "V_Sf --" << NUM_VACCINES_PER_DAY << " vaccine/day" << endl;
                            if (TAU != 0 && OMEGA == 0 && NUM_VACCINES_PER_DAY != 0) myfile_infections << "V_Sp --" << NUM_VACCINES_PER_DAY << " vaccine/day" << endl;
                            if (TAU == 0 && OMEGA == 0 && NUM_VACCINES_PER_DAY != 0) myfile_infections << "V_Sbar --" << NUM_VACCINES_PER_DAY << " vaccine/day" << endl;
                            if (TAU != 0 && OMEGA != 0 && NUM_VACCINES_PER_DAY == 0) myfile_infections << "Vbar_Sf --" << NUM_VACCINES_PER_DAY << " vaccine/day" << endl;
                            if (TAU == 0 && OMEGA == 0 && NUM_VACCINES_PER_DAY == 0) myfile_infections << "Vbar_Sbar --" << NUM_VACCINES_PER_DAY << " vaccine/day" << endl;

                            //use later for sensitivity analysis:
                            //myfile_infections_table << initial_KI_array[k] << "\t" << initial_KI_f_array[f] << "\t"<<ETA << "\t"<<ALPHA << "\t";

                            //Instead, use now this:
                            myfile_infections_table << ETA << "\t" << ALPHA << "\t";
                            //myfile_infections_table << initial_KI_array[k] << "\t" << initial_KI_f_array[f] << "\t";
                            //myfile_compartments << initial_KI_array[k] << "\t" << initial_KI_f_array[f] << "\t";
                            myfile_compartments_per_day << initial_KI_array[k] << "\t" << initial_KI_f_array[f] << "\t";

                            if (TAU == 0)
                            {
                                myfile_infections << "CASE when there is NO screening for the unvaccinated, " << endl;
                                myfile_infections_table << "N/A\t";
                                //myfile_compartments << "N/A\t";
                                 myfile_compartments_per_day << "N/A\t";
                            }
                            else
                            {
                                myfile_infections << "CASE when screening for the unvaccinated is every " << 1.0 / (3 * TAU) << "days, " << endl;
                                myfile_infections_table << 1.0 / (3 * TAU) << "\t";
                               // myfile_compartments << 1.0 / (3 * TAU) << "\t";
                                myfile_compartments_per_day << 1.0 / (3 * TAU) << "\t";
                            }

                            if (OMEGA == 0)
                            {
                                myfile_infections << "when there is NO screening for the vaccinated, " << endl;
                                myfile_infections_table << "N/A\t";
                               // myfile_compartments << "N/A\t";
                                myfile_compartments_per_day << "N/A\t";
                            }
                            else
                            {
                                myfile_infections << "when screening for the vaccinated is every " << 1.0 / (3 * OMEGA) << "days, " << endl;
                                myfile_infections_table << 1.0 / (3 * OMEGA) << "\t";
                               // myfile_compartments << 1.0 / (3 * OMEGA) << "\t";
                                myfile_compartments_per_day << 1.0 / (3 * OMEGA) << "\t";
                            }

                            if (NUM_VACCINES_PER_DAY == 0)
                            {
                                myfile_infections << "and when there is NO vaccination, " << endl;
                                myfile_infections_table << "N/A\t";
                               // myfile_compartments << "N/A\t";
                               myfile_compartments_per_day << "N/A\t" << endl;
                            }
                            else
                            {
                                myfile_infections << "and when vaccination rate is " << NUM_VACCINES_PER_DAY << "days, " << endl;
                                myfile_infections_table << NUM_VACCINES_PER_DAY << "\t";
                               // myfile_compartments << NUM_VACCINES_PER_DAY << "\t";
                                myfile_compartments_per_day << NUM_VACCINES_PER_DAY << "\t" << endl;
                            }

                            counter_for_periods = 0;
                            disp_period_num = 0;
                            week = 1;


                            //myfile_1 << "Unit\t" << "Uninfected\t" << "Asymptomatic\t" << "Exposed\t" << "False Positive\t" << "False Positive Vaccinated & Uninf.\t" << "False Positive Recovered & Unknown\t" << "Immune\t" << "Recovered & Unknown\t" << "Dead\t" << "Symptomatic\t" << "True Positive\t" << "VU\t" << "VA\t" << "VE\t" << "#Vaccines: Asymp.\t" << "#Vaccines: Exp.\t" << "#Vaccines: Uninf.\t" << "#Vaccines Recov&known\t" << "Total# Vaccines/Time Period\t" << "Cumul. # Vaccines given so far\t" << "Cumul. Unvaccinated got Infected\t" << "Cumul. Vaccinated got infected\t" << "Ratio1: unvaccinated infected/uninfected\t" << "Ratio2: vaccinated infected/total vaccinated\t" << endl;
                           // myfile_peak << "Unit\t" << "vacc then infected\t" << "Unvaccinated then infected\t" << "sum of infections\t" << "symptomatics\t" << endl;
                           

                            int loop_index;
                            loop_index = TOTAL_PERIODS_NUMBER;
                            for (int i = 0; i < loop_index; i++)
                            {


                                for (std::vector<region>::iterator it = region_list.begin(); it != region_list.end(); ++it)
                                {   //"it" is now a pointer pointing to each region, so not only "it" shows the information on each region
                                //but also if we change something in "it", the region in the region_list will change

                                    if (i == 0) //Initializations
                                    {
                                        if (it->ID == 1)
                                        {
                                            it->previous_uninfected = 5000 - initial_KI_array[k];         //U(0) //INSERT HERE
                                            it->current_uninfected = 4990 - initial_KI_array[k];                  //U(1) //INSERT 
                                            it->uninfected = it->current_uninfected;
                                            it->previous_asymptomatic_infected = 0.0;  //A(0)
                                            it->current_asymptomatic = 10;          //A(1)
                                            it->asymptomatic_infected = it->current_asymptomatic;
                                            //it->cumul_infected = 10;                //A+S
                                            it->recovered_unknown = 0.0; //INSERT HERE
                                            it->immune = initial_KI_array[k];        //INSERT HERE
                                            it->dead = 0.0;
                                            it->hospitalized = 0.0;
                                            it->current_exposed_asymptomatic = 0.0;
                                            it->exposed_asymptomatic = it->current_exposed_asymptomatic;
                                            it->false_positive = 0.0;
                                            it->false_positive_VU = 0.0;
                                            it->false_positive_RU = 0.0;
                                            it->true_positive = 0.0;
                                            it->symptomatic_infected = 0.0;



                                            it->previous_uninfected_f =  455 - initial_KI_f_array[f];         //U(0) //INSERT HERE
                                            it->current_uninfected_f = 454 - initial_KI_f_array[f];                  //U(1) //INSERT HERE
                                            it->uninfected_f = it->current_uninfected_f;  
                                            it->previous_asymptomatic_infected_f = 0.0;  //A(0)
                                            it->current_asymptomatic_f =  1;          //A(1)
                                            it->asymptomatic_infected_f = it->current_asymptomatic_f;
                                            it->recovered_unknown_f = 0.0; //INSERT HERE
                                            it->immune_f = initial_KI_f_array[f];        //INSERT HERE
                                            it->dead_f = 0.0;
                                            it->hospitalized_f = 0.0;
                                            it->current_exposed_asymptomatic_f = 0.0;
                                            it->exposed_asymptomatic_f = it->current_exposed_asymptomatic_f;
                                            it->false_positive_f = 0.0;
                                            it->false_positive_VU_f = 0.0;
                                            it->false_positive_RU_f = 0.0;
                                            it->true_positive_f = 0.0;
                                            it->symptomatic_infected_f = 0.0;

                                            it->num_vaccines_per_day = NUM_VACCINES_PER_DAY;  // INSERT 0, 30, 60 or 120

                                           // it->lambda_t(t)=vaccination limit per time unit / (A+U+E+RU)   => vaccination
                                            it->lambda_t = (it->num_vaccines_per_day / REPORTING_INTERVAL) / (it->current_asymptomatic + it->current_uninfected + it->exposed_asymptomatic + it->recovered_unknown + it->current_asymptomatic_f + it->current_uninfected_f + it->exposed_asymptomatic_f + it->recovered_unknown_f);

                                        }

                                        else
                                        {
                                            cout << "ERROR! " << endl;
                                            break;
                                        }
                                        it->indicator = 0.0;
                                        // it->cumul_TP = 0; 
                                        it->cumul_asymptomatic = 0.0;
                                        it->vaccinated_asymptomatic_infected = 0.0;
                                        it->vaccinated_exposed_asymptomatic = 0;
                                        it->vaccinated_uninfected = 0.0;
                                        it->vaccinated_recovered_unknown = 0.0;
                                        it->cumul_vaccines_for_asymptomatic = 0.0;
                                        it->cumul_vaccines_for_exposed = 0.0;
                                        it->cumul_vaccines_for_uninfected = 0.0;
                                        it->cumul_vaccines_for_recovered_unknown = 0.0;
                                        it->cumul_total_vaccines_given = 0.0;
                                        it->cumul_pcr_asymptomatic = 0.0;
                                        it->cumul_pcr_exposed = 0.0;
                                        it->cumul_pcr_uninfected = 0.0;
                                        it->cumul_pcr_recovered_unknown = 0.0;
                                        it->cumul_pcr_VA = 0.0;
                                        it->cumul_pcr_VE = 0.0;
                                        it->cumul_pcr_VU = 0.0;
                                        it->cumul_pcr_VRU = 0.0;
                                        it->cumul_vaccinated_got_infected = 0.0;
                                        it->cumul_unvaccinated_got_infected = 0.0;
                                        it->vaccinated_got_infected = 0.0;
                                        it->unvaccinated_got_infected = 0.0;
                                        //it->max_sum_infections = 0.0;
                                        it->max_sum_infections_both_groups = 0.0;
                                        it->max_unvaccinated_got_infected = 0.0;
                                        it->max_vaccinated_got_infected = 0.0;
                                        it->max_sum_hospitalized_both_groups = 0.0;
                                        it->day_max_sum_hospitalized_both_groups = 0.0;
                                        //it->day_max_sum_infections = 0.0;
                                        it->day_max_sum_infections_both_groups = 0.0;
                                        it->day_max_unvaccinated_got_infected = 0.0;
                                        it->day_max_vaccinated_got_infected = 0.0;
                                        it->current_VA = 0;
                                        it->current_VE = 0;
                                        it->current_VU = 0;
                                        it->previous_VU = 0;
                                        it->previous_RU = 0;
                                        it->previous_VA = 0;
                                        it->current_immune = it->immune; //////
                                        it->current_RU = 0;

                                        it->cumul_asymptomatic_f = 0.0;
                                        it->vaccinated_asymptomatic_infected_f = 0.0;
                                        it->vaccinated_exposed_asymptomatic_f = 0;
                                        it->vaccinated_uninfected_f = 0.0;
                                        it->vaccinated_recovered_unknown_f = 0.0;
                                        it->cumul_vaccines_for_asymptomatic_f = 0.0;
                                        it->cumul_vaccines_for_exposed_f = 0.0;
                                        it->cumul_vaccines_for_uninfected_f = 0.0;
                                        it->cumul_vaccines_for_recovered_unknown_f = 0.0;
                                        it->cumul_total_vaccines_given_f = 0.0;
                                        it->cumul_pcr_asymptomatic_f = 0.0;
                                        it->cumul_pcr_exposed_f = 0.0;
                                        it->cumul_pcr_uninfected_f = 0.0;
                                        it->cumul_pcr_recovered_unknown_f = 0.0;
                                        it->cumul_pcr_VA_f = 0.0;
                                        it->cumul_pcr_VE_f = 0.0;
                                        it->cumul_pcr_VU_f = 0.0;
                                        it->cumul_pcr_VRU_f = 0.0;
                                        it->cumul_vaccinated_got_infected_f = 0.0;
                                        it->cumul_unvaccinated_got_infected_f = 0.0;
                                        it->vaccinated_got_infected_f = 0.0;
                                        it->unvaccinated_got_infected_f = 0.0;
                                        it->max_sum_infections_f = 0.0;

                                        it->cumul_hospitalization = 0.0;
                                        it->cumul_hospitalization_f = 0.0;
                                        it->cumul_hospitalization_both_groups = 0.0;
                                        it->cumul_deaths = 0.0;
                                        it->cumul_deaths_f = 0.0;
                                        it->cumul_deaths_both_groups = 0.0;

                                        //it->max_unvaccinated_got_infected_f = 0.0;
                                        //it->max_vaccinated_got_infected_f = 0.0;
                                        //it->max_hospitalized_f = 0.0;
                                        //it->day_max_hospitalized_f = 0.0;
                                        it->day_max_sum_infections_f = 0.0;
                                        //it->day_max_unvaccinated_got_infected_f = 0.0;
                                        //it->day_max_vaccinated_got_infected_f = 0.0;
                                        it->current_VA_f = 0;
                                        it->current_VE_f = 0;
                                        it->current_VU_f = 0;
                                        it->previous_VU_f = 0;
                                        it->previous_RU_f = 0;
                                        it->previous_VA_f = 0;
                                        it->current_immune_f = it->immune_f;   //
                                        it->current_RU_f = 0;

                                        it->ratio_students = ((it->current_asymptomatic + it->current_VA) * 1.0) / (1.0 * (it->current_uninfected + it->current_VU + it->current_exposed_asymptomatic + it->current_VE + it->current_asymptomatic + it->current_VA + it->current_immune + it->current_RU));
                                        it->ratio_faculty = ((it->current_asymptomatic_f + it->current_VA_f) * 1.0) / (1.0 * (it->current_uninfected_f + it->current_VU_f + it->current_exposed_asymptomatic_f + it->current_VE_f + it->current_asymptomatic_f + it->current_VA_f + it->current_immune_f + it->current_RU_f));
                                        //denominator needs to be >0. So not an empty population
                                    }

                                    if (i / 3 == (7 * week - 1))
                                    {
                                        it->indicator = 1.0; //=1 to consider exogenous shocks
                                        week++;
                                    }
                                    else
                                    {

                                        it->indicator = 0.0;
                                    }
                                    
                                   // STUDENTS COMPARTMENTS:
                                    it->uninfected = it->current_uninfected * (1 - BETA_SS * it->ratio_students - BETA_FS * it->ratio_faculty - it->lambda_t * ALPHA) - it->previous_uninfected * TAU * ETA * (1 - Sp) + MU * it->false_positive - X * 1.0 * it->indicator; //Fp here is current FP (not yet updated)
                                    
                                    it->asymptomatic_infected = it->current_asymptomatic * (1 - SIGMA - RHO - it->lambda_t * ALPHA) - it->previous_asymptomatic_infected * TAU * ETA * Se + it->current_exposed_asymptomatic * THETA;
                                    
                                    it->exposed_asymptomatic = it->exposed_asymptomatic * (1 - THETA - it->lambda_t * ALPHA) + it->current_uninfected * (BETA_SS * it->ratio_students + BETA_FS * it->ratio_faculty)+ 1.0 * X * it->indicator;
                                    
                                    it->false_positive = it->false_positive * (1 - MU) + it->previous_uninfected * TAU * ETA * (1 - Sp);
                                  

                                    it->immune = it->immune + RHO * (it->true_positive + it->symptomatic_infected + it->hospitalized + it->vaccinated_asymptomatic_infected) + it->lambda_t * ALPHA * it->recovered_unknown + PHI * EPSILON * (it->current_VU); //no need for current variables bcz variables are not updated yet
                                    
                                    it->recovered_unknown = it->recovered_unknown * (1 - it->lambda_t * ALPHA) + RHO * it->current_asymptomatic - it->previous_RU * TAU * ETA * (1 - Sp) + MU * it->false_positive_RU;
                                    
                                    it->dead = it->dead + DELTA * it->hospitalized;
                                    
                                    it->hospitalized =  it->hospitalized * (1 - RHO - DELTA) + PI * it->symptomatic_infected;
                                    
                                    it->symptomatic_infected = it->symptomatic_infected * (1 - RHO - PI) + SIGMA * (it->true_positive + it->current_asymptomatic + it->current_VA); //TP not yet updated
                                    
                                    it->true_positive = it->true_positive * (1 - SIGMA - RHO) + it->previous_asymptomatic_infected * TAU * ETA * Se + it->previous_VA * OMEGA * ETA * Se;
                                   
                                    it->vaccinated_uninfected = it->vaccinated_uninfected * (1 - PHI * EPSILON - BETA_SS * it->ratio_students - BETA_FS * it->ratio_faculty) + it->lambda_t * ALPHA * it->current_uninfected - it->previous_VU * OMEGA * ETA * (1 - Sp) + MU * it->false_positive_VU;
                                    
                                    it->false_positive_VU = it->false_positive_VU * (1 - MU) + it->previous_VU * OMEGA * ETA * (1 - Sp);
                                    
                                    it->false_positive_RU = it->false_positive_RU * (1 - MU) + it->previous_RU * TAU * ETA * (1 - Sp);
                                    
                                    it->vaccinated_exposed_asymptomatic = it->vaccinated_exposed_asymptomatic * (1 - THETA) + it->lambda_t * ALPHA * it->current_exposed_asymptomatic + it->current_VU * (BETA_SS * it->ratio_students + BETA_FS * it->ratio_faculty);
                                    
                                    it->vaccinated_asymptomatic_infected = it->vaccinated_asymptomatic_infected * (1 - SIGMA-RHO) + it->lambda_t * ALPHA * it->current_asymptomatic - it->previous_VA * OMEGA * ETA * Se +it->current_VE * THETA;
                                    

                                    //FACULTY COMPARTMENTS:
                                    it->uninfected_f = it->current_uninfected_f * (1 - BETA_SF * it->ratio_students - BETA_FF * it->ratio_faculty - it->lambda_t * ALPHA) - it->previous_uninfected_f * TAU * ETA * (1 - Sp) + MU * it->false_positive_f -X * 1.0 * it->indicator; //Fp here is current FP (not yet updated)

                                    it->asymptomatic_infected_f = it->current_asymptomatic_f * (1 - SIGMA - RHO - it->lambda_t * ALPHA) - it->previous_asymptomatic_infected_f * TAU * ETA * Se + it->current_exposed_asymptomatic_f * THETA;

                                    it->exposed_asymptomatic_f = it->exposed_asymptomatic_f * (1 - THETA - it->lambda_t * ALPHA) + it->current_uninfected_f * (BETA_SF * it->ratio_students + BETA_FF * it->ratio_faculty) +1.0 * X * it->indicator;

                                    it->false_positive_f = it->false_positive_f * (1 - MU) + it->previous_uninfected_f * TAU * ETA * (1 - Sp);


                                    it->immune_f = it->immune_f + RHO * (it->true_positive_f + it->symptomatic_infected_f + it->hospitalized_f + it->vaccinated_asymptomatic_infected_f) + it->lambda_t * ALPHA * it->recovered_unknown_f + PHI * EPSILON * (it->current_VU_f); //no need for current variables bcz variables are not updated yet

                                    it->recovered_unknown_f = it->recovered_unknown_f * (1 - it->lambda_t * ALPHA) + RHO * it->current_asymptomatic_f - it->previous_RU_f * TAU * ETA * (1 - Sp) + MU * it->false_positive_RU_f;

                                    it->dead_f = it->dead_f + DELTA_f * it->hospitalized_f;

                                    it->hospitalized_f = it->hospitalized_f* (1 - RHO - DELTA_f) + PI_f * it->symptomatic_infected_f;


                                    it->symptomatic_infected_f = it->symptomatic_infected_f * (1 - RHO - PI_f) + SIGMA * (it->true_positive_f + it->current_asymptomatic_f + it->current_VA_f); //TP not yet updated

                                    it->true_positive_f = it->true_positive_f * (1 - SIGMA - RHO) + it->previous_asymptomatic_infected_f * TAU * ETA * Se + it->previous_VA_f * OMEGA * ETA * Se;

                                    it->vaccinated_uninfected_f = it->vaccinated_uninfected_f * (1 - PHI * EPSILON - BETA_SF * it->ratio_students - BETA_FF * it->ratio_faculty) + it->lambda_t * ALPHA * it->current_uninfected_f - it->previous_VU_f * OMEGA * ETA * (1 - Sp) + MU * it->false_positive_VU_f;

                                    it->false_positive_VU_f = it->false_positive_VU_f * (1 - MU) + it->previous_VU_f * OMEGA * ETA * (1 - Sp);

                                    it->false_positive_RU_f = it->false_positive_RU_f * (1 - MU) + it->previous_RU_f * TAU * ETA * (1 - Sp);

                                    it->vaccinated_exposed_asymptomatic_f = it->vaccinated_exposed_asymptomatic_f * (1 - THETA) + it->lambda_t * ALPHA * it->current_exposed_asymptomatic_f + it->current_VU_f * (BETA_SF * it->ratio_students + BETA_FF * it->ratio_faculty);

                                    it->vaccinated_asymptomatic_infected_f = it->vaccinated_asymptomatic_infected_f * (1 - SIGMA-RHO) + it->lambda_t * ALPHA * it->current_asymptomatic_f - it->previous_VA_f * OMEGA * ETA * Se +it->current_VE_f * THETA;


                                    if (it->uninfected < 0) it->uninfected = 0;
                                    if (it->exposed_asymptomatic < 0) it->exposed_asymptomatic = 0;
                                    if (it->asymptomatic_infected < 0) it->asymptomatic_infected = 0;
                                    if (it->recovered_unknown < 0) it->recovered_unknown = 0;

                                    if (it->uninfected_f < 0) it->uninfected_f = 0;
                                    if (it->exposed_asymptomatic_f < 0) it->exposed_asymptomatic_f = 0;
                                    if (it->asymptomatic_infected_f < 0) it->asymptomatic_infected_f = 0;
                                    if (it->recovered_unknown_f < 0) it->recovered_unknown_f = 0;



                                   it->ratio_students = ((it->asymptomatic_infected + it->vaccinated_asymptomatic_infected) * 1.0) / (1.0 * (it->uninfected + it->vaccinated_uninfected + it->exposed_asymptomatic + it->vaccinated_exposed_asymptomatic + it->asymptomatic_infected + it->vaccinated_asymptomatic_infected + it->immune + it->recovered_unknown));
                                   it->ratio_faculty = ((it->asymptomatic_infected_f + it->vaccinated_asymptomatic_infected_f) * 1.0) / (1.0 * (it->uninfected_f + it->vaccinated_uninfected_f + it->exposed_asymptomatic_f + it->vaccinated_exposed_asymptomatic_f + it->asymptomatic_infected_f + it->vaccinated_asymptomatic_infected_f + it->immune_f + it->recovered_unknown_f));

                                   

                                    it->unvaccinated_got_infected = it->uninfected* (BETA_SS * it->ratio_students + BETA_FS * it->ratio_faculty);
                                    it->unvaccinated_got_infected_f = it->uninfected_f* (BETA_SF* it->ratio_students + BETA_FF * it->ratio_faculty);
                                    it->vaccinated_got_infected = it->vaccinated_uninfected* (BETA_SS* it->ratio_students + BETA_FS * it->ratio_faculty);
                                    it->vaccinated_got_infected_f = it->vaccinated_uninfected_f* (BETA_SF* it->ratio_students + BETA_FF * it->ratio_faculty);
                                    
                                    
                                  

                                    
                                    
                                   
                                    //Peak Calculations
                                    if ((it->unvaccinated_got_infected + it->vaccinated_got_infected + it->unvaccinated_got_infected_f + it->vaccinated_got_infected_f) > it->max_sum_infections_both_groups)
                                    {
                                        it->max_sum_infections_both_groups = (it->unvaccinated_got_infected + it->vaccinated_got_infected + it->unvaccinated_got_infected_f + it->vaccinated_got_infected_f);
                                        it->day_max_sum_infections_both_groups = disp_period_num + 1;
                                    }
                                     


                                    if (it->hospitalized + it->hospitalized_f > it->max_sum_hospitalized_both_groups)
                                    {
                                        it->max_sum_hospitalized_both_groups = it->hospitalized + it->hospitalized_f;
                                        it->day_max_sum_hospitalized_both_groups = disp_period_num + 1;
                                    }


                                    it->cumul_unvaccinated_got_infected = it->cumul_unvaccinated_got_infected + it->unvaccinated_got_infected;
                                    it->cumul_vaccinated_got_infected = it->cumul_vaccinated_got_infected + it->vaccinated_got_infected;

                                    it->cumul_unvaccinated_got_infected_f = it->cumul_unvaccinated_got_infected_f + it->unvaccinated_got_infected_f;
                                    it->cumul_vaccinated_got_infected_f = it->cumul_vaccinated_got_infected_f + it->vaccinated_got_infected_f;

                                    it->cumul_hospitalization = it->cumul_hospitalization + PI * it->symptomatic_infected;
                                    it->cumul_hospitalization_f = it->cumul_hospitalization_f + PI_f * it->symptomatic_infected_f;
                                    it->cumul_hospitalization_both_groups = it->cumul_hospitalization_both_groups + PI * it->symptomatic_infected + PI_f * it->symptomatic_infected_f;
                                    
                                    it->cumul_deaths = it->cumul_deaths + DELTA * it->hospitalized;
                                    it->cumul_deaths_f = it->cumul_deaths_f + DELTA_f * it->hospitalized_f;
                                    it->cumul_deaths_both_groups = it->cumul_deaths_both_groups + DELTA * it->hospitalized + DELTA_f * it->hospitalized_f;
                                    
                                   
                                   

                                    it->cumul_asymptomatic = it->cumul_asymptomatic + it->asymptomatic_infected;

                                    it->previous_asymptomatic_infected = it->current_asymptomatic;
                                    it->previous_uninfected = it->current_uninfected;
                                    it->current_asymptomatic = it->asymptomatic_infected;
                                    it->current_uninfected = it->uninfected;
                                    it->current_exposed_asymptomatic = it->exposed_asymptomatic;

                                    it->previous_VA = it->current_VA;
                                    it->previous_VU = it->current_VU;
                                    it->previous_RU = it->current_RU;
                                    it->current_VA = it->vaccinated_asymptomatic_infected;
                                    it->current_VE = it->vaccinated_exposed_asymptomatic;
                                    it->current_VU = it->vaccinated_uninfected;

                                    it->current_RU = it->recovered_unknown;
                                    it->current_immune = it->immune;

                                    it->cumul_asymptomatic_f = it->cumul_asymptomatic_f + it->asymptomatic_infected_f;

                                    it->previous_asymptomatic_infected_f = it->current_asymptomatic_f;
                                    it->previous_uninfected_f = it->current_uninfected_f;
                                    it->current_asymptomatic_f = it->asymptomatic_infected_f;
                                    it->current_uninfected_f = it->uninfected_f;
                                    it->current_exposed_asymptomatic_f = it->exposed_asymptomatic_f;

                                    it->previous_VA_f = it->current_VA_f;
                                    it->previous_VU_f = it->current_VU_f;
                                    it->previous_RU_f = it->current_RU_f;
                                    it->current_VA_f = it->vaccinated_asymptomatic_infected_f;
                                    it->current_VE_f = it->vaccinated_exposed_asymptomatic_f;
                                    it->current_VU_f = it->vaccinated_uninfected_f;

                                    it->current_RU_f = it->recovered_unknown_f;
                                    it->current_immune_f = it->immune_f;

                                    counter_for_periods = counter_for_periods + 1.0 / 3;


                                    it->lambda_t = (it->num_vaccines_per_day / REPORTING_INTERVAL) / (it->asymptomatic_infected + it->uninfected + it->exposed_asymptomatic + it->recovered_unknown + it->asymptomatic_infected_f + it->uninfected_f + it->exposed_asymptomatic_f + it->recovered_unknown_f);

 
                                 
                                    
                                    myfile_compartments_per_day << disp_period_num + 1 << fixed << setprecision(1)<<"\t" << it->uninfected << "\t" << it->asymptomatic_infected << "\t" << it->exposed_asymptomatic << "\t" << it->false_positive << "\t" << it->false_positive_VU << "\t" <<it->false_positive_RU << "\t" << it->immune << "\t" << it->recovered_unknown << "\t" <<it->dead << "\t";

                                    myfile_compartments_per_day << it->hospitalized << "\t" << it->symptomatic_infected << "\t" << it->true_positive << "\t" << it->vaccinated_uninfected << "\t" << it->vaccinated_exposed_asymptomatic << "\t" << it->vaccinated_asymptomatic_infected << "\t";

                                    myfile_compartments_per_day << it->uninfected_f << "\t" << it->asymptomatic_infected_f << "\t" << it->exposed_asymptomatic_f << "\t" << it->false_positive_f << "\t" << it->false_positive_VU_f << "\t" << it->false_positive_RU_f << "\t" << it->immune_f << "\t" << it->recovered_unknown_f << "\t" << it->dead_f << "\t";

                                    myfile_compartments_per_day << it->hospitalized_f << "\t" << it->symptomatic_infected_f << "\t" << it->true_positive_f << "\t" << it->vaccinated_uninfected_f << "\t" << it->vaccinated_exposed_asymptomatic_f << "\t" << it->vaccinated_asymptomatic_infected_f ;
                                   
                                    myfile_compartments_per_day << "\t" << it->uninfected + it->asymptomatic_infected + it->exposed_asymptomatic + it->false_positive + it->false_positive_VU + it->false_positive_RU + it->immune + it->recovered_unknown + it->dead + it->hospitalized + it->symptomatic_infected + it->true_positive + it->vaccinated_uninfected + it->vaccinated_exposed_asymptomatic + it->vaccinated_asymptomatic_infected + it->uninfected_f + it->asymptomatic_infected_f + it->exposed_asymptomatic_f + it->false_positive_f + it->false_positive_VU_f + it->false_positive_RU_f + it->immune_f + it->recovered_unknown_f + it->dead_f + it->hospitalized_f + it->symptomatic_infected_f + it->true_positive_f + it->vaccinated_uninfected_f + it->vaccinated_exposed_asymptomatic_f + it->vaccinated_asymptomatic_infected_f << endl;
                                    


                                    // }
                                    

                                    if ((i == TOTAL_PERIODS_NUMBER - 1)|| (it->uninfected <= 0))
                                    {
                                        
                                        myfile_infections << fixed << setprecision(0) << endl;
                                        myfile_infections << "Total Number of vaccinated students who got  infected: " << round(it->cumul_vaccinated_got_infected) << endl;
                                        myfile_infections << "Total Number of unvaccinated students who got infected: " << round(it->cumul_unvaccinated_got_infected) << endl << endl << endl << endl;
                                        myfile_infections_table << round(it->cumul_vaccinated_got_infected) << "\t" << round(it->cumul_unvaccinated_got_infected) << "\t" << round(it->cumul_vaccinated_got_infected) + round(it->cumul_unvaccinated_got_infected) << "\t";

                                        myfile_infections << "Total Number of vaccinated faculty who got  infected: " << round(it->cumul_vaccinated_got_infected_f) << endl;
                                        myfile_infections << "Total Number of unvaccinated faculty who got infected: " << round(it->cumul_unvaccinated_got_infected_f) << endl << endl << endl << endl;
                                        myfile_infections_table << round(it->cumul_vaccinated_got_infected_f) << "\t" << round(it->cumul_unvaccinated_got_infected_f) << "\t" << round(it->cumul_vaccinated_got_infected_f) + round(it->cumul_unvaccinated_got_infected_f) << "\t";
                                        myfile_infections_table << round(it->cumul_vaccinated_got_infected) + round(it->cumul_unvaccinated_got_infected) + round(it->cumul_vaccinated_got_infected_f) + round(it->cumul_unvaccinated_got_infected_f) << "\t";
                                        myfile_infections_table << round(it->max_sum_hospitalized_both_groups) << "\t" << round(it->day_max_sum_hospitalized_both_groups) << "\t" << round(it->max_sum_infections_both_groups) << "\t" << round(it->day_max_sum_infections_both_groups) << "\t";
                                        myfile_infections_table << round(it->cumul_deaths_both_groups) << "\t" << round(it->cumul_hospitalization) << "\t" << round(it->cumul_hospitalization_f) << "\t" << round(it->cumul_hospitalization)+ round(it->cumul_hospitalization_f) << endl;
                                       
                                      
                                

                                        loop_index = i + 1;

                                        
                                    }
                                }

                                if (i >= disp_period_num * REPORTING_INTERVAL) // increase disp_period_num so that we do not report until the next REPORTING_INTERVAL
                                {
                                    disp_period_num++;
                                }




                            }
                        }
                    } myfile_infections_table << endl;


                } myfile_infections_table << endl;
            }
            myfile_infections_table << endl;
        } myfile_infections_table << endl<<endl;
    }



   // myfile.close();
   // myfile_1.close();
   // myfile_peak.close();
    //myfile_infections.close();
    myfile_infections_table.close();
    //myfile_compartments.close();
    //myfile_compartments_per_day.close();


    return 0;
}
