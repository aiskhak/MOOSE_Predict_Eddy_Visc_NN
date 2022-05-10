
#pragma once

#include "FVFluxKernel.h"

// Forward declare variable class
class INSFVVelocityVariable;

class INSFVEddyViscCSVReynoldsStress : public FVFluxKernel
{
public:
  static InputParameters validParams();

  INSFVEddyViscCSVReynoldsStress(const InputParameters & params);

protected:
  ADReal computeQpResidual() override;

  /// the dimension of the simulation
  const unsigned int _dim;

  /// index x|y|z
  const unsigned int _axis_index;

  /// x-velocity
  const INSFVVelocityVariable * const _u_var;
  /// y-velocity
  const INSFVVelocityVariable * const _v_var;
  /// z-velocity
  const INSFVVelocityVariable * const _w_var;

  /// Density
  const Moose::Functor<ADReal> & _rho;

  /// Turbulent eddy mixing length
  //const Moose::Functor<ADReal> & _mixing_len;

  /// Eddy viscosity
  const Moose::Functor<ADReal> & _eddy_visc_csv;
};
