#ifndef AAUXVARFROMNN_H
#define AAUXVARFROMNN_H

#include "AuxKernel.h"
#include <torch/script.h>                      // added for libtorch

class AAuxVarFromNN : public AuxKernel
{
public:
  static InputParameters validParams();
  AAuxVarFromNN(const InputParameters & parameters);
protected:
  const std::string _file_name;                // name of the torchscript file
  const Real _Re;                           // maximum y coordinate
  //const VariableGradient & _grad_u;            // velocity gradient
  //const MaterialProperty<Real> & _mu;          // dynamic viscosity
  mutable torch::Tensor _inputs_tensor;        // input tensor - make a member variable for efficiency
  mutable torch::jit::script::Module _module;  // make module a member variable
  virtual Real computeValue();                 // compute function
  //Real _y_w;                                   // distance to the wall
  Real _outputs;
};

#endif
