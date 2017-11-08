#ifndef FLOW_MODEL_RIEMANN_SOLVER_FIVE_EQN_ALLAIRE_HPP
#define FLOW_MODEL_RIEMANN_SOLVER_FIVE_EQN_ALLAIRE_HPP

#include "flow/flow_models/FlowModelRiemannSolver.hpp"

class FlowModelRiemannSolverFiveEqnAllaire: public FlowModelRiemannSolver
{
    public:
        FlowModelRiemannSolverFiveEqnAllaire(
            const std::string& object_name,
            const tbox::Dimension& dim,
            const boost::shared_ptr<geom::CartesianGridGeometry>& grid_geometry,
            const int& num_species):
                FlowModelRiemannSolver(
                    d_object_name,
                    d_dim,
                    d_grid_geometry,
                    d_num_species)
        {}
        
        /*
         * Compute the convective flux from conservative variables.
         */
        void
        computeConvectiveFluxFromConservativeVariables(
            boost::shared_ptr<pdat::SideData<double> > convective_flux,
            const std::vector<boost::shared_ptr<pdat::CellData<double> > >& conservative_variables,
            const hier::Box& domain,
            const RIEMANN_SOLVER::TYPE& riemann_solver_type);
        
        /*
         * Compute the convective flux from primitive variables.
         */
        void
        computeConvectiveFluxFromPrimitiveVariables(
            boost::shared_ptr<pdat::SideData<double> > convective_flux,
            const std::vector<boost::shared_ptr<pdat::CellData<double> > >& primitive_variables,
            const hier::Box& domain,
            const RIEMANN_SOLVER::TYPE& riemann_solver_type);
        
};

#endif /* FLOW_MODEL_RIEMANN_SOLVER_FIVE_EQN_ALLAIRE_HPP */
