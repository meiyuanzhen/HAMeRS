#include "util/mixing_rules/equations_of_mass_diffusivity/constant/EquationOfMassDiffusivityMixingRulesConstant.hpp"

EquationOfMassDiffusivityMixingRulesConstant::EquationOfMassDiffusivityMixingRulesConstant(
    const std::string& object_name,
    const tbox::Dimension& dim,
    const int& num_species,
    const MIXING_CLOSURE_MODEL::TYPE& mixing_closure_model,
    const boost::shared_ptr<tbox::Database>& equation_of_mass_diffusivity_mixing_rules_db):
        EquationOfMassDiffusivityMixingRules(
            object_name,
            dim,
            num_species,
            mixing_closure_model,
            equation_of_mass_diffusivity_mixing_rules_db)
{
    /*
     * Get the mass diffusivity of each species from the database.
     */
    
    if (equation_of_mass_diffusivity_mixing_rules_db->keyExists("species_D"))
    {
        size_t species_D_array_size =
            equation_of_mass_diffusivity_mixing_rules_db->getArraySize("species_D");
        if (static_cast<int>(species_D_array_size) == d_num_species)
        {
            d_species_D =
                equation_of_mass_diffusivity_mixing_rules_db->getDoubleVector("species_D");
        }
        else
        {
            TBOX_ERROR(d_object_name
                << ": "
                << "number of 'species_D' entries must be equal to 'num_species'."
                << std::endl);
        }
    }
    else if (equation_of_mass_diffusivity_mixing_rules_db->keyExists("d_species_D"))
    {
        size_t species_D_array_size =
            equation_of_mass_diffusivity_mixing_rules_db->getArraySize("d_species_D");
        if (static_cast<int>(species_D_array_size) == d_num_species)
        {
            d_species_D =
                equation_of_mass_diffusivity_mixing_rules_db->getDoubleVector("d_species_D");
        }
        else
        {
            TBOX_ERROR(d_object_name
                << ": "
                << "number of 'd_species_D' entries must be equal to 'd_num_species'."
                << std::endl);
        }
    }
    else
    {
        TBOX_ERROR(d_object_name
            << ": "
            << "Key data 'species_D'/'d_species_D'"
            << "not found in data for equation of mass diffusivity mixing rules."
            << std::endl);
    }
}


/*
 * Print all characteristics of the equation of mass diffusivity class.
 */
void
EquationOfMassDiffusivityMixingRulesConstant::printClassData(
    std::ostream& os) const
{
    os << "\nPrint EquationOfMassDiffusivityMixingRulesConstant object..."
       << std::endl;
    
    os << std::endl;
    os << "EquationOfMassDiffusivityMixingRulesConstant: this = "
       << (EquationOfMassDiffusivityMixingRulesConstant *)this
       << std::endl;
    
    os << "d_object_name = "
       << d_object_name
       << std::endl;
    
    os << "d_mixing_closure_model = "
       << d_mixing_closure_model
       << std::endl;
    
    /*
     * Print the Lennard-Jones energy parameter of each species.
     */
    
    os << "d_species_D = ";
    for (int si = 0; si < d_num_species - 1; si++)
    {
        os << d_species_D[si] << ", ";
    }
    os << d_species_D[d_num_species - 1];
    os << std::endl;
}


/*
 * Put the characteristics of the equation of mass diffusivity mixing rules class into the restart
 * database.
 */
void
EquationOfMassDiffusivityMixingRulesConstant::putToRestart(
    const boost::shared_ptr<tbox::Database>& restart_db) const
{
    restart_db->putDoubleVector("d_species_D", d_species_D);
}


/*
 * Compute the mass diffusivities of the mixture with isothermal and isobaric assumptions.
 */
void
EquationOfMassDiffusivityMixingRulesConstant::getMassDiffusivities(
    std::vector<double*>& mass_diffusivities,
    const double* const pressure,
    const double* const temperature,
    const std::vector<const double*>& mass_fraction) const
{
    NULL_USE(pressure);
    NULL_USE(temperature);
    NULL_USE(mass_fraction);
    
#ifdef DEBUG_CHECK_DEV_ASSERTIONS
    TBOX_ASSERT(static_cast<int>(mass_diffusivities.size()) == d_num_species);
    TBOX_ASSERT((d_mixing_closure_model == MIXING_CLOSURE_MODEL::ISOTHERMAL_AND_ISOBARIC) ||
                (d_mixing_closure_model == MIXING_CLOSURE_MODEL::NO_MODEL && d_num_species == 1));
    TBOX_ASSERT((static_cast<int>(mass_fraction.size()) == d_num_species) ||
                (static_cast<int>(mass_fraction.size()) == d_num_species - 1));
#endif
    
    for (int si = 0; si < d_num_species; si++)
    {
        *(mass_diffusivities[si]) = d_species_D[si];
    }
}


/*
 * Get the molecular properties of a species.
 */
void
EquationOfMassDiffusivityMixingRulesConstant::getSpeciesMolecularProperties(
    std::vector<double*>& species_molecular_properties,
    const int& species_index) const
{
#ifdef DEBUG_CHECK_DEV_ASSERTIONS
    TBOX_ASSERT(static_cast<int>(species_molecular_properties.size()) >= 1);
    TBOX_ASSERT(species_index >= 0);
    TBOX_ASSERT(species_index < d_num_species);
#endif
    
    *(species_molecular_properties[0]) = d_species_D[species_index];
}
